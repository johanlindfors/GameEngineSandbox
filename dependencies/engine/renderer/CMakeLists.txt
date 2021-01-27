project(renderer)

set(DEPENDENCIES
    utilities
    filesystem
    textures
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
