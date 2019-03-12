cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES
    utilities
    engine
)

add_executable(game WIN32 source/main.cpp)
target_link_libraries(game ${DEPENDENCIES})

