REM Quick hack to fix the continuing issues with makefiles produced by Qmake.
REM This removes Qmake-dependent material from each generated file.

set INPUT_FILE=%1

perl -pi -e 's/Q:/\.\.\/\.\./g' %INPUT_FILE%
perl -pi -e 's/INCPATH\s+=\s+\S+\s+/INCPATH  = /g' %INPUT_FILE%
perl -pi -e 's/all:\s+\S+\s+/all: /g' %INPUT_FILE%
perl -pi -e 's/Makefile-.*//g' %INPUT_FILE%
perl -pi -e 's/\s+\$\(QMAKE\).*//g' %INPUT_FILE%
perl -pi -e 's/qmake:.*//g' %INPUT_FILE%
perl -pi -e 's/\s+@\$\(QMAKE\).*//g' %INPUT_FILE%
"C:\Program Files\dos2unix\dos2unix.exe" %INPUT_FILE%
if exist %INPUT_FILE%.bak del %INPUT_FILE%.bak
