# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/shameerahmad/Desktop/City Landscape"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/shameerahmad/Desktop/City Landscape/build"

# Include any dependencies generated for this target.
include CMakeFiles/city_landscape.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/city_landscape.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/city_landscape.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/city_landscape.dir/flags.make

CMakeFiles/city_landscape.dir/src/main.cpp.o: CMakeFiles/city_landscape.dir/flags.make
CMakeFiles/city_landscape.dir/src/main.cpp.o: /Users/shameerahmad/Desktop/City\ Landscape/src/main.cpp
CMakeFiles/city_landscape.dir/src/main.cpp.o: CMakeFiles/city_landscape.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/shameerahmad/Desktop/City Landscape/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/city_landscape.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/city_landscape.dir/src/main.cpp.o -MF CMakeFiles/city_landscape.dir/src/main.cpp.o.d -o CMakeFiles/city_landscape.dir/src/main.cpp.o -c "/Users/shameerahmad/Desktop/City Landscape/src/main.cpp"

CMakeFiles/city_landscape.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/city_landscape.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/shameerahmad/Desktop/City Landscape/src/main.cpp" > CMakeFiles/city_landscape.dir/src/main.cpp.i

CMakeFiles/city_landscape.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/city_landscape.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/shameerahmad/Desktop/City Landscape/src/main.cpp" -o CMakeFiles/city_landscape.dir/src/main.cpp.s

CMakeFiles/city_landscape.dir/src/glad.c.o: CMakeFiles/city_landscape.dir/flags.make
CMakeFiles/city_landscape.dir/src/glad.c.o: /Users/shameerahmad/Desktop/City\ Landscape/src/glad.c
CMakeFiles/city_landscape.dir/src/glad.c.o: CMakeFiles/city_landscape.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/shameerahmad/Desktop/City Landscape/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/city_landscape.dir/src/glad.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/city_landscape.dir/src/glad.c.o -MF CMakeFiles/city_landscape.dir/src/glad.c.o.d -o CMakeFiles/city_landscape.dir/src/glad.c.o -c "/Users/shameerahmad/Desktop/City Landscape/src/glad.c"

CMakeFiles/city_landscape.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/city_landscape.dir/src/glad.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/shameerahmad/Desktop/City Landscape/src/glad.c" > CMakeFiles/city_landscape.dir/src/glad.c.i

CMakeFiles/city_landscape.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/city_landscape.dir/src/glad.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/shameerahmad/Desktop/City Landscape/src/glad.c" -o CMakeFiles/city_landscape.dir/src/glad.c.s

# Object files for target city_landscape
city_landscape_OBJECTS = \
"CMakeFiles/city_landscape.dir/src/main.cpp.o" \
"CMakeFiles/city_landscape.dir/src/glad.c.o"

# External object files for target city_landscape
city_landscape_EXTERNAL_OBJECTS =

city_landscape: CMakeFiles/city_landscape.dir/src/main.cpp.o
city_landscape: CMakeFiles/city_landscape.dir/src/glad.c.o
city_landscape: CMakeFiles/city_landscape.dir/build.make
city_landscape: /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.3.4.dylib
city_landscape: CMakeFiles/city_landscape.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/shameerahmad/Desktop/City Landscape/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable city_landscape"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/city_landscape.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/city_landscape.dir/build: city_landscape
.PHONY : CMakeFiles/city_landscape.dir/build

CMakeFiles/city_landscape.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/city_landscape.dir/cmake_clean.cmake
.PHONY : CMakeFiles/city_landscape.dir/clean

CMakeFiles/city_landscape.dir/depend:
	cd "/Users/shameerahmad/Desktop/City Landscape/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/shameerahmad/Desktop/City Landscape" "/Users/shameerahmad/Desktop/City Landscape" "/Users/shameerahmad/Desktop/City Landscape/build" "/Users/shameerahmad/Desktop/City Landscape/build" "/Users/shameerahmad/Desktop/City Landscape/build/CMakeFiles/city_landscape.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/city_landscape.dir/depend

