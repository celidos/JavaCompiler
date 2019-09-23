set(HEADER_FILES graph.h)
set(SOURCE_FILES graph.cpp)
add_library(smart_graphviz STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(GraphvizWarmup::smart_graphviz ALIAS smart_graphviz)
