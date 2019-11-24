cmake_minimum_required(VERSION 3.0)

SET (CMAKE_CXX_COMPILER  "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register")

project(javacompiler CXX)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(mc_parser
             src/mc_parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/mc_parser.tab.cc)
FLEX_TARGET (mc_lexer
             src/mc_lexer.l
             ${CMAKE_CURRENT_BINARY_DIR}/mc_lexer.yy.cc)

add_subdirectory(src/ast)
add_subdirectory(src/smart_graphviz)

ADD_FLEX_BISON_DEPENDENCY(mc_lexer mc_parser)

add_executable(javacompiler
    src/main.cpp
    src/mc_driver.cpp

    ${FLEX_mc_lexer_OUTPUTS}
    ${BISON_mc_parser_OUTPUTS}
)

target_link_libraries(javacompiler
    PUBLIC ast
)

target_link_libraries(javacompiler
    PUBLIC smart_graphviz
)

target_include_directories(javacompiler
    PRIVATE . ${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET javacompiler
    PROPERTY CXX_STANDARD 11)

message("Current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})

# enable_testing()
# add_test(NAME basic
#         COMMAND ${CMAKE_SOURCE_DIR}/test/test0.pl
#         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
