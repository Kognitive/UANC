cmake_minimum_required(VERSION 3.6)
project(UANC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# apply some settings to generate output in Bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin/Lib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Create the main executable and link the needed libraries
set(SOURCE_FILES Code/UANC/main.cpp Code/UANC/gui/MainWindow.cpp Code/UANC/gui/MainWindow.h Code/UANC/gui/MainWidget.cpp Code/UANC/gui/MainWidget.h Code/UANC/util/FileActor.h Code/UANC/util/DialogUtil.h Code/UANC/algorithm/Algorithm.h Code/UANC/algorithm/InverseFFTAlgorithm.h Code/UANC/algorithm/InverseDirectAlgorithm.h)
set(AQUILA_FILES Code/libs/aquila/source/SignalSource.h Code/libs/aquila/source/SignalSource.cpp)
set(QCUSTOMPLOT_FILES Code/libs/qplot/qcustomplot.h Code/libs/qplot/qcustomplot.cpp)

add_executable(UANC ${SOURCE_FILES} ${AQUILA_FILES} ${QCUSTOMPLOT_FILES})

# ------------------------------------ QT5 -----------------------------------------

set(ENV{QT5_QMAKE_DIR} /opt/qt5.7/5.7/gcc_64/bin/qmake)
set(CMAKE_PREFIX_PATH $ENV{QT5_QMAKE_DIR})
MESSAGE(STATUS "QT5_QMAKE_DIR: " ${CMAKE_PREFIX_PATH})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS}
)

add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
target_link_libraries(UANC ${Qt5Widgets_LIBRARIES})
target_link_libraries(UANC ${Qt5PrintSupport_LIBRARIES})
target_link_libraries(UANC ${Qt5Network_LIBRARIES})

# ------------------------------------ Multiplattform -----------------------------------------

# generate proper gui program on specified platform
if(WIN32) # Check if we are on Windows
    if(MSVC) # Check if we are using the Visual Studio compiler
        set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE YES
                LINK_FLAGS "/ENTRY:mainCRTStartup"
                )
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif(MSVC)
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE YES
            )
elseif(UNIX)
    # Nothing special required
else()
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)