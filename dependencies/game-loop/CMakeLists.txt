project(game-loop)

set(DEPENDENCIES
    utilities
    engine
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
