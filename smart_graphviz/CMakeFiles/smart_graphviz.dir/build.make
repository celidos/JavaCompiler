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
CMAKE_SOURCE_DIR = /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler

# Include any dependencies generated for this target.
include smart_graphviz/CMakeFiles/smart_graphviz.dir/depend.make

# Include the progress variables for this target.
include smart_graphviz/CMakeFiles/smart_graphviz.dir/progress.make

# Include the compile flags for this target's objects.
include smart_graphviz/CMakeFiles/smart_graphviz.dir/flags.make

smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o: smart_graphviz/CMakeFiles/smart_graphviz.dir/flags.make
smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o: smart_graphviz/graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o"
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/smart_graphviz.dir/graph.cpp.o -c /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz/graph.cpp

smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smart_graphviz.dir/graph.cpp.i"
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz/graph.cpp > CMakeFiles/smart_graphviz.dir/graph.cpp.i

smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smart_graphviz.dir/graph.cpp.s"
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz/graph.cpp -o CMakeFiles/smart_graphviz.dir/graph.cpp.s

smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.requires:

.PHONY : smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.requires

smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.provides: smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.requires
	$(MAKE) -f smart_graphviz/CMakeFiles/smart_graphviz.dir/build.make smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.provides.build
.PHONY : smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.provides

smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.provides.build: smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o


# Object files for target smart_graphviz
smart_graphviz_OBJECTS = \
"CMakeFiles/smart_graphviz.dir/graph.cpp.o"

# External object files for target smart_graphviz
smart_graphviz_EXTERNAL_OBJECTS =

smart_graphviz/libsmart_graphviz.a: smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o
smart_graphviz/libsmart_graphviz.a: smart_graphviz/CMakeFiles/smart_graphviz.dir/build.make
smart_graphviz/libsmart_graphviz.a: smart_graphviz/CMakeFiles/smart_graphviz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsmart_graphviz.a"
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz && $(CMAKE_COMMAND) -P CMakeFiles/smart_graphviz.dir/cmake_clean_target.cmake
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smart_graphviz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
smart_graphviz/CMakeFiles/smart_graphviz.dir/build: smart_graphviz/libsmart_graphviz.a

.PHONY : smart_graphviz/CMakeFiles/smart_graphviz.dir/build

smart_graphviz/CMakeFiles/smart_graphviz.dir/requires: smart_graphviz/CMakeFiles/smart_graphviz.dir/graph.cpp.o.requires

.PHONY : smart_graphviz/CMakeFiles/smart_graphviz.dir/requires

smart_graphviz/CMakeFiles/smart_graphviz.dir/clean:
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz && $(CMAKE_COMMAND) -P CMakeFiles/smart_graphviz.dir/cmake_clean.cmake
.PHONY : smart_graphviz/CMakeFiles/smart_graphviz.dir/clean

smart_graphviz/CMakeFiles/smart_graphviz.dir/depend:
	cd /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz /mnt/3B1D7BDC2D2641B0/Documents/GIT/JavaCompiler/smart_graphviz/CMakeFiles/smart_graphviz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : smart_graphviz/CMakeFiles/smart_graphviz.dir/depend
