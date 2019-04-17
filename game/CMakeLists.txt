cmake_minimum_required(VERSION 3.10)
project(game)

set(DEPENDENCIES 
    utilities 
    engine
)

set(PLATFORM_RESOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../resources/${PLATFORM}")
set(COMMON_RESOURCES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../resources/common")

# explicit resources
set(RESOURCES
    "${COMMON_RESOURCES_DIRECTORY}/textures/apple.png"
    "${COMMON_RESOURCES_DIRECTORY}/audio/score.wav"
)

file(GLOB_RECURSE PLATFORM_RESOURCES
    ${PLATFORM_RESOURCES_DIRECTORY}/*
)

list(APPEND RESOURCES ${PLATFORM_RESOURCES})

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/../" FILES ${RESOURCES})
    
if(UWP)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()
    add_custom_command(TARGET game POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${COMMON_RESOURCES_DIRECTORY} $<TARGET_FILE_DIR:game>/resources)
    
    set(PLATFORM_RESOURCES)
    if(EXISTS "${PLATFORM_RESOURCES_DIRECTORY}" AND IS_DIRECTORY "${PLATFORM_RESOURCES_DIRECTORY}")
        add_custom_command(TARGET game POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${PLATFORM_RESOURCES_DIRECTORY} $<TARGET_FILE_DIR:game>/resources)
    endif()
endif()

