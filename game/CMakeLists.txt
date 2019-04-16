cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES 
    utilities 
    engine
)

# explicit resources
set(RESOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/textures/bird.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/textures/sky.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/textures/trees.png"
)

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
