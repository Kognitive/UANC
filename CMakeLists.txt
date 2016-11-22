cmake_minimum_required(VERSION 3.6)
project(UANC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# apply some settings to generate output in Bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Bin/Lib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Create the main executable and link the needed libraries
set(SOURCE_FILES Code/UANC/main.cpp)
add_executable(UANC ${SOURCE_FILES})
target_link_libraries(UANC Qt5::Widgets)
