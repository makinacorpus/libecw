#!/bin/ksh
#set -x 

###############################################################################
#
# NCSNightlyBuildUnix.ksh :	master build script for the ECW JPEG 2000 SDK on 
#							UNIX-like platforms.
#
# To build the libraries, review the instructions in the file build.txt
# and the files makefile.inc and makelibs.inc.
#
# You will need to set the value of $NCSTOP below to the directory in 
# which you unzipped the SDK source archive.  You may also need to give 
# this script execution permissions and change the interpreter in the 
# "shebang" line (e.g. to bash), depending on your platform.
#
# Invoking this script with different arguments allows you to build the 
# debug and release configurations of the SDK libraries.
#
# e.g.	
#	"NCSNightlyBuildUnix.ksh release" builds the release configuration 
#	of the shared libraries
#
#	"NCSNightlyBuildUnix.ksh build" builds both the relase and debug
#	configurations of the shared libraries
#
###############################################################################

NCSTOP=$HOME/NCS
export PROJECTS='NCSUtil NCSnet/NCSCnet3 NCSEcw/NCSEcw NCSEcw/NCSEcwC_SDK'
platform=`uname -s`

# Use gmake on all platforms.
if test $platform = "HP-UX"; then
MAKE=/usr/local/bin/make
else
MAKE=make
fi

if test "$1" = "clean"; then
for i in $PROJECTS; do
	cd $NCSTOP/Source/C/$i
	echo Cleaning $i
	$MAKE clean
done
fi

if test "$1" = "release"; then
for i in $PROJECTS; do
	cd $NCSTOP/Source/C/$i
	echo Building release version of $i
	$MAKE
done
fi

if test "$1" = "build"; then
for i in $PROJECTS; do
	cd $NCSTOP/Source/C/$i
	echo Building release version of $i
	$MAKE
	echo Building debug version of $i
	$MAKE debug
done
fi

echo Make task complete
