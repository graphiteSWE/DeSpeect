#!/bin/bash

# Varie
apt-get install libxext-dev

# Build speect
cd SpeectInstaller
./install.sh
cd ..

rm -rf test-framework/build
mkdir test-framework/build

# Build QT
rm -rf build
mkdir build
cd build
cmake ../DeSpeect -DENABLE_COVERAGE=On || exit 1
make || exit 2
ctest || exit 4
gcov -o ../gcov_file ../DeSpeect/main.cpp
gcov -o ../gcov_file ../DeSpeect/Model/Command/src/*.cpp
gcov -o ../gcov_file ../DeSpeect/Model/SpeectWrapper/src/*.cpp
gcov -o ../gcov_file ../DeSpeect/Qt/src/*.cpp
gcov -o ../gcov_file ../DeSpeect/Test/*.cpp
lcov --directory . --capture --output-file codecov.info
#lcov --directory . --capture --output-file coverage.info # capture coverage info
#lcov --remove coverage.info '/usr/*' --output-file coverage.info # filter out system
#lcov --list coverage.info #debug info
cd ..
