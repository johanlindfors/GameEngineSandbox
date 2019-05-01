cmake_minimum_required(VERSION 3.10)
project(game)

get_property(PLATFORM_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_PLATFORM_RESOURCES_DIRECTORY)
get_property(COMMON_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_COMMON_RESOURCES_DIRECTORY)
get_property(RESOURCES GLOBAL PROPERTY GLOBAL_RESOURCES)

set(DEPENDENCIES 
    utilities
    application
    game-loop
    engine
)

if(LINUX)
    message(STATUS "Temporary solution for Linux: Finding GLUT")
    find_package(GLUT REQUIRED)
    list(APPEND DEPENDENCIES 
        GLUT::GLUT
    )
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/../" FILES ${RESOURCES})

if(WINDOWS_STORE)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
    # TODO: Remove this line when using C++/WinRT
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_WINRT_COMPONENT 1)
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
