macro(initialize_pipeline)
    if(MSVC)
        if(MSVC_VERSION GREATER 1700)
            set(COMPILER_VERSION "12")
        elseif(MSVC_VERSION GREATER 1600)
            set(COMPILER_VERSION "11")
        endif()

        if("${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore")
            set(PLATFORM UWP)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await /DUWP /DPLATFORM_MSFT")
        else()
            set(PLATFORM WIN32)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DWIN32 /DPLATFORM_MSFT")
        endif()
    else()
        if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
            set(PLATFORM linux)
            set(LINUX 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DPLATFORM_POSIX")
        elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
            set(PLATFORM osx)
            set(OSX 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOSX -DPLATFORM_POSIX")
            set(CMAKE_APPLE_SILICON_PROCESSOR arm64)
        elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
            set(PLATFORM android)
            set(ANDROID 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANDROID")
        elseif(${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
            set(PLATFORM ios)
            set(IOS 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIOS")
        elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
            set(PLATFORM emscripten)
            set(EMSCRIPTEN 1)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN")
        endif()
    endif()

    # Enable folders grouping in IDE
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    if(USE_HTTP)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_HTTP")
    endif()
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
    set(ASSETS ${ARGV2})

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

    if(ANDROID)
        add_library(xpengine SHARED ${COMMON_SOURCES} ${PLATFORM_SOURCES} ${PLATFORM_COMMON_SOURCES} ${RESOURCES})
        target_link_libraries(xpengine ${DEPENDENCIES})
    
        set_property(TARGET xpengine PROPERTY CXX_STANDARD 17)
        set_property(TARGET xpengine PROPERTY CXX_STANDARD_REQUIRED ON)
    elseif(EMSCRIPTEN)
        set(CMAKE_EXECUTABLE_SUFFIX ".html")
        set(LINK_OPTIONS ${LINK_OPTIONS} -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sNO_EXIT_RUNTIME=0 -sASSERTIONS=1 -oindex.html)
        add_executable(${project_name} WIN32 ${COMMON_SOURCES} ${PLATFORM_SOURCES} ${PLATFORM_COMMON_SOURCES} ${RESOURCES})
        target_link_libraries(${project_name} ${DEPENDENCIES} ${LINK_OPTIONS})

        set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
        set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
    else()
        add_executable(${project_name} WIN32 ${COMMON_SOURCES} ${PLATFORM_SOURCES} ${PLATFORM_COMMON_SOURCES} ${RESOURCES})
        target_link_libraries(${project_name} ${DEPENDENCIES})

        set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 17)
        set_property(TARGET ${project_name} PROPERTY CXX_STANDARD_REQUIRED ON)
    endif()

endfunction()

function (copy_assets)
    if(MSVC)
        message(STATUS "Preparing to copy MSVC resources")
        set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/assets")
    elseif(ANDROID)
        message(STATUS "Preparing to copy android resources")
        set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/platforms/android/app/src/main/assets")
    else()
        message(STATUS "Preparing to copy other platform resources")
        set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/assets")
    endif()
    if(EXISTS "${COMMON_ASSETS_DIRECTORY}" AND IS_DIRECTORY "${COMMON_ASSETS_DIRECTORY}")
        file(GLOB_RECURSE COMMON_ASSETS_FILES LIST_DIRECTORIES false RELATIVE ${COMMON_ASSETS_DIRECTORY}
            ${COMMON_ASSETS_DIRECTORY}/*.*
        )
        foreach(ASSET_FILE ${COMMON_ASSETS_FILES})
            # get_filename_component(ASSET_FILE_NAME ${ASSET_FILE} NAME)
            message(STATUS "Copying common asset: ${ASSET_FILE}")
            configure_file("${COMMON_ASSETS_DIRECTORY}/${ASSET_FILE}" "${OUTPUT_DIRECTORY}/${ASSET_FILE}" COPYONLY)  
        endforeach()
        
    endif()
    if(EXISTS "${PLATFORM_ASSETS_DIRECTORY}" AND IS_DIRECTORY "${PLATFORM_ASSETS_DIRECTORY}")
        file(GLOB_RECURSE PLATFORM_ASSETS_FILES LIST_DIRECTORIES false RELATIVE ${PLATFORM_ASSETS_DIRECTORY}
            ${PLATFORM_ASSETS_DIRECTORY}/*.*
        )
        foreach(ASSET_FILE ${PLATFORM_ASSETS_FILES})
            # get_filename_component(ASSET_FILE_NAME ${ASSET_FILE} NAME)
            message(STATUS "Copying platform asset: ${ASSET_FILE}")
            configure_file("${PLATFORM_ASSETS_DIRECTORY}/${ASSET_FILE}" "${OUTPUT_DIRECTORY}/${ASSET_FILE}" COPYONLY)  
        endforeach()
        
    endif()
endfunction()