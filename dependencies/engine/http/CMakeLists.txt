project(http)

set(DEPENDENCIES
    utilities
)
if(USE_HTTP)
    list(APPEND DEPENDENCIES
        cpr
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
