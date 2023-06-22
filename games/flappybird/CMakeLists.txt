cmake_minimum_required(VERSION 3.10)
project(flappybird)

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
    renderers
    resources
    input
    scenes
    physics
    tweeny
)

if(WINDOWS_STORE)
    set(GAME_PACKAGE_NAME  "se.coderox.flappybird")
    set(GAME_VERSION       "0.1.0.0")
    set(GAME_TITLE         "flappybird")
    set(GAME_DESCRIPTION   "a flappybird game")
    set(PHONE_PRODUCT_ID   "B9EC94EF-8576-33B8-81E6-1192C89DBED8")
    set(PHONE_PUBLISHER_ID "00000000-0000-0000-0000-120000000000")

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

if(LINUX)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)

    message(STATUS "GLFW: ${GLFW_LIBRARIES}")
    list(APPEND DEPENDENCIES 
        GLESv2
        ${GLFW_LIBRARIES}
    )
endif()

if(WINDOWS_STORE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")
endif()

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group("resources" ${RESOURCES})

if(WINDOWS_STORE)
    set_property(SOURCE ${RESOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()
    copy_resources()
endif()