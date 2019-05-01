add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/dependencies/utilities)
set_target_properties (utilities PROPERTIES FOLDER "Dependencies")

add_subdirectory(engine ${CMAKE_CURRENT_BINARY_DIR}/dependencies/engine)
set_target_properties (engine PROPERTIES FOLDER "Dependencies")

add_subdirectory(game-loop ${CMAKE_CURRENT_BINARY_DIR}/dependencies/game-loop)
set_target_properties (engine PROPERTIES FOLDER "Dependencies")

if(WINDOWS_STORE)
    add_subdirectory(application-cxx ${CMAKE_CURRENT_BINARY_DIR}/dependencies/application-cxx)
    set_target_properties (application PROPERTIES FOLDER "Dependencies")
    add_subdirectory(thirdparty ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
else()
    add_subdirectory(application ${CMAKE_CURRENT_BINARY_DIR}/dependencies/application)
    set_target_properties (application PROPERTIES FOLDER "Dependencies")
endif(WINDOWS_STORE)