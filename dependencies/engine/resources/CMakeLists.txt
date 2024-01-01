project(resources)

set(DEPENDENCIES
    utilities
    filesystem
    glm
)

if(OSX)
    find_package(JPEG REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(PNG REQUIRED libpng)
    list(APPEND DEPENDENCIES 
        PNG
        JPEG::JPEG
    )
elseif(LINUX)
    find_package(PNG REQUIRED)
    find_package(JPEG REQUIRED)
    
    list(APPEND DEPENDENCIES 
        PNG::PNG
        JPEG::JPEG
    )
elseif(ANDROID)
    find_package(game-activity REQUIRED CONFIG)
    list(APPEND DEPENDENCIES
        game-activity::game-activity
        android
        jnigraphics
    )
elseif(WIN32)
    find_package(PNG REQUIRED)
    list(APPEND DEPENDENCIES 
        PNG::PNG
    )
endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
