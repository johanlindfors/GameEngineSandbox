project(game-loop)

set(DEPENDENCIES
    input
    renderers
    resources
    scenes
    utilities
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
