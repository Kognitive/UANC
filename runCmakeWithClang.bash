#!/bin/bash

# This script re-generates the cmake files with clang and debug settings.
# It must be run in the root folder of the project

cd ./Bin

rm -rf CMakeCache.txt CMakeFiles/ ../CMakeCache.txt  ../CMakeFiles/
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j $(grep -c ^processor /proc/cpuinfo)
