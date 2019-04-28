cmake_minimum_required(VERSION 3.8)
project(game_engine_sandbox)

if(MSVC)

  if(MSVC_VERSION GREATER 1700)
    set(COMPILER_VERSION "12")
  elseif(MSVC_VERSION GREATER 1600)
    set(COMPILER_VERSION "11")
  endif()

  if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
    set(PLATFORM UWP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
  else()
    set(PLATFORM WIN32)
  endif()
else()
  if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM LINUX)
    set(LINUX 1)
  else()
    set(PLATFORM OSX)
    set(OSX 1)
  endif()
endif()

message(STATUS "Building platform ${PLATFORM}")

include(pipeline/functions.cmake)

# Enable folders grouping in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PLATFORM_RESOURCES_DIRECTORY)
set_property(GLOBAL PROPERTY COMMON_RESOURCES_DIRECTORY)
set_property(GLOBAL PROPERTY RESOURCES)

# Add dependencies for client project
add_subdirectory(dependencies)
add_subdirectory(resources)
add_subdirectory(game)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)