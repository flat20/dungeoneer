# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Microsoft Visual Studio\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Microsoft Visual Studio\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\andreas\code\dungeoneer\dungeoneer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\andreas\code\dungeoneer\dungeoneer\build

# Include any dependencies generated for this target.
include CMakeFiles\app.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\app.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\app.dir\flags.make

CMakeFiles\app.dir\dll.obj: CMakeFiles\app.dir\flags.make
CMakeFiles\app.dir\dll.obj: ..\dll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\andreas\code\dungeoneer\dungeoneer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/app.dir/dll.obj"
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\app.dir\dll.obj /FdCMakeFiles\app.dir\app.pdb /FS -c C:\Users\andreas\code\dungeoneer\dungeoneer\dll.cpp
<<

CMakeFiles\app.dir\dll.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/dll.i"
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\cl.exe" > CMakeFiles\app.dir\dll.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\andreas\code\dungeoneer\dungeoneer\dll.cpp
<<

CMakeFiles\app.dir\dll.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/dll.s"
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\app.dir\dll.s /c C:\Users\andreas\code\dungeoneer\dungeoneer\dll.cpp
<<

CMakeFiles\app.dir\ui.obj: CMakeFiles\app.dir\flags.make
CMakeFiles\app.dir\ui.obj: ..\ui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\andreas\code\dungeoneer\dungeoneer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/app.dir/ui.obj"
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\app.dir\ui.obj /FdCMakeFiles\app.dir\app.pdb /FS -c C:\Users\andreas\code\dungeoneer\dungeoneer\ui.cpp
<<

CMakeFiles\app.dir\ui.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app.dir/ui.i"
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\cl.exe" > CMakeFiles\app.dir\ui.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\andreas\code\dungeoneer\dungeoneer\ui.cpp
<<

CMakeFiles\app.dir\ui.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app.dir/ui.s"
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\app.dir\ui.s /c C:\Users\andreas\code\dungeoneer\dungeoneer\ui.cpp
<<

# Object files for target app
app_OBJECTS = \
"CMakeFiles\app.dir\dll.obj" \
"CMakeFiles\app.dir\ui.obj"

# External object files for target app
app_EXTERNAL_OBJECTS =

app.lib: CMakeFiles\app.dir\dll.obj
app.lib: CMakeFiles\app.dir\ui.obj
app.lib: CMakeFiles\app.dir\build.make
app.lib: CMakeFiles\app.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\andreas\code\dungeoneer\dungeoneer\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library app.lib"
	$(CMAKE_COMMAND) -P CMakeFiles\app.dir\cmake_clean_target.cmake
	"D:\Microsoft Visual Studio\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64\link.exe" /lib /nologo /machine:x64 /out:app.lib @CMakeFiles\app.dir\objects1.rsp 

# Rule to build all files generated by this target.
CMakeFiles\app.dir\build: app.lib

.PHONY : CMakeFiles\app.dir\build

CMakeFiles\app.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\app.dir\cmake_clean.cmake
.PHONY : CMakeFiles\app.dir\clean

CMakeFiles\app.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\andreas\code\dungeoneer\dungeoneer C:\Users\andreas\code\dungeoneer\dungeoneer C:\Users\andreas\code\dungeoneer\dungeoneer\build C:\Users\andreas\code\dungeoneer\dungeoneer\build C:\Users\andreas\code\dungeoneer\dungeoneer\build\CMakeFiles\app.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\app.dir\depend

