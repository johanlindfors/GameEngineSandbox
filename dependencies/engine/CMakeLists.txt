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
    list(APPEND DEPENDENCIES 
        GLEW::GLEW
        opengl32.lib
    )
    find_package(GLEW REQUIRED)
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
