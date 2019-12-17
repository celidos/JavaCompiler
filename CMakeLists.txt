cmake_minimum_required(VERSION 3.0)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# SET (CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/clang++")

if(LINUX)
    message("")
    message(STATUS "LINUX DETECTED, choosing g++ compiler. If that's not true, please, check out CMakeLists.txt")
    message("")
else()
    message("")
    message(STATUS "MACOS DETECTED, choosing clang++ compiler. If that's not true, please, check out CMakeLists.txt")
    message("")
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++") # Dima, that's your place
endif()

SET (CMAKE_CXX_COMPILER  "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-deprecated-register")

project(javacompiler CXX)



find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(mc_parser
             src/mc_parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/mc_parser.tab.cc)
FLEX_TARGET (mc_lexer
             src/mc_lexer.l
             ${CMAKE_CURRENT_BINARY_DIR}/mc_lexer.yy.cc)



# TEST TEST -----------------------------------------------------------------
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
# TEST TEST -----------------------------------------------------------------

add_subdirectory(src/ast)
add_subdirectory(src/irt)
add_subdirectory(src/smart_graphviz)

ADD_FLEX_BISON_DEPENDENCY(mc_lexer mc_parser)

add_executable(javacompiler
    src/main.cpp
)

add_library(driver STATIC
    src/mc_driver.cpp
    ${FLEX_mc_lexer_OUTPUTS}
    ${BISON_mc_parser_OUTPUTS}
)
target_include_directories(driver PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} )

target_link_libraries(driver
    PUBLIC ast irt smart_graphviz
)

target_link_libraries(javacompiler
    PUBLIC driver
)

target_include_directories(javacompiler
    PRIVATE . ${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET javacompiler
    PROPERTY CXX_STANDARD 11)

message("Current binary dir: " ${CMAKE_CURRENT_BINARY_DIR})

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )


include(CTest)

enable_testing()

add_subdirectory(test)
# -------------------------------------------------------------------------------------------

