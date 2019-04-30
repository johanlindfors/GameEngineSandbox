project(application)

set(DEPENDENCIES
    utilities
    engine
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
