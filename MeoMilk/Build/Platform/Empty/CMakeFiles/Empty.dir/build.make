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
CMAKE_SOURCE_DIR = /home/moebiusmeow/repo/MeoMilk/MeoMilk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build

# Include any dependencies generated for this target.
include Platform/Empty/CMakeFiles/Empty.dir/depend.make

# Include the progress variables for this target.
include Platform/Empty/CMakeFiles/Empty.dir/progress.make

# Include the compile flags for this target's objects.
include Platform/Empty/CMakeFiles/Empty.dir/flags.make

Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o: Platform/Empty/CMakeFiles/Empty.dir/flags.make
Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o: ../Platform/Empty/EmptyApplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o"
	cd /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Empty.dir/EmptyApplication.cpp.o -c /home/moebiusmeow/repo/MeoMilk/MeoMilk/Platform/Empty/EmptyApplication.cpp

Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Empty.dir/EmptyApplication.cpp.i"
	cd /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moebiusmeow/repo/MeoMilk/MeoMilk/Platform/Empty/EmptyApplication.cpp > CMakeFiles/Empty.dir/EmptyApplication.cpp.i

Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Empty.dir/EmptyApplication.cpp.s"
	cd /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moebiusmeow/repo/MeoMilk/MeoMilk/Platform/Empty/EmptyApplication.cpp -o CMakeFiles/Empty.dir/EmptyApplication.cpp.s

Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.requires:

.PHONY : Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.requires

Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.provides: Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.requires
	$(MAKE) -f Platform/Empty/CMakeFiles/Empty.dir/build.make Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.provides.build
.PHONY : Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.provides

Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.provides.build: Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o


# Object files for target Empty
Empty_OBJECTS = \
"CMakeFiles/Empty.dir/EmptyApplication.cpp.o"

# External object files for target Empty
Empty_EXTERNAL_OBJECTS =

Platform/Empty/Empty: Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o
Platform/Empty/Empty: Platform/Empty/CMakeFiles/Empty.dir/build.make
Platform/Empty/Empty: Framework/Common/libCommon.a
Platform/Empty/Empty: Platform/Empty/CMakeFiles/Empty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Empty"
	cd /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Empty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Platform/Empty/CMakeFiles/Empty.dir/build: Platform/Empty/Empty

.PHONY : Platform/Empty/CMakeFiles/Empty.dir/build

Platform/Empty/CMakeFiles/Empty.dir/requires: Platform/Empty/CMakeFiles/Empty.dir/EmptyApplication.cpp.o.requires

.PHONY : Platform/Empty/CMakeFiles/Empty.dir/requires

Platform/Empty/CMakeFiles/Empty.dir/clean:
	cd /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty && $(CMAKE_COMMAND) -P CMakeFiles/Empty.dir/cmake_clean.cmake
.PHONY : Platform/Empty/CMakeFiles/Empty.dir/clean

Platform/Empty/CMakeFiles/Empty.dir/depend:
	cd /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/moebiusmeow/repo/MeoMilk/MeoMilk /home/moebiusmeow/repo/MeoMilk/MeoMilk/Platform/Empty /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty /home/moebiusmeow/repo/MeoMilk/MeoMilk/Build/Platform/Empty/CMakeFiles/Empty.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Platform/Empty/CMakeFiles/Empty.dir/depend

