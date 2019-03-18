function(build_library project_name)
    set(DEPENDENCIES ${ARGV1})

    file(GLOB PLATFORM_SOURCES
        source/common/*.cpp
        source/common/*.h
        source/${PLATFORM}/*.cpp
        source/${PLATFORM}/*.h
    )

    file(GLOB INCLUDES 
        include/*.h
        include/${PLATFORM}/*.h
    )

    add_library(${project_name} STATIC ${PLATFORM_SOURCES} ${INCLUDES})

    target_link_libraries(${project_name} ${DEPENDENCIES})

    target_include_directories(${project_name} PUBLIC 
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}/"
    )
endfunction()

function(build_executable project_name)
    set(DEPENDENCIES ${ARGV1})

    file(GLOB PLATFORM_SOURCES
        source/common/*.cpp
        source/common/*.h
        source/${PLATFORM}/*.cpp
        source/${PLATFORM}/*.h
    )

    include_directories(
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}/"
    )

    add_executable(${project_name} WIN32 ${PLATFORM_SOURCES})

    target_link_libraries(${project_name} ${DEPENDENCIES})

endfunction()