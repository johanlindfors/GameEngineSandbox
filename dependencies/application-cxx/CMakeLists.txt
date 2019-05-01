project(application)

set(DEPENDENCIES
    utilities
    engine
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")

set_target_properties(${PROJECT_NAME} PROPERTIES VS_WINRT_COMPONENT 1)