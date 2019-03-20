project(engine)

set(DEPENDENCIES
    utilities
    libEGL
    libGLESv2
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
