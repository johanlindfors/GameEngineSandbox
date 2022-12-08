project(renderer)

set(DEPENDENCIES
    utilities
    filesystem
    textures
    glm
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
