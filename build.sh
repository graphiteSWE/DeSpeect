#!/bin/bash

# Build speect
cd SpeectInstaller
./install.sh
cd ..

# Build QT
cd DeSpeect
rm -rf test
mkdir test
cd test
cmake ..
make
cd ../..
