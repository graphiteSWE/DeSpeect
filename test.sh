#!/bin/bash

# Varie
BASEDIR=`pwd`

##prepare folder
apt-get install libxext-dev
case "$1" in
	"")OUTPUTFOLDER="./Despeect";;
	*)OUTPUTFOLDER=$1;;
esac
if [ -d "$OUTPUTFOLDER" ]; 
	then
	echo "Found Folder"
	else
	mkdir -p $OUTPUTFOLDER 
fi
rm -r $OUTPUTFOLDER/SpeectInstaller
rm -r $OUTPUTFOLDER/DeSpeect
mkdir -p $OUTPUTFOLDER/SpeectInstaller/install
mkdir -p $OUTPUTFOLDER/DeSpeect
cd $OUTPUTFOLDER
OUTPUTFOLDER=`pwd`
cd $BASEDIR
#build Speect
cd SpeectInstaller
./install.sh

cp -r ./install $OUTPUTFOLDER/SpeectInstaller/install
cd ..

# Build QT
cd DeSpeect
rm -rf build

mkdir build
mkdir build/Test

cp -r ../SpeectInstaller/voices/cmu_arctic_slt ./build/Test
cd build
cmake .. -DTest=FALSE || exit 1
make || exit 2
cd ..
cp -r ./build $OUTPUTFOLDER
mv $OUTPUTFOLDER/build $OUTPUTFOLDER/DeSpeect
cd $OUTPUTFOLDER/DeSpeect
ln -s $OUTPUTFOLDER/DeSpeect/build/main ../exe
