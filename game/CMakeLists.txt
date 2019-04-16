cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES 
    utilities 
    engine
)

# explicit resources
set(RESOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/textures/apple.png"
    "${CMAKE_CURRENT_SOURCE_DIR}/../resources/audio/score.wav"
)

set_property(SOURCE ${RESOURES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
source_group("Resources" FILES ${RESOURCES})

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
