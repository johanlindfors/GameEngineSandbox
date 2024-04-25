cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(GAME_TO_BUILD "carcassone" CACHE STRING "Provide game to build")

project(${GAME_TO_BUILD})

if(MSVC)
    message("Including VCPK toolchain")
    include(dependencies/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake)
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "_DEBUG")
else ()
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "NDEBUG")
endif ()

include(dependencies/pipeline/functions.cmake)
initialize_pipeline()

message(STATUS "Building '${CMAKE_BUILD_TYPE}' configuration of '${GAME_TO_BUILD}' for '${PLATFORM}'")

# Add dependencies for client project
add_subdirectory(dependencies)
add_subdirectory("games/${GAME_TO_BUILD}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${GAME_TO_BUILD})
