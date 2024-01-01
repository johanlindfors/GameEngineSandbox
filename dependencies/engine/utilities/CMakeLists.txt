project(utilities)

if(WINDOWS_STORE)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
elseif(OSX)
    find_package(OpenGL REQUIRED)
    list(APPEND DEPENDENCIES 
        OpenGL::GL
    )
elseif(LINUX)
    list(APPEND DEPENDENCIES 
        GLESv2
    )
elseif(ANDROID)
    find_package(PkgConfig REQUIRED)
    find_package(game-activity REQUIRED CONFIG)
    list(APPEND DEPENDENCIES
        EGL
        GLESv3
        log
        game-activity::game-activity
    )
elseif(WIN32)
    find_package(GLEW REQUIRED)
    list(APPEND DEPENDENCIES 
        opengl32.lib
        GLEW::GLEW
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
