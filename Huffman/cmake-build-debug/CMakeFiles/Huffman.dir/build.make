# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2018.2.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2018.2.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\User\CLionProjects\Huffman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\User\CLionProjects\Huffman\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Huffman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Huffman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Huffman.dir/flags.make

CMakeFiles/Huffman.dir/main.cpp.obj: CMakeFiles/Huffman.dir/flags.make
CMakeFiles/Huffman.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\User\CLionProjects\Huffman\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Huffman.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Huffman.dir\main.cpp.obj -c C:\Users\User\CLionProjects\Huffman\main.cpp

CMakeFiles/Huffman.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Huffman.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\User\CLionProjects\Huffman\main.cpp > CMakeFiles\Huffman.dir\main.cpp.i

CMakeFiles/Huffman.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Huffman.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\User\CLionProjects\Huffman\main.cpp -o CMakeFiles\Huffman.dir\main.cpp.s

CMakeFiles/Huffman.dir/huffman.cpp.obj: CMakeFiles/Huffman.dir/flags.make
CMakeFiles/Huffman.dir/huffman.cpp.obj: ../huffman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\User\CLionProjects\Huffman\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Huffman.dir/huffman.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Huffman.dir\huffman.cpp.obj -c C:\Users\User\CLionProjects\Huffman\huffman.cpp

CMakeFiles/Huffman.dir/huffman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Huffman.dir/huffman.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\User\CLionProjects\Huffman\huffman.cpp > CMakeFiles\Huffman.dir\huffman.cpp.i

CMakeFiles/Huffman.dir/huffman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Huffman.dir/huffman.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\User\CLionProjects\Huffman\huffman.cpp -o CMakeFiles\Huffman.dir\huffman.cpp.s

CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.obj: CMakeFiles/Huffman.dir/flags.make
CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.obj: ../HuffmanArchiver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\User\CLionProjects\Huffman\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Huffman.dir\HuffmanArchiver.cpp.obj -c C:\Users\User\CLionProjects\Huffman\HuffmanArchiver.cpp

CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\User\CLionProjects\Huffman\HuffmanArchiver.cpp > CMakeFiles\Huffman.dir\HuffmanArchiver.cpp.i

CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\User\CLionProjects\Huffman\HuffmanArchiver.cpp -o CMakeFiles\Huffman.dir\HuffmanArchiver.cpp.s

# Object files for target Huffman
Huffman_OBJECTS = \
"CMakeFiles/Huffman.dir/main.cpp.obj" \
"CMakeFiles/Huffman.dir/huffman.cpp.obj" \
"CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.obj"

# External object files for target Huffman
Huffman_EXTERNAL_OBJECTS =

Huffman.exe: CMakeFiles/Huffman.dir/main.cpp.obj
Huffman.exe: CMakeFiles/Huffman.dir/huffman.cpp.obj
Huffman.exe: CMakeFiles/Huffman.dir/HuffmanArchiver.cpp.obj
Huffman.exe: CMakeFiles/Huffman.dir/build.make
Huffman.exe: CMakeFiles/Huffman.dir/linklibs.rsp
Huffman.exe: CMakeFiles/Huffman.dir/objects1.rsp
Huffman.exe: CMakeFiles/Huffman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\User\CLionProjects\Huffman\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Huffman.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Huffman.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Huffman.dir/build: Huffman.exe

.PHONY : CMakeFiles/Huffman.dir/build

CMakeFiles/Huffman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Huffman.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Huffman.dir/clean

CMakeFiles/Huffman.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\User\CLionProjects\Huffman C:\Users\User\CLionProjects\Huffman C:\Users\User\CLionProjects\Huffman\cmake-build-debug C:\Users\User\CLionProjects\Huffman\cmake-build-debug C:\Users\User\CLionProjects\Huffman\cmake-build-debug\CMakeFiles\Huffman.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Huffman.dir/depend

