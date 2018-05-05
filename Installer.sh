#!/bin/bash

# Varie
BASEDIR=`pwd`
apt-get install libxext-dev

##prepare folder
OUTPUTFOLDER=$(zenity --file-selection --directory)
rm -rf $OUTPUTFOLDER/DeSpeect_SWE
mkdir $OUTPUTFOLDER/DeSpeect_SWE

cd $OUTPUTFOLDER/DeSpeect_SWE
OUTPUTFOLDER=`pwd`

cd $BASEDIR
rm -rf $OUTPUTFOLDER/SpeectInstaller
rm -rf $OUTPUTFOLDER/DeSpeect

cp -r $BASEDIR/SpeectInstaller $OUTPUTFOLDER/

cp -r $BASEDIR/DeSpeect $OUTPUTFOLDER/

rm -rf $OUTPUTFOLDER/SpeectInstaller/build
rm -rf $OUTPUTFOLDER/SpeectInstaller/install
cd $OUTPUTFOLDER
#build Speect
cd SpeectInstaller
./install.sh no-download
rm -rf ./downloads
rm -rf ./sources
cd ..

# Build QT
cd DeSpeect
rm -rf ../DespeectInstall
mkdir ../DespeectInstall
mkdir ../DespeectInstall/Test

cp -r ../SpeectInstaller/voices/cmu_arctic_slt ../DespeectInstall/Test
rm -rf ../SpeectInstaller/voices
cd ../DespeectInstall
cmake ../DeSpeect/ -DTest=FALSE || exit 1
make || exit 2
cd ..
rm -r DeSpeect
rm -rf ./Despeect
ln -s $OUTPUTFOLDER/DespeectInstall/main ./DeSpeect