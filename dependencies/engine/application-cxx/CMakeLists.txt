project(application)

set(DEPENDENCIES
    utilities
    systems
    game-loop
)

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")

if(WINDOWS_STORE)
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_WINRT_COMPONENT 1)
endif(WINDOWS_STORE)