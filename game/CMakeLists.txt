cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES 
    utilities 
    engine
)

# explicit resources
set(RESOURCES
    "${CMAKE_CURRENT_LIST_DIR}/../resources/common/textures/apple.png"
    "${CMAKE_CURRENT_LIST_DIR}/../resources/common/audio/score.wav"
)

file(GLOB_RECURSE PLATFORM_RESOURCES
    "${CMAKE_CURRENT_LIST_DIR}/../resources/${PLATFORM}/*"
)

list(APPEND RESOURCES ${PLATFORM_RESOURCES})

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")

if(UWP)
    source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/../" FILES ${RESOURCES})
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()
    add_custom_command(TARGET game POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/../common/resources/ $<TARGET_FILE_DIR:game>/resources)
    add_custom_command(TARGET game POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/../${PLATFORM}/resources/ $<TARGET_FILE_DIR:game>/resources)
endif()

