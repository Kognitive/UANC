# Install script for directory: /home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/libAquila.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/aquila" TYPE DIRECTORY FILES "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/aquila/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aquila" TYPE FILE FILES
    "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/CHANGELOG"
    "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/LICENSE"
    "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-src/README.md"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/lib/cmake_install.cmake")
  include("/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/examples/cmake_install.cmake")
  include("/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "/home/markus/Daten/University/BP/understanding-active-noise-cancelling/Code/libs/aquila-build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
