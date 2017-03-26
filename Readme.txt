These are the build and run instructions for the UANC application:

Preconditions:
On the operation system CMake has to be installed at least in version 3.5.1
On Linux either clang and clang++ or gcc/g++ are required.
On Windows the required MSVC 2013 compiler is needed for building.
QT is required at least in the version 5.7.1 and also the armadillo library is needed. The aquila and qplot libraries are already deployed with the application and no action is needed.

For the generation of the documentation Doxygen must be installed and for lint-testing of the code a python runtime in a version >2.7 must be available on the system.

Build of main application and tests:

For Linux:

	At first modify the CMAKE_PREFIX_PATH cmake variable, if you use a QT installation which is not in the standard distribution packages. E.g. set (CMAKE_PREFIX_PATH ${CMAKE_MODULE_PATH} "/opt/Qt5.8.0/5.8/gcc_64/lib/cmake") 

	Auto-Build: Run runCmakeWithClang.bash, if bash is available. This should build the UANC application and the tests with clang. The output is put into the Bin directory.

Otherwise generate the makefiles using cd Bin
									   cmake ..
									   cmake -DCMAKE_BUILD_TYPE=Release/Debug ..

Then build the application using       make [-j X]

For windows:
	
Install MSVC 2013 e.g. https://www.microsoft.com/de-de/download/details.aspx?id=44914

