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

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")

if(UWP)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()
    add_custom_command(TARGET game POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/../resources/ $<TARGET_FILE_DIR:game>/resources)
endif()

source_group("Resources" FILES ${RESOURCES})
