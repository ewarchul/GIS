cmake_minimum_required(VERSION 3.10)
project(BAGenerator)

set(CMAKE_CXX_STANDARD 14)

#set(LEMON_LIBRARY "C:/lemon1/")
#LINK_DIRECTORIES(${LEMON_LIBRARY}/lib/)

add_subdirectory(generator)
add_subdirectory(graph)
add_executable(BAGenerator main.cpp)

#target_include_directories(BAGenerator PRIVATE "${LEMON_LIBRARY}/include/")
target_link_libraries(BAGenerator sub::gen sub::graph)
#target_link_libraries(BAGenerator PUBLIC generator)
