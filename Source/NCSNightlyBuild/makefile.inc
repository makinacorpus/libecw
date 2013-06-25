#################################################################
#
# Makefile.inc : rules for building NCS libraries and binaries on
#                UNIX-like systems. See also `makelibs.inc'.
#
# Supported platforms:
#	1) solaris (SunOS, gcc v3.3 compiler, gmake)
#
# Unsupported/experimental platforms:
#	2) hpux    (HP-UX, native "cc & aCC" compilers, gmake)
#	3) linux   (Linux, gcc v3.3 compiler, gmake)
#	4) macosx  (Darwin, MacOSX, gcc v3.3, gmake)
#
# All platforms need gmake to build. Most native make
# implemetations won't work.
#
# When building the libraries you may need to change the directory
# paths (e.g. those used by gcc as stored in $GCC_LIB_PATH), compiler
# and linker flags, versions of the compilers used, and additional 
# system libraries for a successful outcome.
#
# When porting to a platform that uses the POSIX api, define
# -DPOSIX on the command line and most of the NCS code will
# automatically compile.
#
# The make system uses a different compiler for C/C++, so if
# you are using one compiler for both, make sure the CFLAGS and
# LFLAGS stuff are identical for both compilers.
#
# HPUX support is currently compiled as 64 bit binaries for
# 64 bit HPUX 11, with `largefile' support.
#
# MacOSX/Darwin support is currently not implemented. It shouldnt
# be too difficult to compile since it's based on BSD. We already
# have a port of the libs for the old Carbon API, but as time moves
# on a native Darwin port will be developed.
#
#################################################################


#################################################################
#
# The logic below attempts to assign a library path for C and C++
# compilation based on the platform being used.  If your system 
# has a configuration that does not match one of those below you 
# may need to alter the value of GCC_LIB_PATH (for example) to 
# build the libraries.
#
#################################################################

platform := "$(shell uname -s)"

ifeq ($(platform), "SunOS")
	NCS_PLATFORM := solaris
	GCC_LIB_PATH=/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2
else 
ifeq ($(platform), "HP-UX")
	NCS_PLATFORM := hpux
else 
ifeq ($(platform), "Linux")
	NCS_PLATFORM := linux
# Suggested for Red Hat users
	GCC_LIB_PATH=/usr/lib/gcc/i386-redhat-linux/3.4.2/
# Suggested for Debian users with gcc-3.3 and g++-3.3 
#	GCC_LIB_PATH=/usr/lib/gcc-lib/i486-linux/3.3.5
else 
ifeq ($(platform), "Darwin")
	NCS_PLATFORM := macosx
endif
endif
endif
endif

#################################################################
#
#  Setup the source directories.
#
#################################################################

NCS_INC_PATH=$(NCSTOP)/Source/include
NCS_BIN_PATH=$(NCSTOP)/bin/$(NCS_PLATFORM)


NCS_LIB_PATH=$(NCS_BIN_PATH)
RELEASE_DIR=./Release/$(NCS_PLATFORM)
RELEASE_DEBUG_DIR=./ReleaseDebug/$(NCS_PLATFORM)
DEBUG_DIR=./Debug/$(NCS_PLATFORM)
SRC_DIR=../..

#################################################################
#
# Setup the flags for the C/C++ compiler
#
#################################################################

ifeq ($(NCS_PLATFORM), solaris)

CC=gcc
CXX=gcc
CFLAGS=-Wall -Wno-long-long -fpic -mno-app-regs -D_REENTRANT -DSOLARIS -DUNICODE -DPOSIX -shared -D_LARGEFILE64_SOURCE=1
CFLAGS+=-I$(NCS_INC_PATH) -I/usr/local/include/g++-v3
CXXFLAGS=-Wall -Wno-long-long -fpic -mno-app-regs -D_REENTRANT -DSOLARIS -DUNICODE -DPOSIX -shared -D_LARGEFILE64_SOURCE=1
CXXFLAGS+=-I$(NCS_INC_PATH) -I/usr/local/include/g++-v3

else 
ifeq ($(NCS_PLATFORM), hpux)

CC=cc
CXX=aCC
CFLAGS=-Wall -DHPUX -DUNICODE -DPOSIX +Z +O3 -Ae -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
CFLAGS+=-I$(NCS_INC_PATH) -I/usr/local/include/
CFLAGS+= +DA2.0W +DD64 -D_PSTAT64
CXXFLAGS= +O3 -AA -DHPUX -DUNICODE -DPOSIX +Z +W 829,921,430 -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
CXXFLAGS+=-I$(NCS_INC_PATH) -I/usr/local/include/ 
CXXFLAGS+= +DA2.0W +DD64 -D_PSTAT64
CXXFLAGS+=-DRWSTD_MULTI_THREAD -DRW_MULTI_THREAD 

else 
ifeq ($(NCS_PLATFORM), linux)

CC=gcc
CXX=gcc

CFLAGS=-Wall -Wno-long-long -fpic -DLINUX -DUNICODE -DPOSIX -shared
CFLAGS+=-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
CFLAGS+=-I$(NCS_INC_PATH) -I/usr/local/include/g++-v3
CXXFLAGS=-Wall -Wno-long-long -fpic -DLINUX -DUNICODE -DPOSIX -shared
CXXFLAGS+=-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
CXXFLAGS+=-I$(NCS_INC_PATH) -I/usr/local/include/g++-v3

else 
ifeq ($(NCS_PLATFORM), macosx)

#ERROR You must define the native build environment for Darwin/macosx
# A good first step is to use the POSIX preprocessor definition when compiling
CC=gcc
CXX=g++
CFLAGS=-Wall -Wno-long-long -DMACOSX -DUNICODE -DPOSIX
CFLAGS+=-I$(NCS_INC_PATH) -I/Developer/Headers/FlatCarbon/
CFLAGS+= -fno-common
CXXFLAGS=-Wall -Wno-long-long -DMACOSX -DUNICODE -DPOSIX
CXXFLAGS+=-I$(NCS_INC_PATH) -I/Developer/Headers/FlatCarbon/ 
CXXFLAGS+= -fno-common

endif
endif
endif
endif

#################################################################
#
# Setup the flags for the linker
#
#################################################################

ifeq ($(NCS_PLATFORM), solaris)

#LINK=/usr/ccs/bin/ld
LINK=gcc -shared
LFLAGS= -G -z defs -R.
LFLAGS+= -L/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2
LFLAGS+= -L/usr/local/lib -L$(NCS_LIB_PATH)

else 
ifeq ($(NCS_PLATFORM), hpux)

# Must use aCC as the linker, not ld for C++ shared libs.
LINK=aCC
LFLAGS= -b +inst_close -L/usr/lib -L/usr/local/lib -L$(NCS_LIB_PATH)
#64 bit native shared library
LFLAGS+= +DA2.0W +DD64

else 
ifeq ($(NCS_PLATFORM), linux)

#LINK=ld
#LFLAGS= -G -z defs -R.
LINK=gcc -shared
LFLAGS= -z defs
LFLAGS+= -L$(GCC_LIB_PATH) -L/usr/lib
LFLAGS+= -L/usr/local/lib -L$(NCS_LIB_PATH)

else 
ifeq ($(NCS_PLATFORM), macosx)
LINK=gcc
LFLAGS= -dynamiclib
LFLAGS+= -L/usr/lib
LFLAGS+= -L/usr/local/lib -L$(NCS_LIB_PATH)
LFLAGS+= /System/Library/Frameworks/Carbon.framework/Carbon

endif
endif
endif
endif

#################################################################
#
# Setup the object and source files. If your platform uses an
# extension for shared libraries other than .so, add it here.
#
#################################################################

OBJ2=$(SRC:.c=.o)
OBJ1=$(OBJ2:.CPP=.o)
OBJ=$(OBJ1:.cpp=.o)

ifeq ($(NCS_PLATFORM), hpux)

RELEASE_TARGET=$(TARGET).sl
DEBUG_TARGET=$(TARGET)d.sl

else 
ifeq ($(NCS_PLATFORM), macosx)

RELEASE_TARGET=$(TARGET).dylib
DEBUG_TARGET=$(TARGET)d.dylib
else

RELEASE_TARGET=$(TARGET).so
DEBUG_TARGET=$(TARGET)d.so

endif
endif

RELEASE_OBJ=$(OBJ:%=$(RELEASE_DIR)/%)
DEBUG_OBJ=$(OBJ:%=$(DEBUG_DIR)/%)
RELEASE_DEBUG_OBJ=$(OBJ:%=$(RELEASE_DEBUG_DIR)/%)

NCS_LIBS=

#################################################################
#
# Additional system libs. Add standard system/c/c++ libs that
# all libraries must link against here.
#
#################################################################

ifeq ($(NCS_PLATFORM), solaris)

LIBS= -lm -lc -ldl -lrt 
LIBS+= -lstdc++ -lsupc++ -lgcc_s $(GCC_LIB_PATH)/libgcc.a
#LIBS= -lc -lm -lrt -ldl 
#LIBS+= /usr/local/lib/libstdc++.a
#LIBS+= /usr/local/lib/libsupc++.a
#LIBS+= /usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/libgcc.a
#LIBS+= /usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/libgcc_eh.a

else 
ifeq ($(NCS_PLATFORM), hpux)

#LIBS+= -lm -lrt -ldld
#LIBS+= -lc
#LIBS+= -lstd_v2 -lstream -lCsup_v2

else 
ifeq ($(NCS_PLATFORM), linux)

LIBS= -lm -lc -lrt -ldl 
LIBS+= -lstdc++ -lgcc_s -lgcc
#LIBS+= -lstdc++ -lsupc++ -lgcc_s $(GCC_LIB_PATH)/libgcc.a
#LIBS+= -lstdc++ -lsupc++ -lgcc_s $(GCC_LIB_PATH)/crtbegin.o
#LIBS+= /usr/lib/gcc-lib/i386-redhat-linux/3.2/
#LIBS+= /usr/lib/gcc-lib/i386-redhat-linux/3.2/libstdc++.a
#LIBS+= /usr/lib/gcc-lib/i386-redhat-linux/3.2/libsupc++.a
#LIBS+= /usr/lib/gcc-lib/i386-redhat-linux/3.2/libgcc.a
#LIBS+= /usr/lib/gcc-lib/i386-redhat-linux/3.2/libgcc.a

else 
ifeq ($(NCS_PLATFORM), macosx)

LIBS= -lm -lc -ldl 
LIBS+= -lstdc++ -lgcc
endif
endif
endif
endif