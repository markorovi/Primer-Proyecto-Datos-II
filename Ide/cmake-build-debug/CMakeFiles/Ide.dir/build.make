# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/joel/Descargas/clion-2020.3.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/joel/Descargas/clion-2020.3.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joel/Qt_proyects/Ide

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joel/Qt_proyects/Ide/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ide.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ide.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ide.dir/flags.make

CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.o: CMakeFiles/Ide.dir/flags.make
CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.o: Ide_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Qt_proyects/Ide/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.o -c /home/joel/Qt_proyects/Ide/cmake-build-debug/Ide_autogen/mocs_compilation.cpp

CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Qt_proyects/Ide/cmake-build-debug/Ide_autogen/mocs_compilation.cpp > CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.i

CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Qt_proyects/Ide/cmake-build-debug/Ide_autogen/mocs_compilation.cpp -o CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.s

CMakeFiles/Ide.dir/main.cpp.o: CMakeFiles/Ide.dir/flags.make
CMakeFiles/Ide.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Qt_proyects/Ide/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Ide.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ide.dir/main.cpp.o -c /home/joel/Qt_proyects/Ide/main.cpp

CMakeFiles/Ide.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ide.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Qt_proyects/Ide/main.cpp > CMakeFiles/Ide.dir/main.cpp.i

CMakeFiles/Ide.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ide.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Qt_proyects/Ide/main.cpp -o CMakeFiles/Ide.dir/main.cpp.s

CMakeFiles/Ide.dir/mainwindow.cpp.o: CMakeFiles/Ide.dir/flags.make
CMakeFiles/Ide.dir/mainwindow.cpp.o: ../mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Qt_proyects/Ide/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Ide.dir/mainwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ide.dir/mainwindow.cpp.o -c /home/joel/Qt_proyects/Ide/mainwindow.cpp

CMakeFiles/Ide.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ide.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Qt_proyects/Ide/mainwindow.cpp > CMakeFiles/Ide.dir/mainwindow.cpp.i

CMakeFiles/Ide.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ide.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Qt_proyects/Ide/mainwindow.cpp -o CMakeFiles/Ide.dir/mainwindow.cpp.s

CMakeFiles/Ide.dir/Interpreter.cpp.o: CMakeFiles/Ide.dir/flags.make
CMakeFiles/Ide.dir/Interpreter.cpp.o: ../Interpreter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Qt_proyects/Ide/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Ide.dir/Interpreter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ide.dir/Interpreter.cpp.o -c /home/joel/Qt_proyects/Ide/Interpreter.cpp

CMakeFiles/Ide.dir/Interpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ide.dir/Interpreter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Qt_proyects/Ide/Interpreter.cpp > CMakeFiles/Ide.dir/Interpreter.cpp.i

CMakeFiles/Ide.dir/Interpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ide.dir/Interpreter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Qt_proyects/Ide/Interpreter.cpp -o CMakeFiles/Ide.dir/Interpreter.cpp.s

# Object files for target Ide
Ide_OBJECTS = \
"CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/Ide.dir/main.cpp.o" \
"CMakeFiles/Ide.dir/mainwindow.cpp.o" \
"CMakeFiles/Ide.dir/Interpreter.cpp.o"

# External object files for target Ide
Ide_EXTERNAL_OBJECTS =

Ide: CMakeFiles/Ide.dir/Ide_autogen/mocs_compilation.cpp.o
Ide: CMakeFiles/Ide.dir/main.cpp.o
Ide: CMakeFiles/Ide.dir/mainwindow.cpp.o
Ide: CMakeFiles/Ide.dir/Interpreter.cpp.o
Ide: CMakeFiles/Ide.dir/build.make
Ide: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
Ide: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
Ide: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
Ide: CMakeFiles/Ide.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joel/Qt_proyects/Ide/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Ide"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ide.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ide.dir/build: Ide

.PHONY : CMakeFiles/Ide.dir/build

CMakeFiles/Ide.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ide.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ide.dir/clean

CMakeFiles/Ide.dir/depend:
	cd /home/joel/Qt_proyects/Ide/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joel/Qt_proyects/Ide /home/joel/Qt_proyects/Ide /home/joel/Qt_proyects/Ide/cmake-build-debug /home/joel/Qt_proyects/Ide/cmake-build-debug /home/joel/Qt_proyects/Ide/cmake-build-debug/CMakeFiles/Ide.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ide.dir/depend

