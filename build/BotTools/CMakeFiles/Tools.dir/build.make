# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gleb/CXX/BotDialog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gleb/CXX/BotDialog/build

# Include any dependencies generated for this target.
include BotTools/CMakeFiles/Tools.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include BotTools/CMakeFiles/Tools.dir/compiler_depend.make

# Include the progress variables for this target.
include BotTools/CMakeFiles/Tools.dir/progress.make

# Include the compile flags for this target's objects.
include BotTools/CMakeFiles/Tools.dir/flags.make

BotTools/CMakeFiles/Tools.dir/Button.cpp.o: BotTools/CMakeFiles/Tools.dir/flags.make
BotTools/CMakeFiles/Tools.dir/Button.cpp.o: ../BotTools/Button.cpp
BotTools/CMakeFiles/Tools.dir/Button.cpp.o: BotTools/CMakeFiles/Tools.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gleb/CXX/BotDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object BotTools/CMakeFiles/Tools.dir/Button.cpp.o"
	cd /home/gleb/CXX/BotDialog/build/BotTools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT BotTools/CMakeFiles/Tools.dir/Button.cpp.o -MF CMakeFiles/Tools.dir/Button.cpp.o.d -o CMakeFiles/Tools.dir/Button.cpp.o -c /home/gleb/CXX/BotDialog/BotTools/Button.cpp

BotTools/CMakeFiles/Tools.dir/Button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tools.dir/Button.cpp.i"
	cd /home/gleb/CXX/BotDialog/build/BotTools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gleb/CXX/BotDialog/BotTools/Button.cpp > CMakeFiles/Tools.dir/Button.cpp.i

BotTools/CMakeFiles/Tools.dir/Button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tools.dir/Button.cpp.s"
	cd /home/gleb/CXX/BotDialog/build/BotTools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gleb/CXX/BotDialog/BotTools/Button.cpp -o CMakeFiles/Tools.dir/Button.cpp.s

# Object files for target Tools
Tools_OBJECTS = \
"CMakeFiles/Tools.dir/Button.cpp.o"

# External object files for target Tools
Tools_EXTERNAL_OBJECTS =

BotTools/libTools.so: BotTools/CMakeFiles/Tools.dir/Button.cpp.o
BotTools/libTools.so: BotTools/CMakeFiles/Tools.dir/build.make
BotTools/libTools.so: BotTools/CMakeFiles/Tools.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gleb/CXX/BotDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libTools.so"
	cd /home/gleb/CXX/BotDialog/build/BotTools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tools.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
BotTools/CMakeFiles/Tools.dir/build: BotTools/libTools.so
.PHONY : BotTools/CMakeFiles/Tools.dir/build

BotTools/CMakeFiles/Tools.dir/clean:
	cd /home/gleb/CXX/BotDialog/build/BotTools && $(CMAKE_COMMAND) -P CMakeFiles/Tools.dir/cmake_clean.cmake
.PHONY : BotTools/CMakeFiles/Tools.dir/clean

BotTools/CMakeFiles/Tools.dir/depend:
	cd /home/gleb/CXX/BotDialog/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gleb/CXX/BotDialog /home/gleb/CXX/BotDialog/BotTools /home/gleb/CXX/BotDialog/build /home/gleb/CXX/BotDialog/build/BotTools /home/gleb/CXX/BotDialog/build/BotTools/CMakeFiles/Tools.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : BotTools/CMakeFiles/Tools.dir/depend
