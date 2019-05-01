project(engine)

set(DEPENDENCIES
    utilities
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Dependencies")
