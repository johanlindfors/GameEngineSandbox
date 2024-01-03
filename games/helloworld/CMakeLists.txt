cmake_minimum_required(VERSION 3.10)
project(helloworld)

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
)

if(USE_HTTP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_HTTP")
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

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")
endif()

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${ASSETS}")
source_group("assets" ${ASSETS})
copy_assets()
