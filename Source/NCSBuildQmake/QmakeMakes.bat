@echo off
echo Creating libecwj2 (or NCSEcw, NCSUtil, NCScnet, NCSEcwC, and NCSEcwC_SDK) project files ...
set OLD_QMAKESPEC=%QMAKESPEC%
set QMAKESPEC=win32-msvc
set QMAKECMD=qmake.exe
set FIXCMD=call .\FixQmakeMakefile.bat
set ZIPFILE=Q:\Master\libecwj2.zip
set THISZIPCMD="C:\Program Files\Winzip\wzzip.exe" -rP %ZIPFILE%

%QMAKECMD% -win32 -tp vc -o libecwj2-win32-static.dsp libecwj2.pro "CONFIG+=libecwj2 staticlib"
%QMAKECMD% -win32 -tp vc -o libecwj2-win32-shared.dsp libecwj2.pro "CONFIG+=libecwj2 dll"

REM
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSEcw/NCSEcw/NCSEcw_Static/NCSEcwS_qmake.dsp libecwj2.pro "CONFIG+=NCSEcw staticlib"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSEcw/NCSEcw/NCSEcw_qmake.dsp libecwj2.pro "CONFIG+=NCSEcw dll com"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSnet/NCScnet2/NCScnet2_Static/NCScnetS_qmake.dsp "CONFIG+=NCScnet staticlib"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSnet/NCScnet2/NCScnet2_qmake.dsp libecwj2.pro "CONFIG+=NCScnet dll"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSUtil/NCSUtil_Static/NCSUtilS_qmake.dsp "CONFIG+=NCSUtil"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSUtil/NCSUtil_qmake.dsp libecwj2.pro "CONFIG+=NCSUtil dll"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSEcw/NCSEcwC/NCSEcwC_qmake.dsp "CONFIG+=NCSEcwC staticlib"
REM %QMAKECMD% -win32 -tp vc -o ../C/NCSEcw/NCSEcwC_SDK/NCSEcwC_SDK_qmake.dsp "CONFIG+=NCSEcwC dll"


set QMAKESPEC=linux-g++
%QMAKECMD% -unix -o Makefile-linux-static libecwj2.pro "CONFIG+=libecwj2 staticlib" 
%FIXCMD% Makefile-linux-static
%QMAKECMD% -unix -o Makefile-linux-shared libecwj2.pro "CONFIG+=libecwj2 dll"
%FIXCMD% Makefile-linux-shared


set QMAKESPEC=solaris-g++
%QMAKECMD% -unix -o Makefile-solaris-static libecwj2.pro "CONFIG+=libecwj2 staticlib"
%FIXCMD% Makefile-solaris-static
%QMAKECMD% -unix -o Makefile-solaris-shared libecwj2.pro "CONFIG+=libecwj2 dll"
%FIXCMD% Makefile-solaris-shared

REM set QMAKESPEC=hpux-acc
REM %QMAKECMD% -unix -o Makefile-hpux-static libecwj2.pro "CONFIG+=libecwj2 staticlib"
REM %FIXCMD% Makefile-hpux-static
REM %QMAKECMD% -unix -o Makefile-hpux-shared libecwj2.pro "CONFIG+=libecwj2 dll"
REM %FIXCMD% Makefile-hpux-shared

REM Mac OSX XCode files must be built on the mac itself
REM export QMAKESPEC=macx-g++
REM %QMAKECMD% -macx -spec ~/Qt.../mkspecs/macx-g++ -o Makefile-macx-static libecwj2.pro "CONFIG+=libecwj2 staticlib"
%FIXCMD% Makefile-macx-static
REM %QMAKECMD% -macx -spec ~/Qt.../mkspecs/macx-g++ -o Makefile-macx-shared libecwj2.pro "CONFIG+=libecwj2 dll"
%FIXCMD% Makefile-macx-shared

set QMAKESPEC=win32-msvc.net
%QMAKECMD% -win32 -tp vc -o libecwj2-win32-net-static.vcproj libecwj2.pro "CONFIG+=libecwj2 staticlib"
%QMAKECMD% -win32 -tp vc -o libecwj2-win32-net-shared.vcproj libecwj2.pro "CONFIG+=libecwj2 dll"

set QMAKESPEC=%OLD_QMAKESPEC%

Q:
cd \
IF EXIST obj del /s /q obj
MKDIR obj
MKDIR obj\linux-g++
MKDIR obj\solaris-g++
MKDIR obj\macx-pbuilder
MKDIR obj\shared
MKDIR obj\static
%THISZIPCMD% obj

cd \Source\NCSBuildQmake
