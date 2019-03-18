project(engine)
include(../pipeline/functions.cmake)

set(DEPENDENCIES
    utilities
)

build_library(${PROJECT_NAME} ${DEPENDENCIES})
