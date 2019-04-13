macro(update_sources)
    file(GLOB_RECURSE COMMON_SOURCES
        source/common/*.cpp
        source/common/*.h*
    )

    file(GLOB PLATFORM_SOURCES
        source/${PLATFORM}/*.cpp
        source/${PLATFORM}/*.h*
    )
endmacro()

function(build_library project_name)
    set(DEPENDENCIES ${ARGV1})

    update_sources()

    file(GLOB_RECURSE EXTERNAL_HEADERS 
        include/common/*.h*
        include/${PLATFORM}/*.h*
    )

    add_library(${project_name} STATIC ${PLATFORM_SOURCES} ${COMMON_SOURCES} ${EXTERNAL_HEADERS})

    target_link_libraries(${project_name} ${DEPENDENCIES})

    target_include_directories(${project_name} PUBLIC 
        "${CMAKE_CURRENT_LIST_DIR}/include/common"
        "${CMAKE_CURRENT_LIST_DIR}/include/${PLATFORM}/"
    )
endfunction()

function(build_executable project_name)
    set(DEPENDENCIES ${ARGV1})

    update_sources()

    include_directories(
        source/
        source/common
        source/${PLATFORM}
    )

    add_executable(${project_name} WIN32 ${PLATFORM_SOURCES} ${COMMON_SOURCES})

    target_link_libraries(${project_name} ${DEPENDENCIES})

endfunction()