if(WINDOWS_STORE)
    add_subdirectory(angle ${CMAKE_CURRENT_BINARY_DIR}/angle)

    set(ANGLE_FOLDER "Thirdparty/Angle")

    set(ANGLE_TARGETS
        libEGL
        libANGLE
        libGLESv2
        angle_common
        angle_image_util
        angle_preprocessor
        angle_translator
    )

    foreach(ANGLE_TARGET ${ANGLE_TARGETS})
        set_target_properties (${ANGLE_TARGET} PROPERTIES FOLDER ${ANGLE_FOLDER})
    endforeach()
endif()

if (${GAME_TO_BUILD} STREQUAL flappybird)
    message(STATUS "Adding the tweeny library to game")
    add_subdirectory(tweeny ${CMAKE_CURRENT_BINARY_DIR}/tweeny)
endif()

if (${GAME_TO_BUILD} STREQUAL snake)
    message(STATUS "Adding the entt library to game")
    add_subdirectory(entt ${CMAKE_CURRENT_BINARY_DIR}/entt)
endif()

add_subdirectory(glm ${CMAKE_CURRENT_BINARY_DIR}/glm)

if(DEFINED USE_HTTP)
    add_subdirectory(cpr ${CMAKE_CURRENT_BINARY_DIR}/cpr)
endif()