cmake_minimum_required(VERSION 3.10)
project(snake)

set_property(GLOBAL PROPERTY PLATFORM_RESOURCES_DIRECTORY)
set_property(GLOBAL PROPERTY COMMON_RESOURCES_DIRECTORY)
set_property(GLOBAL PROPERTY RESOURCES)

add_subdirectory(resources)

get_property(PLATFORM_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_PLATFORM_RESOURCES_DIRECTORY)
get_property(COMMON_RESOURCES_DIRECTORY GLOBAL PROPERTY GLOBAL_COMMON_RESOURCES_DIRECTORY)
get_property(RESOURCES GLOBAL PROPERTY GLOBAL_RESOURCES)

set(DEPENDENCIES 
    application
    game-loop
    renderer
    textures
    input
    scenes
)

if(WINDOWS_STORE)
    set(GAME_PACKAGE_NAME  "se.coderox.snake")
    set(GAME_VERSION       "0.1.0.0")
    set(GAME_TITLE         "a snake")
    set(GAME_DESCRIPTION   "a simple snake game")
    set(PHONE_PRODUCT_ID   "B9EC94EF-8576-33B8-81E6-0092C89DBED8")
    set(PHONE_PUBLISHER_ID "00000000-0000-0000-0000-000000000000")

    # set(APPLICATION_EXTENSIONS "<Extensions><Extension Category='windows.updateTask' EntryPoint='updatetask.ApplicationUpdateTask'/></Extensions>")
    # list(APPEND DEPENDENCIES
    #     updatetask
    # )

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/pipeline/uwp/package.appxManifest.in"
        "${PROJECT_BINARY_DIR}/package.appxManifest"
        @ONLY
    )
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/pipeline/uwp/inject.py.in"
        "${PROJECT_BINARY_DIR}/../inject.py"
         @ONLY
    )
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/pipeline/uwp/TemporaryKey.pfx"
        "${PROJECT_BINARY_DIR}/TemporaryKey.pfx"
        COPYONLY
    )

    list(APPEND RESOURCES
        "${PROJECT_BINARY_DIR}/package.appxManifest"
        "${PROJECT_BINARY_DIR}/TemporaryKey.pfx"
    )
endif()

if(LINUX OR OSX)
    message(STATUS "Temporary solution for Posix: Finding GLUT")
    find_package(GLUT REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)

    message(STATUS "GLFW: ${GLFW_LIBRARIES}")
    list(APPEND DEPENDENCIES 
        GLESv2
        ${GLFW_LIBRARIES}
    )
endif()

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")
endif()

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group("resources" ${RESOURCES})

if(WINDOWS_STORE)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${COMMON_RESOURCES_DIRECTORY} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
    
    set(PLATFORM_RESOURCES)
    if(EXISTS "${PLATFORM_RESOURCES_DIRECTORY}" AND IS_DIRECTORY "${PLATFORM_RESOURCES_DIRECTORY}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${PLATFORM_RESOURCES_DIRECTORY} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
    endif()
endif()
