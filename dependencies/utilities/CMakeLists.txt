project(utilities)

file(GLOB PLATFORM_SOURCES 
    source/${PLATFORM}/*.cpp
    source/${PLATOFMR}/*.h)

file(GLOB INCLUDES include/*.h)

add_library(utilities STATIC ${PLATFORM_SOURCES} ${INCLUDES})

target_include_directories(utilities PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")