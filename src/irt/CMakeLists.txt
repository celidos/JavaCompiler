cmake_minimum_required(VERSION 3.1)

# message("Current source dir: " ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(irt STATIC ${SOURCES} ${HEADERS})

target_include_directories(irt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::irt ALIAS irt)
