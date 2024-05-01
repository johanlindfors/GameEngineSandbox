project(utilities)

if(WINDOWS_STORE)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
elseif(OSX)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(JPEG REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(PNG REQUIRED libpng)
    list(APPEND DEPENDENCIES 
        OpenGL::GL
        glfw
        PNG
        JPEG::JPEG
        OpenAL
    )
elseif(LINUX)
    find_package(PNG REQUIRED)
    find_package(JPEG REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)

    list(APPEND DEPENDENCIES 
        GLESv2
        ${GLFWs_LIBRARIES}
        PNG::PNG
        JPEG::JPEG
        OpenAL
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
else() # WIN32
    find_package(GLEW REQUIRED)
    find_package(PNG REQUIRED)
    list(APPEND DEPENDENCIES 
        GLEW::GLEW
        PNG::PNG
        OpenAL
    )
    if(WIN32)
        list(APPEND DEPENDENCIES
            opengl32.lib
        )
    endif()
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
