@echo off 
echo Creating build files for sample code ...
set OLD_QMAKESPEC=%QMAKESPEC%
set QMAKESPEC=win32-msvc
set QMAKECMD=qmake.exe
set FIXCMD=call ..\..\..\Source\NCSBuildQmake\FixQmakeMakefile.bat
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example1/DExample1-static.dsp examples.pro "CONFIG+=dexample1 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example2/DExample2-static.dsp examples.pro "CONFIG+=dexample2 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example4/DExample4-static.dsp examples.pro "CONFIG+=dexample4 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example1/CExample1-static.dsp examples.pro "CONFIG+=cexample1 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example2/CExample2-static.dsp examples.pro "CONFIG+=cexample2 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example3/CExample3-static.dsp examples.pro "CONFIG+=cexample3 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example4/CExample4-static.dsp examples.pro "CONFIG+=cexample4 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example5/CExample5-static.dsp examples.pro "CONFIG+=cexample5 libecwj2 staticlink"

%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example1/DExample1-shared.dsp examples.pro "CONFIG+=dexample1 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example2/DExample2-shared.dsp examples.pro "CONFIG+=dexample2 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example4/DExample4-shared.dsp examples.pro "CONFIG+=dexample4 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example1/CExample1-shared.dsp examples.pro "CONFIG+=cexample1 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example2/CExample2-shared.dsp examples.pro "CONFIG+=cexample2 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example3/CExample3-shared.dsp examples.pro "CONFIG+=cexample3 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example4/CExample4-shared.dsp examples.pro "CONFIG+=cexample4 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example5/CExample5-shared.dsp examples.pro "CONFIG+=cexample5 libecwj2 sharedlink"

set QMAKESPEC=linux-g++
%QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-linux-static examples.pro "CONFIG+=dexample1 libecwj2 staticlink"

CD ../../examples/decompression/example1/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-linux-static examples.pro "CONFIG+=dexample2 libecwj2 staticlink"

CD ../../examples/decompression/example2/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-linux-static examples.pro "CONFIG+=dexample4 libecwj2 staticlink"

CD ../../examples/decompression/example4/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-linux-static examples.pro "CONFIG+=cexample1 libecwj2 staticlink"

CD ../../examples/compression/example1/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-linux-static examples.pro "CONFIG+=cexample2 libecwj2 staticlink"

CD ../../examples/compression/example2/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-linux-static examples.pro "CONFIG+=cexample3 libecwj2 staticlink"

CD ../../examples/compression/example3/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-linux-static examples.pro "CONFIG+=cexample4 libecwj2 staticlink"

CD ../../examples/compression/example4/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-linux-static examples.pro "CONFIG+=cexample5 libecwj2 staticlink"

CD ../../examples/compression/example5/
%FIXCMD% Makefile-linux-static
CD ../../../Source/NCSBuildQmake

%QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-linux-shared examples.pro "CONFIG+=dexample1 libecwj2 sharedlink"

CD ../../examples/decompression/example1/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-linux-shared examples.pro "CONFIG+=dexample2 libecwj2 sharedlink"

CD ../../examples/decompression/example2/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-linux-shared examples.pro "CONFIG+=dexample4 libecwj2 sharedlink"

CD ../../examples/decompression/example4/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-linux-shared examples.pro "CONFIG+=cexample1 libecwj2 sharedlink"

CD ../../examples/compression/example1/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-linux-shared examples.pro "CONFIG+=cexample2 libecwj2 sharedlink"

CD ../../examples/compression/example2/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-linux-shared examples.pro "CONFIG+=cexample3 libecwj2 sharedlink"

CD ../../examples/compression/example3/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-linux-shared examples.pro "CONFIG+=cexample4 libecwj2 sharedlink"

CD ../../examples/compression/example4/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-linux-shared examples.pro "CONFIG+=cexample5 libecwj2 sharedlink"

CD ../../examples/compression/example5/
%FIXCMD% Makefile-linux-shared
CD ../../../Source/NCSBuildQmake

set QMAKESPEC=solaris-g++
%QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-solaris-static examples.pro "CONFIG+=dexample1 libecwj2 staticlink"

CD ../../examples/decompression/example1/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-solaris-static examples.pro "CONFIG+=dexample2 libecwj2 staticlink"

CD ../../examples/decompression/example2/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-solaris-static examples.pro "CONFIG+=dexample4 libecwj2 staticlink"

CD ../../examples/decompression/example4/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-solaris-static examples.pro "CONFIG+=cexample1 libecwj2 staticlink"

CD ../../examples/compression/example1/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-solaris-static examples.pro "CONFIG+=cexample2 libecwj2 staticlink"

CD ../../examples/compression/example2/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-solaris-static examples.pro "CONFIG+=cexample3 libecwj2 staticlink"

CD ../../examples/compression/example3/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-solaris-static examples.pro "CONFIG+=cexample4 libecwj2 staticlink"

CD ../../examples/compression/example4/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-solaris-static examples.pro "CONFIG+=cexample5 libecwj2 staticlink"

CD ../../examples/compression/example5/
%FIXCMD% Makefile-solaris-static
CD ../../../Source/NCSBuildQmake

%QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-solaris-shared examples.pro "CONFIG+=dexample1 libecwj2 sharedlink"

CD ../../examples/decompression/example1/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-solaris-shared examples.pro "CONFIG+=dexample2 libecwj2 sharedlink"

CD ../../examples/decompression/example2/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-solaris-shared examples.pro "CONFIG+=dexample4 libecwj2 sharedlink"

CD ../../examples/decompression/example4/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-solaris-shared examples.pro "CONFIG+=cexample1 libecwj2 sharedlink"

CD ../../examples/compression/example1/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-solaris-shared examples.pro "CONFIG+=cexample2 libecwj2 sharedlink"

CD ../../examples/compression/example2/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-solaris-shared examples.pro "CONFIG+=cexample3 libecwj2 sharedlink"

CD ../../examples/compression/example3/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-solaris-shared examples.pro "CONFIG+=cexample4 libecwj2 sharedlink"

CD ../../examples/compression/example4/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake
%QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-solaris-shared examples.pro "CONFIG+=cexample5 libecwj2 sharedlink"

CD ../../examples/compression/example5/
%FIXCMD% Makefile-solaris-shared
CD ../../../Source/NCSBuildQmake


REM set QMAKESPEC=hpux-acc
REM %QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-hpux-static examples.pro "CONFIG+=dexample1 libecwj2 staticlink"
REM %FIXMCD% ../../examples/decompression/example1/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-hpux-static examples.pro "CONFIG+=dexample2 libecwj2 staticlink"
REM %FIXMCD% ../../examples/decompression/example2/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-hpux-static examples.pro "CONFIG+=dexample4 libecwj2 staticlink"
REM %FIXMCD% ../../examples/decompression/example4/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-hpux-static examples.pro "CONFIG+=cexample1 libecwj2 staticlink"
REM %FIXMCD% ../../examples/compression/example1/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-hpux-static examples.pro "CONFIG+=cexample2 libecwj2 staticlink"
REM %FIXMCD% ../../examples/compression/example2/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-hpux-static examples.pro "CONFIG+=cexample3 libecwj2 staticlink"
REM %FIXMCD% ../../examples/compression/example3/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-hpux-static examples.pro "CONFIG+=cexample4 libecwj2 staticlink"
REM %FIXMCD% ../../examples/compression/example4/Makefile-hpux-static
REM %QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-hpux-static examples.pro "CONFIG+=cexample5 libecwj2 staticlink"
REM %FIXMCD% ../../examples/compression/example5/Makefile-hpux-static

REM %QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-hpux-shared examples.pro "CONFIG+=dexample1 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/decompression/example1/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-hpux-shared examples.pro "CONFIG+=dexample2 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/decompression/example2/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-hpux-shared examples.pro "CONFIG+=dexample4 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/decompression/example4/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-hpux-shared examples.pro "CONFIG+=cexample1 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/compression/example1/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-hpux-shared examples.pro "CONFIG+=cexample2 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/compression/example2/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-hpux-shared examples.pro "CONFIG+=cexample3 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/compression/example3/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-hpux-shared examples.pro "CONFIG+=cexample4 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/compression/example4/Makefile-hpux-shared
REM %QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-hpux-shared examples.pro "CONFIG+=cexample5 libecwj2 sharedlink"
REM %FIXMCD% ../../examples/compression/example5/Makefile-hpux-shared


REM Mac OS X build files must be created on a Mac
REM set QMAKESPEC=macx-pbuilder
REM %QMAKECMD% -unix -o ../../examples/decompression/example1/Makefile-macosx-static examples.pro "CONFIG+=dexample1 libecwj2 staticlink"
REM %FIXCMD% ../../examples/decompression/example1/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/decompression/example2/Makefile-macosx-static examples.pro "CONFIG+=dexample2 libecwj2 staticlink"
REM %FIXCMD% ../../examples/decompression/example2/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/decompression/example4/Makefile-macosx-static examples.pro "CONFIG+=dexample4 libecwj2 staticlink"
REM %FIXCMD% ../../examples/decompression/example4/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/compression/example1/Makefile-macosx-static examples.pro "CONFIG+=cexample1 libecwj2 staticlink"
REM %FIXCMD% ../../examples/compression/example1/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/compression/example2/Makefile-macosx-static examples.pro "CONFIG+=cexample2 libecwj2 staticlink"
REM %FIXCMD% ../../examples/compression/example2/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/compression/example3/Makefile-macosx-static examples.pro "CONFIG+=cexample3 libecwj2 staticlink"
REM %FIXCMD% ../../examples/compression/example3/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/compression/example4/Makefile-macosx-static examples.pro "CONFIG+=cexample4 libecwj2 staticlink"
REM %FIXCMD% ../../examples/compression/example4/Makefile-macosx-static
REM %QMAKECMD% -unix -o ../../examples/compression/example5/Makefile-macosx-static examples.pro "CONFIG+=cexample5 libecwj2 staticlink"
REM %FIXCMD% ../../examples/compression/example5/Makefile-macosx-static

set QMAKESPEC=win32-msvc.net
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example1/Dexample1-static.vcproj examples.pro "CONFIG+=dexample1 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example2/Dexample2-static.vcproj examples.pro "CONFIG+=dexample2 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example4/Dexample4-static.vcproj examples.pro "CONFIG+=dexample4 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example1/Cexample1-static.vcproj examples.pro "CONFIG+=cexample1 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example2/Cexample2-static.vcproj examples.pro "CONFIG+=cexample2 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example3/Cexample3-static.vcproj examples.pro "CONFIG+=cexample3 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example4/Cexample4-static.vcproj examples.pro "CONFIG+=cexample4 libecwj2 staticlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example5/Cexample5-static.vcproj examples.pro "CONFIG+=cexample5 libecwj2 staticlink"

%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example1/Dexample1-shared.vcproj examples.pro "CONFIG+=dexample1 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example2/Dexample2-shared.vcproj examples.pro "CONFIG+=dexample2 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/decompression/example4/Dexample4-shared.vcproj examples.pro "CONFIG+=dexample4 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example1/Cexample1-shared.vcproj examples.pro "CONFIG+=cexample1 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example2/Cexample2-shared.vcproj examples.pro "CONFIG+=cexample2 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example3/Cexample3-shared.vcproj examples.pro "CONFIG+=cexample3 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example4/Cexample4-shared.vcproj examples.pro "CONFIG+=cexample4 libecwj2 sharedlink"
%QMAKECMD% -win32 -tp vc -o ../../examples/compression/example5/Cexample5-shared.vcproj examples.pro "CONFIG+=cexample5 libecwj2 sharedlink"

set QMAKESPEC=%OLD_QMAKESPEC%
