cmake_minimum_required(VERSION 3.10)
project(GraphvizWarmup)

set(CMAKE_CXX_STANDARD 11)

add_executable(GraphvizWarmup main.cpp)

include_directories(smart_graphviz)
add_subdirectory(smart_graphviz)
add_subdirectory(Google_tests)
target_link_libraries(GraphvizWarmup PRIVATE GraphvizWarmup::smart_graphviz)
