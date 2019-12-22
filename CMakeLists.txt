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

# SET (CMAKE_CXX_COMPILER  "/usr/bin/clang++")
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
    PUBLIC driver)


target_include_directories(javacompiler
    PRIVATE . ${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET javacompiler
    PROPERTY CXX_STANDARD 11)

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

# -----------------------------------------------------------------------

include(CTest)

enable_testing()

# -----------------------------------------------------------------------

add_test(NAME test_two_plus_two COMMAND  "./../run_test.sh"
                                         "./samples/good_samples/two_plus_two.java"
                                         "./output/two_plus_two"
                                         0)
add_test(NAME test_binary_search COMMAND "./../run_test.sh"
                                         "./samples/good_samples/BinarySearch.java"
                                         "./output/BinarySearch"
                                         0)
add_test(NAME test_binary_tree COMMAND "./../run_test.sh"
                                       "./samples/good_samples/BinaryTree.java"
                                       "./output/BinaryTree"
                                       0)
add_test(NAME test_bubble_sort COMMAND "./../run_test.sh"
                                       "./samples/good_samples/BubbleSort.java"
                                       "./output/BubbleSort"
                                       0)
add_test(NAME test_factorial COMMAND "./../run_test.sh"
                                       "./samples/good_samples/Factorial.java"
                                       "./output/Factorial"
                                       0)
add_test(NAME test_linear_search COMMAND "./../run_test.sh"
                                       "./samples/good_samples/LinearSearch.java"
                                       "./output/LinearSearch"
                                       0)
add_test(NAME test_linked_list COMMAND "./../run_test.sh"
                                       "./samples/good_samples/LinkedList.java"
                                       "./output/LinearSearch"
                                       0)
add_test(NAME test_quick_sort COMMAND "./../run_test.sh"
                                       "./samples/good_samples/QuickSort.java"
                                       "./output/QuickSort"
                                       0)
add_test(NAME test_tree_visitor COMMAND "./../run_test.sh"
                                       "./samples/good_samples/TreeVisitor.java"
                                       "./output/TreeVisitor"
                                       0)

add_test(NAME test_my_test COMMAND "./../run_test.sh"
                                       "./samples/good_samples/my_test.java"
                                       "./output/LinearSearch"
                                       0)

# tests which cannot compile ----------------------------------------------------------------------

add_test(NAME test_lc_1 COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/LC_1.java"
                                 "."
                                 3)
add_test(NAME test_my1 COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/My1.java"
                                 "."
                                 4)
add_test(NAME test_tc_1a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_1a.java"
                                 "."
                                 4)
add_test(NAME test_tc_2 COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_2.java"
                                 "."
                                 4)
add_test(NAME test_tc_2a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_2a.java"
                                 "."
                                 4)
add_test(NAME test_tc_3a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_3a.java"
                                 "."
                                 4)
add_test(NAME test_tc_3a_1 COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_3a_1.java"
                                 "."
                                 4)
add_test(NAME test_tc_3a_2 COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_3a_2.java"
                                 "."
                                 4)
add_test(NAME test_tc_3b COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_3b.java"
                                 "."
                                 4)
add_test(NAME test_tc_4a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_4a.java"
                                 "."
                                 4)
add_test(NAME test_tc_4b COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_4b.java"
                                 "."
                                 4)
add_test(NAME test_tc_5a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_5a.java"
                                 "."
                                 4)
add_test(NAME test_tc_6a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_6a.java"
                                 "."
                                 4)
add_test(NAME test_tc_7b COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_7b.java"
                                 "."
                                 4)
add_test(NAME test_tc_7c COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_7c.java"
                                 "."
                                 4)
add_test(NAME test_tc_8a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_8a.java"
                                 "."
                                 4)
add_test(NAME test_tc_9a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_9a.java"
                                 "."
                                 3)
add_test(NAME test_tc_9a_2 COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_9a_2.java"
                                 "."
                                 3)
add_test(NAME test_tc_11a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_11a.java"
                                 "."
                                 4)
add_test(NAME test_tc_12b COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_12b.java"
                                 "."
                                 4)
add_test(NAME test_tc_13a COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_13a.java"
                                 "."
                                 4)
add_test(NAME test_tc_13b COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_13b.java"
                                 "."
                                 4)
add_test(NAME test_tc_13c COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_13c.java"
                                 "."
                                 4)
add_test(NAME test_tc_13d_optional COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_13d_optional.java"
                                 "."
                                 4)
add_test(NAME test_tc_bonus COMMAND "./../run_test.sh"
                                 "./samples/bad_samples/TC_bonus1.java"
                                 "."
                                 4)

# INSTRUCTION: if you will add some google tests in future, just uncomment this example
#
# add_executable(
#    unit_tests
#    main.cpp
#    )
#
#
# target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
# target_link_libraries(
#    unit_tests
#    gtest_main
#    ast
#    driver
#    )
#
#
# add_test(
#  NAME
#    test_example
#  COMMAND
#    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
#  )
