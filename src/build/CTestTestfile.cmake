# CMake generated Testfile for 
# Source directory: /home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src
# Build directory: /home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(basic "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/test/test0.pl")
set_tests_properties(basic PROPERTIES  WORKING_DIRECTORY "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build")
subdirs("AST")
