project(graph)
# set sources
#file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")



set(HEADERS
        include/graph/Graph.h
       # include/graph/GraphImplLemon.h
        include/graph/Node.h
       # include/graph/NodeImplLemon.h
        include/graph/GraphImpOur.h
        include/graph/NodeImpOur.h
)

set(SOURCES
      #  src/GraphImplLemon.cpp
        src/GraphImpOur.cpp
        src/NodeImpOur.cpp
        ${HEADERS}
        )


#set(LEMON_LIBRARY "C:/lemon1/")

#LINK_DIRECTORIES(${LEMON_LIBRARY}/lib/)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::graph ALIAS ${PROJECT_NAME})

#target_include_directories(graph PUBLIC "${LEMON_LIBRARY}/include/")

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        )




#target_link_libraries(graph lemon.lib)