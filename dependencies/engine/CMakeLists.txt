project(engine)

set(DEPENDENCIES
    utilities
)

file(GLOB PLATFORM_SOURCES
    source/common/*.cpp
    source/common/*.h
    source/${PLATFORM}/*.cpp
    source/${PLATFORM}/*.h
)

file(GLOB INCLUDES include/*.h)

add_library(engine STATIC ${PLATFORM_SOURCES} ${INCLUDES})
target_link_libraries(engine ${DEPENDENCIES})

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")