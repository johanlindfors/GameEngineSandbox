project(utilities)

if(WINDOWS_STORE)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
elseif(LINUX)
    find_package(PNG REQUIRED)
    find_package(PkgConfig REQUIRED)    
    pkg_search_module(GLFW REQUIRED glfw3)

    message(STATUS "GLFW: ${GLFW_LIBRARIES}")
    list(APPEND DEPENDENCIES 
        GLESv2
        ${GLFW_LIBRARIES}
        PNG::PNG
    )
else()
    find_package(GLEW REQUIRED)
    find_package(PNG REQUIRED)
    list(APPEND DEPENDENCIES 
        GLEW::GLEW
        PNG::PNG
    )
    if(WIN32)
        list(APPEND DEPENDENCIES
            opengl32.lib
        )
    endif()
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
