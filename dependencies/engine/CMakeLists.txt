add_subdirectory(application ${CMAKE_CURRENT_BINARY_DIR}/dependencies/application)

add_subdirectory(filesystem ${CMAKE_CURRENT_BINARY_DIR}/dependencies/filesystem)

add_subdirectory(game-loop ${CMAKE_CURRENT_BINARY_DIR}/dependencies/game-loop)

add_subdirectory(input ${CMAKE_CURRENT_BINARY_DIR}/dependencies/input)

add_subdirectory(renderer ${CMAKE_CURRENT_BINARY_DIR}/dependencies/renderer)

add_subdirectory(scenes ${CMAKE_CURRENT_BINARY_DIR}/dependencies/scenes)

add_subdirectory(textures ${CMAKE_CURRENT_BINARY_DIR}/dependencies/textures)

if(WINDOWS_STORE)
    add_subdirectory(updatetask ${CMAKE_CURRENT_BINARY_DIR}/dependencies/updatetask)
endif()

add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/dependencies/utilities)
