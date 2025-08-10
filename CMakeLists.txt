cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 20)
project(speedrun)


add_compile_options(-g -fsanitize=address)
add_link_options(-g -fsanitize=address)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB SRC_UI_El ${PROJECT_SOURCE_DIR}/src/UI_elements/*.cpp)
file(GLOB SRC_UI_T ${PROJECT_SOURCE_DIR}/src/UI_Tools/*.cpp)

add_executable(speedrun main.cpp ${SRC} ${SRC_UI_El} ${SRC_UI_T})

target_include_directories(speedrun PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(speedrun PUBLIC ${PROJECT_SOURCE_DIR}/raylib/src/include)


target_link_libraries(speedrun PUBLIC ${PROJECT_SOURCE_DIR}/raylib/src/libraylib.so)
target_precompile_headers(speedrun PUBLIC ${PROJECT_SOURCE_DIR}/src/stdafx.h)
