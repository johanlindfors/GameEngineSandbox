project(utilities)

if(WINDOWS_STORE)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
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
    elseif(LINUX)
    list(APPEND DEPENDENCIES
        GL
    )
    endif()
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
