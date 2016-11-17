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
include examples/triangle_generator/CMakeFiles/triangle_generator.dir/depend.make

# Include the progress variables for this target.
include examples/triangle_generator/CMakeFiles/triangle_generator.dir/progress.make

# Include the compile flags for this target's objects.
include examples/triangle_generator/CMakeFiles/triangle_generator.dir/flags.make

examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o: examples/triangle_generator/CMakeFiles/triangle_generator.dir/flags.make
examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o: /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/triangle_generator/triangle_generator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o -c /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/triangle_generator/triangle_generator.cpp

examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangle_generator.dir/triangle_generator.cpp.i"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/triangle_generator/triangle_generator.cpp > CMakeFiles/triangle_generator.dir/triangle_generator.cpp.i

examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangle_generator.dir/triangle_generator.cpp.s"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/triangle_generator/triangle_generator.cpp -o CMakeFiles/triangle_generator.dir/triangle_generator.cpp.s

examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.requires:
.PHONY : examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.requires

examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.provides: examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.requires
	$(MAKE) -f examples/triangle_generator/CMakeFiles/triangle_generator.dir/build.make examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.provides.build
.PHONY : examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.provides

examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.provides.build: examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o

# Object files for target triangle_generator
triangle_generator_OBJECTS = \
"CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o"

# External object files for target triangle_generator
triangle_generator_EXTERNAL_OBJECTS =

examples/triangle_generator/triangle_generator: examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o
examples/triangle_generator/triangle_generator: examples/triangle_generator/CMakeFiles/triangle_generator.dir/build.make
examples/triangle_generator/triangle_generator: libAquila.a
examples/triangle_generator/triangle_generator: lib/libOoura_fft.a
examples/triangle_generator/triangle_generator: examples/triangle_generator/CMakeFiles/triangle_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable triangle_generator"
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/triangle_generator/CMakeFiles/triangle_generator.dir/build: examples/triangle_generator/triangle_generator
.PHONY : examples/triangle_generator/CMakeFiles/triangle_generator.dir/build

examples/triangle_generator/CMakeFiles/triangle_generator.dir/requires: examples/triangle_generator/CMakeFiles/triangle_generator.dir/triangle_generator.cpp.o.requires
.PHONY : examples/triangle_generator/CMakeFiles/triangle_generator.dir/requires

examples/triangle_generator/CMakeFiles/triangle_generator.dir/clean:
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator && $(CMAKE_COMMAND) -P CMakeFiles/triangle_generator.dir/cmake_clean.cmake
.PHONY : examples/triangle_generator/CMakeFiles/triangle_generator.dir/clean

examples/triangle_generator/CMakeFiles/triangle_generator.dir/depend:
	cd /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/examples/triangle_generator /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/triangle_generator/CMakeFiles/triangle_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/triangle_generator/CMakeFiles/triangle_generator.dir/depend

