# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build"

# Include any dependencies generated for this target.
include AST/CMakeFiles/AST.dir/depend.make

# Include the progress variables for this target.
include AST/CMakeFiles/AST.dir/progress.make

# Include the compile flags for this target's objects.
include AST/CMakeFiles/AST.dir/flags.make

AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o: AST/CMakeFiles/AST.dir/flags.make
AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o: ../AST/Expression/ExpressionBase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o -c "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionBase.cpp"

AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.i"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionBase.cpp" > CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.i

AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.s"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionBase.cpp" -o CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.s

AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.requires:

.PHONY : AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.requires

AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.provides: AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.requires
	$(MAKE) -f AST/CMakeFiles/AST.dir/build.make AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.provides.build
.PHONY : AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.provides

AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.provides.build: AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o


AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o: AST/CMakeFiles/AST.dir/flags.make
AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o: ../AST/Expression/ExpressionBinaryOp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o -c "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionBinaryOp.cpp"

AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.i"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionBinaryOp.cpp" > CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.i

AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.s"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionBinaryOp.cpp" -o CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.s

AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.requires:

.PHONY : AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.requires

AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.provides: AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.requires
	$(MAKE) -f AST/CMakeFiles/AST.dir/build.make AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.provides.build
.PHONY : AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.provides

AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.provides.build: AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o


AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o: AST/CMakeFiles/AST.dir/flags.make
AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o: ../AST/Expression/ExpressionInt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o -c "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionInt.cpp"

AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.i"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionInt.cpp" > CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.i

AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.s"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST/Expression/ExpressionInt.cpp" -o CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.s

AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.requires:

.PHONY : AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.requires

AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.provides: AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.requires
	$(MAKE) -f AST/CMakeFiles/AST.dir/build.make AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.provides.build
.PHONY : AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.provides

AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.provides.build: AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o


# Object files for target AST
AST_OBJECTS = \
"CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o" \
"CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o" \
"CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o"

# External object files for target AST
AST_EXTERNAL_OBJECTS =

AST/libAST.a: AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o
AST/libAST.a: AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o
AST/libAST.a: AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o
AST/libAST.a: AST/CMakeFiles/AST.dir/build.make
AST/libAST.a: AST/CMakeFiles/AST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libAST.a"
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && $(CMAKE_COMMAND) -P CMakeFiles/AST.dir/cmake_clean_target.cmake
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AST.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
AST/CMakeFiles/AST.dir/build: AST/libAST.a

.PHONY : AST/CMakeFiles/AST.dir/build

AST/CMakeFiles/AST.dir/requires: AST/CMakeFiles/AST.dir/Expression/ExpressionBase.cpp.o.requires
AST/CMakeFiles/AST.dir/requires: AST/CMakeFiles/AST.dir/Expression/ExpressionBinaryOp.cpp.o.requires
AST/CMakeFiles/AST.dir/requires: AST/CMakeFiles/AST.dir/Expression/ExpressionInt.cpp.o.requires

.PHONY : AST/CMakeFiles/AST.dir/requires

AST/CMakeFiles/AST.dir/clean:
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" && $(CMAKE_COMMAND) -P CMakeFiles/AST.dir/cmake_clean.cmake
.PHONY : AST/CMakeFiles/AST.dir/clean

AST/CMakeFiles/AST.dir/depend:
	cd "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src" "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/AST" "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build" "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST" "/home/sofya/Homework/7 семестр/ABBYY: компиляторы/JavaCompiler/src/build/AST/CMakeFiles/AST.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : AST/CMakeFiles/AST.dir/depend

