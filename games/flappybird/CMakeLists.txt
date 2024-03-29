cmake_minimum_required(VERSION 3.10)
project(flappybird)

set_property(GLOBAL PROPERTY PLATFORM_ASSETS_DIRECTORY)
set_property(GLOBAL PROPERTY COMMON_ASSETS_DIRECTORY)
set_property(GLOBAL PROPERTY ASSETS)

add_subdirectory(assets)

get_property(PLATFORM_ASSETS_DIRECTORY GLOBAL PROPERTY GLOBAL_PLATFORM_ASSETS_DIRECTORY)
get_property(COMMON_ASSETS_DIRECTORY GLOBAL PROPERTY GLOBAL_COMMON_ASSETS_DIRECTORY)
get_property(ASSETS GLOBAL PROPERTY GLOBAL_ASSETS)

set(DEPENDENCIES
    application
    game-loop
    renderers
    resources
    input
    scenes
    physics
    tweeny
    audio
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

    list(APPEND ASSETS
        "${PROJECT_BINARY_DIR}/package.appxManifest"
        "${PROJECT_BINARY_DIR}/TemporaryKey.pfx"
    )
endif()

if(LINUX)
    find_package(PkgConfig REQUIRED)
    #pkg_search_module(GLFW REQUIRED glfw3)
    list(APPEND DEPENDENCIES 
        GLESv2
        #${GLFW_LIBRARIES}
    )
endif()

if(WINDOWS_STORE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")
endif()

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${ASSETS}")
source_group("assets" ${ASSETS})

if(WINDOWS_STORE)
    set_property(SOURCE ${ASSETS} PROPERTY VS_DEPLOYMENT_CONTENT 1)
else()
    copy_assets()
endif()
