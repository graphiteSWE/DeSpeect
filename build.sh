#!/bin/bash

# Varie
apt-get install libxext-dev

# Build speect
cd SpeectInstaller
./install.sh
cd ..

# Build QT
cd DeSpeect
rm -rf build

mkdir build
mkdir build/Test

cp -r ../SpeectInstaller/voices/cmu_arctic_slt ./build/Test
cd build
cmake .. || exit 1
make || exit 2
ctest
cd ../..
