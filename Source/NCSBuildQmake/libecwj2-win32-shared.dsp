# Microsoft Developer Studio Project File - Name="libecwj2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libecwj2 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libecwj2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libecwj2.mak" CFG="libecwj2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libecwj2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libecwj2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libecwj2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../../lib"
# PROP BASE Intermediate_Dir "../../obj/win32-msvc/shared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../lib"
# PROP Intermediate_Dir "../../obj/win32-msvc/shared"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP -MD /W3 /I "..\..\Source\include" /I "..\..\Source\C\NCSEcw\lcms\include" /I "." /I "C:\Qt\3.3.4Evaluation\mkspecs\win32-msvc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D UNICODE /D _MBCS /D _UNICODE /D LIBECWJ2 /D QT_DLL  /FD /c -nologo -Zm200 -GX -O2  
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32  "imagehlp.lib"  "version.lib"  "Crypt32.lib"  "shlwapi.lib"  "ws2_32.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib" /dll  /out:"..\..\lib\libecwj2.dll"  /implib:"..\..\lib\libecwj2.lib" /NOLOGO /SUBSYSTEM:console /DLL delayimp.lib /DELAYLOAD:comdlg32.dll /DELAYLOAD:oleaut32.dll /DELAYLOAD:winmm.dll /DELAYLOAD:wsock32.dll /DELAYLOAD:winspool.dll 
# Begin Special Build Tool
SOURCE=$(InputPath)
PostBuild_Desc=Post Build Step
PostBuild_Cmds=	copy "$(TargetPath)" "..\..\bin"	
# End Special Build Tool


!ELSEIF  "$(CFG)" == "libecwj2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD CPP -MDd /W3 /GZ /ZI /Od /I "..\..\Source\include" /I "..\..\Source\C\NCSEcw\lcms\include" /I "." /I "C:\Qt\3.3.4Evaluation\mkspecs\win32-msvc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D UNICODE /D _MBCS /D _UNICODE /D LIBECWJ2 /D QT_DLL /FD /c -nologo -Zm200 -GX -Zi  
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32  "imagehlp.lib"  "version.lib"  "Crypt32.lib"  "shlwapi.lib"  "ws2_32.lib"  "kernel32.lib"  "user32.lib"  "gdi32.lib"  "comdlg32.lib"  "advapi32.lib"  "shell32.lib"  "ole32.lib"  "oleaut32.lib"  "uuid.lib"  "imm32.lib"  "winmm.lib"  "wsock32.lib"  "winspool.lib" /dll  /out:"..\..\lib\libecwj2.dll"  /implib:"..\..\lib\libecwj2.lib" /NOLOGO /SUBSYSTEM:console /DLL /pdbtype:sept /DEBUG 
# Begin Special Build Tool
SOURCE=$(InputPath)
PostBuild_Desc=Post Build Step
PostBuild_Cmds=	copy "$(TargetPath)" "..\..\bin"	
# End Special Build Tool


!ENDIF 

# Begin Target

# Name "libecwj2 - Win32 Release"
# Name "libecwj2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2BitsPerComponentBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2Box.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2CaptureResolutionBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2ChannelDefinitionBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2ColorSpecificationBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2ComponentMappingBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2ContiguousCodestreamBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2DataEntryURLBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2DefaultDisplayResolutionBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2File.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2FileTypeBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2FileView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2GMLGeoLocationBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2HeaderBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2ImageHeaderBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2IntellectualPropertyBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2PaletteBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2PCSBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2ResolutionBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2SignatureBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2SuperBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2UUIDBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2UUIDInfoBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2UUIDListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2WorldBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJP2XMLBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCCOCMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCCodeBlock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCCodingStyleParameter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCCODMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCCOMMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCComponentDepthType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCCRGMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCDCShiftNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCDump.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCEcwpIOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCEOCMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCEPHMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCFileIOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCICCNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCIOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCMainHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCMCTNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCMemoryIOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCMQCoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCNodeTiler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPacket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPacketLengthType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPaletteNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPLMMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPLTMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPOCMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPPMMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPPTMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCPrecinct.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCProgression.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCProgressionOrderType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCQCCMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCQCDMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCQuantizationParameter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCResample.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCResolution.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCRGNMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSegment.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSIZMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSOCMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSODMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSOPMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSOTMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCSubBand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCT1Coder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCTagTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCTilePartHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCTLMMarker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSJP2\NCSJPCYCbCrNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSOutputFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSRenderer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSWorldFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSAffineTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSBlockFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\ncscbm.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\ncscbmidwt.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\ncscbmnet.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\ncscbmopen.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\ncscbmpurge.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSEcw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\NCSEcw\NCSHuffmanCoder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\collapse_pyr.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\ecw_open.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\ecw_read.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\fileio_compress.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\fileio_decompress.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\build_pyr.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\pack.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\qmf_util.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\quantize.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\unpack.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmscnvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmserr.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsgamma.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsgmt.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsintrp.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsio1.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmslut.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsmatsh.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsmtrx.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsnamed.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmspack.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmspcs.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmssamp.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsvirt.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmswtpnt.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\lcms\src\cmsxform.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSGDT2\NCSGDTEpsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSGDT2\NCSGDTEPSGKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSGDT2\NCSGDTLocation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSnet\NCScnet2\connect.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSnet\NCScnet2\NCScnet.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSnet\NCScnet2\NCSWinHttp.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSnet\NCScnet2\packet.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSnet\NCScnet2\cnet2util.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\CNCSMetabaseEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\CNCSMultiSZ.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\exception_catch.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\main.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSCoordinateConverter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSCoordinateSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSCoordinateTransform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSCrypto.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSExtent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSExtents.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSObjectList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSRasterCoordinateConverter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSScreenPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSServerState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSWorldPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\quadtree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\timer.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSPrefsWin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSPrefs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\CNCSBase64Coder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\dynamiclib.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\error.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\file.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\log.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\malloc.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\mutex.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSBase64.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSMutex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\pool.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\queue.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\thread.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\util.c
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSUtil\NCSString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\C\NCSEcw\shared_src\compress.cpp
# End Source File
# Begin Source File

SOURCE=libecwj2.def
# End Source File

# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Source\include\ECW.h

# End Source File
# Begin Source File

SOURCE=..\..\Source\include\NCSMisc.h

# End Source File

# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group







# Begin Group "Generated"






# Prop Default_Filter "moc"
# End Group
# End Target
# End Project

