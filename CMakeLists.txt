cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(GAME_TO_BUILD "sample" CACHE STRING "Provide game to build")

project(${GAME_TO_BUILD})

if (CMAKE_BUILD_TYPE STREQUAL "")
    # Build type is not set eg. command was "cmake .."
    message(STATUS "  Diag: Build type was unspecified, set to Release")
    set(CMAKE_BUILD_TYPE Release)
else ()
    message(STATUS "  Diag: Build type specified as '${CMAKE_BUILD_TYPE}'")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "_DEBUG")
else ()
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "NDEBUG")
endif ()

include(dependencies/pipeline/functions.cmake)
initialize_pipeline()

message(STATUS "Building '${GAME_TO_BUILD}' for platform ${PLATFORM}")

# Add dependencies for client project
add_subdirectory(dependencies)
add_subdirectory(${GAME_TO_BUILD})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${GAME_TO_BUILD})