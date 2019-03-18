cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES 
    utilities 
    engine
)

build_executable(${PROJECT_NAME} "${DEPENDENCIES}")
