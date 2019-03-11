cmake_minimum_required(VERSION 3.8)
project(game_engine_sandbox)

# Enable folders grouping in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
  set(PLATFORM UWP)
else()
  set(PLATFORM WIN32)
endif()

# Add dependencies for client project
add_subdirectory(dependencies)
add_subdirectory(game)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)