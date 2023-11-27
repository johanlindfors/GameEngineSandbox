project(resources)

set(DEPENDENCIES
    utilities
    filesystem
    glm
)

if(ANDROID)
    find_package(game-activity REQUIRED CONFIG)
    list(APPEND DEPENDENCIES
        game-activity::game-activity
        android
        jnigraphics
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
