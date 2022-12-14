add_subdirectory(application ${CMAKE_CURRENT_BINARY_DIR}/engine/application)

add_subdirectory(filesystem ${CMAKE_CURRENT_BINARY_DIR}/engine/filesystem)

add_subdirectory(game-loop ${CMAKE_CURRENT_BINARY_DIR}/engine/game-loop)

add_subdirectory(input ${CMAKE_CURRENT_BINARY_DIR}/engine/input)

add_subdirectory(physics ${CMAKE_CURRENT_BINARY_DIR}/engine/physics)

add_subdirectory(renderer ${CMAKE_CURRENT_BINARY_DIR}/engine/renderer)

add_subdirectory(scenes ${CMAKE_CURRENT_BINARY_DIR}/engine/scenes)

add_subdirectory(resources ${CMAKE_CURRENT_BINARY_DIR}/engine/resources)

if(WINDOWS_STORE)
    add_subdirectory(updatetask ${CMAKE_CURRENT_BINARY_DIR}/engine/updatetask)
endif()

add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/engine/utilities)
