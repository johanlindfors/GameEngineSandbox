cmake_minimum_required(VERSION 3.10)
project(game)
include(../dependencies/pipeline/functions.cmake)

set(DEPENDENCIES "utilities,engine")

build_executable(${PROJECT_NAME} "${DEPENDENCIES}")
