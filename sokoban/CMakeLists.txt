cmake_minimum_required(VERSION 3.10)
project(sokoban)

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
)

if(LINUX)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)

    message(STATUS "GLFW: ${GLFW_LIBRARIES}")
    list(APPEND DEPENDENCIES 
        GLESv2
        ${GLFW_LIBRARIES}
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

build_executable(${PROJECT_NAME} "${DEPENDENCIES}" "${RESOURCES}")
source_group("resources" ${RESOURCES})
copy_resources()
