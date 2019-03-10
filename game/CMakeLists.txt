cmake_minimum_required(VERSION 3.10)

# Enable folders grouping in IDE
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(game WIN32 source/main.cpp)
target_link_libraries(game utilities)