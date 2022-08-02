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
include ReviewBot/CMakeFiles/ReviewBot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ReviewBot/CMakeFiles/ReviewBot.dir/compiler_depend.make

# Include the progress variables for this target.
include ReviewBot/CMakeFiles/ReviewBot.dir/progress.make

# Include the compile flags for this target's objects.
include ReviewBot/CMakeFiles/ReviewBot.dir/flags.make

ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o: ReviewBot/CMakeFiles/ReviewBot.dir/flags.make
ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o: ../ReviewBot/ReviewBot.cpp
ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o: ReviewBot/CMakeFiles/ReviewBot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gleb/CXX/BotDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o"
	cd /home/gleb/CXX/BotDialog/build/ReviewBot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o -MF CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o.d -o CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o -c /home/gleb/CXX/BotDialog/ReviewBot/ReviewBot.cpp

ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ReviewBot.dir/ReviewBot.cpp.i"
	cd /home/gleb/CXX/BotDialog/build/ReviewBot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gleb/CXX/BotDialog/ReviewBot/ReviewBot.cpp > CMakeFiles/ReviewBot.dir/ReviewBot.cpp.i

ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ReviewBot.dir/ReviewBot.cpp.s"
	cd /home/gleb/CXX/BotDialog/build/ReviewBot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gleb/CXX/BotDialog/ReviewBot/ReviewBot.cpp -o CMakeFiles/ReviewBot.dir/ReviewBot.cpp.s

# Object files for target ReviewBot
ReviewBot_OBJECTS = \
"CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o"

# External object files for target ReviewBot
ReviewBot_EXTERNAL_OBJECTS =

ReviewBot/libReviewBot.so: ReviewBot/CMakeFiles/ReviewBot.dir/ReviewBot.cpp.o
ReviewBot/libReviewBot.so: ReviewBot/CMakeFiles/ReviewBot.dir/build.make
ReviewBot/libReviewBot.so: BotTools/libTools.so
ReviewBot/libReviewBot.so: ReviewBot/Event/libEvent.so
ReviewBot/libReviewBot.so: ReviewBot/Review/libReview.so
ReviewBot/libReviewBot.so: ReviewBot/Time/libTime.so
ReviewBot/libReviewBot.so: ReviewBot/CMakeFiles/ReviewBot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gleb/CXX/BotDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libReviewBot.so"
	cd /home/gleb/CXX/BotDialog/build/ReviewBot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ReviewBot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ReviewBot/CMakeFiles/ReviewBot.dir/build: ReviewBot/libReviewBot.so
.PHONY : ReviewBot/CMakeFiles/ReviewBot.dir/build

ReviewBot/CMakeFiles/ReviewBot.dir/clean:
	cd /home/gleb/CXX/BotDialog/build/ReviewBot && $(CMAKE_COMMAND) -P CMakeFiles/ReviewBot.dir/cmake_clean.cmake
.PHONY : ReviewBot/CMakeFiles/ReviewBot.dir/clean

ReviewBot/CMakeFiles/ReviewBot.dir/depend:
	cd /home/gleb/CXX/BotDialog/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gleb/CXX/BotDialog /home/gleb/CXX/BotDialog/ReviewBot /home/gleb/CXX/BotDialog/build /home/gleb/CXX/BotDialog/build/ReviewBot /home/gleb/CXX/BotDialog/build/ReviewBot/CMakeFiles/ReviewBot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ReviewBot/CMakeFiles/ReviewBot.dir/depend
