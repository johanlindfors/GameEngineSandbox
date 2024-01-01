project(application)

set(DEPENDENCIES
    utilities
    game-loop
)

if(LINUX)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    list(APPEND DEPENDENCIES 
        ${GLFWs_LIBRARIES}
    )
elseif(ANDROID)
    message(STATUS "Now adding Android references in application package")
    find_package(game-activity REQUIRED CONFIG)

    list(APPEND DEPENDENCIES
        game-activity::game-activity
        android
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
