message(STATUS "Adding dependency utilities")
add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/dependencies/utilities)

message(STATUS "Adding dependency gamelopp")
add_subdirectory(gameloop ${CMAKE_CURRENT_BINARY_DIR}/dependencies/gameloop)