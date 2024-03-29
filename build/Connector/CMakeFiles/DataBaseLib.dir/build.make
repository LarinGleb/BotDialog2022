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
include Connector/CMakeFiles/DataBaseLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Connector/CMakeFiles/DataBaseLib.dir/compiler_depend.make

# Include the progress variables for this target.
include Connector/CMakeFiles/DataBaseLib.dir/progress.make

# Include the compile flags for this target's objects.
include Connector/CMakeFiles/DataBaseLib.dir/flags.make

Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.o: Connector/CMakeFiles/DataBaseLib.dir/flags.make
Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.o: ../Connector/DataBase.cpp
Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.o: Connector/CMakeFiles/DataBaseLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gleb/CXX/BotDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.o"
	cd /home/gleb/CXX/BotDialog/build/Connector && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.o -MF CMakeFiles/DataBaseLib.dir/DataBase.cpp.o.d -o CMakeFiles/DataBaseLib.dir/DataBase.cpp.o -c /home/gleb/CXX/BotDialog/Connector/DataBase.cpp

Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DataBaseLib.dir/DataBase.cpp.i"
	cd /home/gleb/CXX/BotDialog/build/Connector && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gleb/CXX/BotDialog/Connector/DataBase.cpp > CMakeFiles/DataBaseLib.dir/DataBase.cpp.i

Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DataBaseLib.dir/DataBase.cpp.s"
	cd /home/gleb/CXX/BotDialog/build/Connector && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gleb/CXX/BotDialog/Connector/DataBase.cpp -o CMakeFiles/DataBaseLib.dir/DataBase.cpp.s

# Object files for target DataBaseLib
DataBaseLib_OBJECTS = \
"CMakeFiles/DataBaseLib.dir/DataBase.cpp.o"

# External object files for target DataBaseLib
DataBaseLib_EXTERNAL_OBJECTS =

Connector/libDataBaseLib.so: Connector/CMakeFiles/DataBaseLib.dir/DataBase.cpp.o
Connector/libDataBaseLib.so: Connector/CMakeFiles/DataBaseLib.dir/build.make
Connector/libDataBaseLib.so: /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so.7
Connector/libDataBaseLib.so: /usr/local/lib/libssl.a
Connector/libDataBaseLib.so: /usr/local/lib/libcrypto.a
Connector/libDataBaseLib.so: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
Connector/libDataBaseLib.so: /usr/lib/x86_64-linux-gnu/libcurl.so
Connector/libDataBaseLib.so: Connector/CMakeFiles/DataBaseLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gleb/CXX/BotDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libDataBaseLib.so"
	cd /home/gleb/CXX/BotDialog/build/Connector && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DataBaseLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Connector/CMakeFiles/DataBaseLib.dir/build: Connector/libDataBaseLib.so
.PHONY : Connector/CMakeFiles/DataBaseLib.dir/build

Connector/CMakeFiles/DataBaseLib.dir/clean:
	cd /home/gleb/CXX/BotDialog/build/Connector && $(CMAKE_COMMAND) -P CMakeFiles/DataBaseLib.dir/cmake_clean.cmake
.PHONY : Connector/CMakeFiles/DataBaseLib.dir/clean

Connector/CMakeFiles/DataBaseLib.dir/depend:
	cd /home/gleb/CXX/BotDialog/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gleb/CXX/BotDialog /home/gleb/CXX/BotDialog/Connector /home/gleb/CXX/BotDialog/build /home/gleb/CXX/BotDialog/build/Connector /home/gleb/CXX/BotDialog/build/Connector/CMakeFiles/DataBaseLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Connector/CMakeFiles/DataBaseLib.dir/depend

