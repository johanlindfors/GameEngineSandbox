project(game-loop)

set(DEPENDENCIES
    utilities
    engine
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Dependencies")
