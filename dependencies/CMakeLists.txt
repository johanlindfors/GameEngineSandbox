message(STATUS "=== Adding dependency utilities")
add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/dependencies/utilities)
set_target_properties (utilities PROPERTIES FOLDER "Dependencies")

message(STATUS "=== Adding dependency engine")
add_subdirectory(engine ${CMAKE_CURRENT_BINARY_DIR}/dependencies/engine)
set_target_properties (engine PROPERTIES FOLDER "Dependencies")

if(WINDOWS_STORE)
    message(STATUS "=== Adding thirdparties")
    add_subdirectory(thirdparty ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
endif(WINDOWS_STORE)