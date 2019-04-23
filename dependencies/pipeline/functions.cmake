macro(update_sources)
    file(GLOB_RECURSE COMMON_SOURCES
        source/common/*.cpp
        source/common/*.h*
    )
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${COMMON_SOURCES})
    
    file(GLOB PLATFORM_SOURCES
        source/${PLATFORM}/*.cpp
        source/${PLATFORM}/*.h*
    )
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PLATFORM_SOURCES})

    if(UWP OR WIN32)
        file(GLOB PLATFORM_COMMON_SOURCES
            source/msft/*.cpp
            source/msft/*.h*
        )
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PLATFORM_COMMON_SOURCES})
    else()
        message(STATUS "posix")
    endif()

endmacro()

function(build_library project_name)
    set(DEPENDENCIES ${ARGV1})

    update_sources()

    file(GLOB_RECURSE EXTERNAL_HEADERS 
        include/common/*.h*
        include/${PLATFORM}/*.h*
    )
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${EXTERNAL_HEADERS})

    set(LIBRARY_INCLUDE_DIRECTORIES 
        include/common
        include/${PLATFORM}
    )

    if(UWP OR WIN32)
        message(STATUS "msft")
        file(GLOB_RECURSE EXTERNAL_PLATFORM_COMMON_HEADERS 
            include/msft/*.h*
        )
        list(APPEND LIBRARY_INCLUDE_DIRECTORIES
            include/msft
        )
    else()
        file(GLOB_RECURSE EXTERNAL_PLATFORM_COMMON_HEADERS 
            include/posix/*.h*
        )   
        list(APPEND LIBRARY_INCLUDE_DIRECTORIES
            include/posix
        )
    endif()
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${EXTERNAL_PLATFORM_COMMON_HEADERS})
        
    add_library(${project_name} STATIC ${PLATFORM_SOURCES} ${COMMON_SOURCES} ${PLATFORM_COMMON_SOURCES} ${EXTERNAL_HEADERS} ${EXTERNAL_PLATFORM_COMMON_HEADERS})

    target_link_libraries(${project_name} ${DEPENDENCIES})

    target_include_directories(${project_name} PUBLIC 
       ${LIBRARY_INCLUDE_DIRECTORIES}
    )
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
endfunction()

function(build_executable project_name)
    set(DEPENDENCIES ${ARGV1})
    set(RESOURCES ${ARGV2})

    update_sources()

    set(EXECUTABLE_INCLUDE_DIRECTORIES 
        source/
        source/common
        source/${PLATFORM}
    )

    if(UWP OR WIN32)
        list(APPEND EXECUTABLE_INCLUDE_DIRECTORIES
            source/msft
        )
    else()
        list(APPEND EXECUTABLE_INCLUDE_DIRECTORIES
            source/posix
        )
    endif()

    include_directories(
        ${EXECUTABLE_INCLUDE_DIRECTORIES}
    )

    add_executable(${project_name} WIN32 ${COMMON_SOURCES} ${PLATFORM_SOURCES} ${PLATFORM_COMMON_SOURCES} ${RESOURCES})

    target_link_libraries(${project_name} ${DEPENDENCIES})
    
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
endfunction()