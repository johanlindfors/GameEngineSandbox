add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/dependencies/utilities)

add_subdirectory(engine ${CMAKE_CURRENT_BINARY_DIR}/dependencies/engine)

add_subdirectory(game-loop ${CMAKE_CURRENT_BINARY_DIR}/dependencies/game-loop)

# TODO: Remove this line when using C++/WinRT
add_subdirectory(application ${CMAKE_CURRENT_BINARY_DIR}/dependencies/application)

add_subdirectory(thirdparty ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
