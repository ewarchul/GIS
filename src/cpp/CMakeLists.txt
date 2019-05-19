cmake_minimum_required(VERSION 3.10)
project(BAGenerator)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(generator)
add_subdirectory(graph)
add_executable(BAGenerator main.cpp)

target_link_libraries(BAGenerator sub::gen sub::graph)