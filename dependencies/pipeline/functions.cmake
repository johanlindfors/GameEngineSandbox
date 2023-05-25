macro(initialize_pipeline)
    if(MSVC)

        if(MSVC_VERSION GREATER 1700)
            set(COMPILER_VERSION "12")
        elseif(MSVC_VERSION GREATER 1600)
            set(COMPILER_VERSION "11")
        endif()

        if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
            set(PLATFORM UWP)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await /DUWP")
        else()
            set(PLATFORM WIN32)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32")
        endif()
    else()
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            set(PLATFORM linux)
            set(LINUX 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX")
        else()
            set(PLATFORM osx)
            set(OSX 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOSX")
            set(CMAKE_APPLE_SILICON_PROCESSOR arm64)
        endif()
    endif()

    # Enable folders grouping in IDE
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endmacro()

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
    else()
        file(GLOB PLATFORM_COMMON_SOURCES
            source/posix/*.cpp
            source/posix/*.h*
        )
    endif()
    source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${PLATFORM_COMMON_SOURCES})

endmacro()

function(build_library project_name)
    set(DEPENDENCIES ${ARGV1})
    set(SHARED ${ARGV2})

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

    if(SHARED)
        add_library(${project_name} SHARED ${PLATFORM_SOURCES} ${COMMON_SOURCES} ${PLATFORM_COMMON_SOURCES} ${EXTERNAL_HEADERS} ${EXTERNAL_PLATFORM_COMMON_HEADERS})
    else()
        add_library(${project_name} STATIC ${PLATFORM_SOURCES} ${COMMON_SOURCES} ${PLATFORM_COMMON_SOURCES} ${EXTERNAL_HEADERS} ${EXTERNAL_PLATFORM_COMMON_HEADERS})
    endif()

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

function (copy_resources)
    if(MSVC)
        set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources")
    else()
        set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/resources")
    endif()
    if(EXISTS "${COMMON_RESOURCES_DIRECTORY}" AND IS_DIRECTORY "${COMMON_RESOURCES_DIRECTORY}")
        message(STATUS "Found common resources")
        add_custom_target(copy_common_resources ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${COMMON_RESOURCES_DIRECTORY} 
            "${OUTPUT_DIRECTORY}"
            COMMENT "Copying common resources to binary directory: ${OUTPUT_DIRECTORY}")
    endif()
    if(EXISTS "${PLATFORM_RESOURCES_DIRECTORY}" AND IS_DIRECTORY "${PLATFORM_RESOURCES_DIRECTORY}")
        message(STATUS "Found platform specific resources")
        add_custom_target(copy_platform_resources ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${PLATFORM_RESOURCES_DIRECTORY} 
            "${OUTPUT_DIRECTORY}"
            COMMENT "Copying platform specific resources to binary directory: ${OUTPUT_DIRECTORY}")
    endif()
endfunction()