cmake_minimum_required(VERSION 3.10)
project(game)

add_executable(game WIN32 source/main.cpp)
target_link_libraries(game utilities)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)