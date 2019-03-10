project(utilities)

include_directories(include)

add_library(utilities STATIC source/test.cpp include/test.h)

target_include_directories(utilities PUBLIC "$<INSTALL_INTERFACE:include>")
target_include_directories(utilities PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")