cmake_minimum_required(VERSION 3.10)
project(sokoban)

set_property(GLOBAL PROPERTY PLATFORM_ASSETS_DIRECTORY)
set_property(GLOBAL PROPERTY COMMON_ASSETS_DIRECTORY)
set_property(GLOBAL PROPERTY ASSETS)

add_subdirectory(assets)

get_property(PLATFORM_ASSETS_DIRECTORY GLOBAL PROPERTY GLOBAL_PLATFORM_ASSETS_DIRECTORY)
get_property(COMMON_ASSETS_DIRECTORY GLOBAL PROPERTY GLOBAL_COMMON_ASSETS_DIRECTORY)
get_property(ASSETS GLOBAL PROPERTY GLOBAL_ASSETS)

set(DEPENDENCIES 
    application
    utilities
    game-loop
    renderers
    resources
    input
    scenes
    http
)

if(USE_HTTP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_HTTP")
endif()

if(LINUX)
    list(APPEND DEPENDENCIES 
        GLESv2
    )
endif()

if(OSX)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
    list(APPEND DEPENDENCIES 
        OpenGL::GL
        glfw
    )
endif()

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")
endif()

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${ASSETS}")
source_group("assets" ${ASSETS})
copy_assets()
