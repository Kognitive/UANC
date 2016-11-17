# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build

# Include any dependencies generated for this target.
include examples/window_usage/CMakeFiles/window_usage.dir/depend.make

# Include the progress variables for this target.
include examples/window_usage/CMakeFiles/window_usage.dir/progress.make

# Include the compile flags for this target's objects.
include examples/window_usage/CMakeFiles/window_usage.dir/flags.make

examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o: examples/window_usage/CMakeFiles/window_usage.dir/flags.make
examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o: /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/window_usage/window_usage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/window_usage.dir/window_usage.cpp.o -c /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/window_usage/window_usage.cpp

examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/window_usage.dir/window_usage.cpp.i"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/window_usage/window_usage.cpp > CMakeFiles/window_usage.dir/window_usage.cpp.i

examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/window_usage.dir/window_usage.cpp.s"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/window_usage/window_usage.cpp -o CMakeFiles/window_usage.dir/window_usage.cpp.s

examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.requires:
.PHONY : examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.requires

examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.provides: examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.requires
	$(MAKE) -f examples/window_usage/CMakeFiles/window_usage.dir/build.make examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.provides.build
.PHONY : examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.provides

examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.provides.build: examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o

# Object files for target window_usage
window_usage_OBJECTS = \
"CMakeFiles/window_usage.dir/window_usage.cpp.o"

# External object files for target window_usage
window_usage_EXTERNAL_OBJECTS =

examples/window_usage/window_usage: examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o
examples/window_usage/window_usage: examples/window_usage/CMakeFiles/window_usage.dir/build.make
examples/window_usage/window_usage: libAquila.a
examples/window_usage/window_usage: lib/libOoura_fft.a
examples/window_usage/window_usage: examples/window_usage/CMakeFiles/window_usage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable window_usage"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/window_usage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/window_usage/CMakeFiles/window_usage.dir/build: examples/window_usage/window_usage
.PHONY : examples/window_usage/CMakeFiles/window_usage.dir/build

examples/window_usage/CMakeFiles/window_usage.dir/requires: examples/window_usage/CMakeFiles/window_usage.dir/window_usage.cpp.o.requires
.PHONY : examples/window_usage/CMakeFiles/window_usage.dir/requires

examples/window_usage/CMakeFiles/window_usage.dir/clean:
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage && $(CMAKE_COMMAND) -P CMakeFiles/window_usage.dir/cmake_clean.cmake
.PHONY : examples/window_usage/CMakeFiles/window_usage.dir/clean

examples/window_usage/CMakeFiles/window_usage.dir/depend:
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/window_usage /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/window_usage/CMakeFiles/window_usage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/window_usage/CMakeFiles/window_usage.dir/depend

