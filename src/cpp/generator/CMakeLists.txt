project(generator)
# set sources
#file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

set(HEADERS
        include/generator/BAModel.h
        include/generator/Bucket.h
        src/RollTree.cpp include/generator/RollTree.h)

set(SOURCES
        src/BAModel.cc
        ${HEADERS}
        src/Bucket.cc
        include/generator/PreferentialAttachement.h src/RollTree.cpp include/generator/RollTree.h include/generator/Random.h include/generator/RandomImp.hpp)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::gen ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} sub::graph)