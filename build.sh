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
cd build
cmake .. || exit 1
make || exit 2
cd ../..
