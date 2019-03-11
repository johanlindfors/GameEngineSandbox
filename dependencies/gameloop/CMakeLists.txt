project(gameloop)

file(GLOB PLATFORM_SOURCES 
    source/${PLATFORM}/*.cpp
    source/${PLATOFMR}/*.h)

file(GLOB INCLUDES include/*.h)

add_library(gameloop STATIC ${PLATFORM_SOURCES} ${INCLUDES})
target_link_libraries(gameloop utilities)

target_include_directories(gameloop PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")