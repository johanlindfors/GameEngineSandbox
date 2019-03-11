project(utilities)

#STRING(TOLOWER "${PLATFORM}" PLATFORM_LOWER)

file(GLOB PLATFORM_SOURCES source/${PLATFORM}/*.cpp)

add_library(utilities STATIC ${PLATFORM_SOURCES} include/test.h)

target_include_directories(utilities PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")