cmake_minimum_required(VERSION 3.10)
project(game)

message(STATUS "=== Adding game")
get_property(PLATFORM_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_PLATFORM_RESOURCES_DIRECTORY)
get_property(COMMON_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_COMMON_RESOURCES_DIRECTORY)
get_property(RESOURCES GLOBAL PROPERTY GLOBAL_RESOURCES)

set(DEPENDENCIES 
    utilities 
    engine
)

if(LINUX)
    message(STATUS "Temporary solution for Linux: Finding GLUT")
    find_package(GLUT REQUIRED)
    list(APPEND DEPENDENCIES 
        GLUT::GLUT
    )
endif()

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/../" FILES ${RESOURCES})
    
if(WINDOWS_STORE)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()

    message(STATUS "=== COMMON_RESOURCES_DIRECTORY: ${COMMON_RESOURCES_DIRECTORY}")
    message(STATUS "=== PLATFORM_RESOURCES_DIRECTORY: ${PLATFORM_RESOURCES_DIRECTORY}")

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
