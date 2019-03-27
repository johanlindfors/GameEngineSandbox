project(engine)

set(DEPENDENCIES
    utilities
)

if(UWP)
    list(APPEND DEPENDENCIES 
        libEGL
        libGLESv2
    )
else()
    find_package(GLEW REQUIRED)
    list(APPEND DEPENDENCIES 
        GLEW::GLEW
        opengl32.lib
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
