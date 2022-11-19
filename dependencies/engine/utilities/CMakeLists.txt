project(utilities)

if(WINDOWS_STORE)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
elseif(OSX)
    find_package(PNG REQUIRED)
    find_package(glfw3 3.4 REQUIRED)
    find_package(OpenGL REQUIRED)
    list(APPEND DEPENDENCIES 
        OpenGL::GL
        glfw
        PNG::PNG
    )
elseif(LINUX)
    find_package(PNG REQUIRED)
    find_package(PkgConfig REQUIRED)    
    pkg_search_module(GLFW REQUIRED glfw3)

    list(APPEND DEPENDENCIES 
        GLESv2
        ${GLFWs_LIBRARIES}
        PNG::PNG
    )
else() # WIN32
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
