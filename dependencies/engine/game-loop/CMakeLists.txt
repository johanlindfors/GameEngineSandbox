project(game-loop)

set(DEPENDENCIES
    utilities
    scenes
    input
    resources
    renderers
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
