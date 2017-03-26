These are the build and run instructions for the UANC application:

Preconditions:
On the operation system CMake has to be installed at least in version 3.5.1
On Linux either clang and clang++ or gcc/g++ are required.
On Windows the required MSVC 2013 compiler is needed for building.
QT is required at least in the version 5.7.1 and also the armadillo library is needed. The aquila and qplot libraries are already deployed with the application and no action is needed.

For the generation of the documentation Doxygen must be installed and for lint-testing of the code a python runtime in a version >2.7 must be available on the system.

Build of main application and tests:

For Linux:
	In the CMakeLists.txt
	At first modify the CMAKE_PREFIX_PATH cmake variable, if you use a QT installation which is not in the standard distribution packages. E.g. set (CMAKE_PREFIX_PATH ${CMAKE_MODULE_PATH} "/opt/Qt5.8.0/5.8/gcc_64/lib/cmake") 

	Auto-Build: Run runCmakeWithClang.bash, if bash is available. This should build the UANC application and the tests with clang. The output is put into the Bin directory.

Otherwise generate the makefiles using cd Bin
									   cmake ..
									   cmake -DCMAKE_BUILD_TYPE=Release/Debug ..

Then build the application using       make [-j X]

For windows:
	
Install MSVC 2013 e.g. https://www.microsoft.com/de-de/download/details.aspx?id=44914
Other MSVC versions and 
Download the Armadillo library
Install CMake for Windows and configure Armadillo with it. Generate a MSVC project file.
Build the Armadillo INSTALL target. It is important that the build is done using administrator rights in the Visual Studio!
Edit the CMakeLists.txt
Set the CMAKE_PREFIX_PATH to the QT installation folder: E.g. set (CMAKE_PREFIX_PATH ${CMAKE_MODULE_PATH} "C:/Qt/5.8/msvc2013_64/lib/cmake")
Change the Armadillo inculde directory if necessary: target_include_directories(UANC  PUBLIC "C:/Program Files/armadillo/include")
Configure the UANC Project using CMake GUI and generate the MSVC project files. 
Build the UANC target in the MSVC.

The documentation can be generated after generating the makefile with CMake on all systems by using the make target doc. The Linter can be run with python by using the target stylecheck.
