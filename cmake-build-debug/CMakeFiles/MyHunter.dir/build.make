# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /snap/clion/175/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/175/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/clement/Delivery/MyHunter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/clement/Delivery/MyHunter/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MyHunter.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/MyHunter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyHunter.dir/flags.make

CMakeFiles/MyHunter.dir/main.c.o: CMakeFiles/MyHunter.dir/flags.make
CMakeFiles/MyHunter.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/clement/Delivery/MyHunter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MyHunter.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MyHunter.dir/main.c.o -c /home/clement/Delivery/MyHunter/main.c

CMakeFiles/MyHunter.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyHunter.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/clement/Delivery/MyHunter/main.c > CMakeFiles/MyHunter.dir/main.c.i

CMakeFiles/MyHunter.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyHunter.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/clement/Delivery/MyHunter/main.c -o CMakeFiles/MyHunter.dir/main.c.s

# Object files for target MyHunter
MyHunter_OBJECTS = \
"CMakeFiles/MyHunter.dir/main.c.o"

# External object files for target MyHunter
MyHunter_EXTERNAL_OBJECTS =

MyHunter: CMakeFiles/MyHunter.dir/main.c.o
MyHunter: CMakeFiles/MyHunter.dir/build.make
MyHunter: CMakeFiles/MyHunter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/clement/Delivery/MyHunter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MyHunter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyHunter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyHunter.dir/build: MyHunter
.PHONY : CMakeFiles/MyHunter.dir/build

CMakeFiles/MyHunter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyHunter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyHunter.dir/clean

CMakeFiles/MyHunter.dir/depend:
	cd /home/clement/Delivery/MyHunter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/clement/Delivery/MyHunter /home/clement/Delivery/MyHunter /home/clement/Delivery/MyHunter/cmake-build-debug /home/clement/Delivery/MyHunter/cmake-build-debug /home/clement/Delivery/MyHunter/cmake-build-debug/CMakeFiles/MyHunter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyHunter.dir/depend

