project(updatetask)

build_library(${PROJECT_NAME} "${DEPENDENCIES}" SHARED)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_WINRT_COMPONENT TRUE)
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Engine")
