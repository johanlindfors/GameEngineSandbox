project(audio)

set(DEPENDENCIES
    utilities
    resources
)

if(WINDOWS_STORE)
    # UWP specific dependencies here
elseif(OSX)
    list(APPEND DEPENDENCIES 
        OpenAL
    )
elseif(LINUX)
    list(APPEND DEPENDENCIES 
        OpenAL
    )
elseif(ANDROID)
    list(APPEND DEPENDENCIES
        OpenAL
    )
elseif(WIN32)
    find_package(OpenAL CONFIG REQUIRED)
    list(APPEND DEPENDENCIES
        OpenAL::OpenAL
    )
else() # WIN32

endif()

build_library(${PROJECT_NAME} "${DEPENDENCIES}")
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
