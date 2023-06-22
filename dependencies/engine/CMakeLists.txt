add_subdirectory(application ${CMAKE_CURRENT_BINARY_DIR}/engine/application)

add_subdirectory(filesystem ${CMAKE_CURRENT_BINARY_DIR}/engine/filesystem)

add_subdirectory(game-loop ${CMAKE_CURRENT_BINARY_DIR}/engine/game-loop)

if(DEFINED USE_HTTP)
    add_subdirectory(http ${CMAKE_CURRENT_BINARY_DIR}/engine/http)
endif()

add_subdirectory(input ${CMAKE_CURRENT_BINARY_DIR}/engine/input)

add_subdirectory(physics ${CMAKE_CURRENT_BINARY_DIR}/engine/physics)

add_subdirectory(renderers ${CMAKE_CURRENT_BINARY_DIR}/engine/renderers)

add_subdirectory(scenes ${CMAKE_CURRENT_BINARY_DIR}/engine/scenes)

add_subdirectory(resources ${CMAKE_CURRENT_BINARY_DIR}/engine/resources)

if(WINDOWS_STORE)
    add_subdirectory(updatetask ${CMAKE_CURRENT_BINARY_DIR}/engine/updatetask)
endif()

add_subdirectory(utilities ${CMAKE_CURRENT_BINARY_DIR}/engine/utilities)
