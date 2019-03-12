cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES
    utilities
    engine
)

file(GLOB PLATFORM_SOURCES
    source/common/*.cpp
    source/common/*.h
    source/${PLATFORM}/*.cpp
    source/${PLATFORM}/*.h
)

add_executable(game WIN32 ${PLATFORM_SOURCES})
target_link_libraries(game ${DEPENDENCIES})
