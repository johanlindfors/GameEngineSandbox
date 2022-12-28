add_library(stb src/stb.cpp)

target_include_directories(stb SYSTEM PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories(stb
	INTERFACE SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/include"
)