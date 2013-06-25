AM_CPPFLAGS =	@LIBECWJ2_DEFS@ @LIBECWJ2_INCLUDES@ @LIBECWJ2_CFLAGS@
AM_CFLAGS = @LIBECWJ2_DEFS@ @LIBECWJ2_INCLUDES@ @LIBECWJ2_CFLAGS@

NCSTypesWithGnuDefs.h:	NCSGnuSystemDefs.h ../include/NCSTypes.h
	rm -f NCSTypesWithGnuDefs.h
	cp NCSGnuSystemDefs.h NCSTypesWithGnuDefs.h
	cat ../include/NCSTypes.h >> NCSTypesWithGnuDefs.h

install-data-local:	NCSTypesWithGnuDefs.h
		$(includeHEADERS_INSTALL) NCSTypesWithGnuDefs.h \
		$(DESTDIR)$(includedir)/NCSTypes.h

NCSECWSRC = \
	../C/NCSEcw/NCSJP2/NCSJP2.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2BitsPerComponentBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2Box.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2CaptureResolutionBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2ChannelDefinitionBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2ColorSpecificationBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2ComponentMappingBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2ContiguousCodestreamBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2DataEntryURLBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2DefaultDisplayResolutionBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2File.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2FileTypeBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2FileView.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2GMLGeoLocationBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2HeaderBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2ImageHeaderBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2IntellectualPropertyBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2PaletteBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2PCSBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2ResolutionBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2SignatureBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2SuperBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2UUIDBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2UUIDInfoBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2UUIDListBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2WorldBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJP2XMLBox.cpp \
	../C/NCSEcw/NCSJP2/NCSJPC.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCBuffer.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCCOCMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCCodeBlock.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCCodingStyleParameter.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCCODMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCCOMMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCComponent.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCComponentDepthType.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCCRGMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCDCShiftNode.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCDump.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCEcwpIOStream.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCEOCMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCEPHMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCFileIOStream.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCICCNode.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCIOStream.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCMainHeader.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCMCTNode.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCMemoryIOStream.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCMQCoder.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCNode.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCNodeTiler.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPacket.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPacketLengthType.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPaletteNode.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPLMMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPLTMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPOCMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPPMMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPPTMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCPrecinct.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCProgression.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCProgressionOrderType.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCQCCMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCQCDMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCQuantizationParameter.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCResample.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCResolution.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCRGNMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSegment.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSIZMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSOCMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSODMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSOPMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSOTMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCSubBand.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCT1Coder.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCTagTree.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCTilePartHeader.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCTLMMarker.cpp \
	../C/NCSEcw/NCSJP2/NCSJPCYCbCrNode.cpp \
	../C/NCSEcw/NCSEcw/NCSWorldFile.cpp \
	../C/NCSEcw/NCSEcw/NCSAffineTransform.cpp \
	../C/NCSEcw/NCSEcw/NCSBlockFile.cpp \
	../C/NCSEcw/NCSEcw/ncscbm.c \
	../C/NCSEcw/NCSEcw/ncscbmidwt.c \
	../C/NCSEcw/NCSEcw/ncscbmnet.c \
	../C/NCSEcw/NCSEcw/ncscbmopen.c \
	../C/NCSEcw/NCSEcw/ncscbmpurge.c \
	../C/NCSEcw/NCSEcw/NCSEcw.cpp \
	../C/NCSEcw/NCSEcw/NCSFile.cpp \
	../C/NCSEcw/NCSEcw/NCSHuffmanCoder.cpp \
	../C/NCSEcw/shared_src/collapse_pyr.c \
	../C/NCSEcw/shared_src/ecw_open.c \
	../C/NCSEcw/shared_src/ecw_read.c \
	../C/NCSEcw/shared_src/fileio_compress.c \
	../C/NCSEcw/shared_src/fileio_decompress.c \
	../C/NCSEcw/shared_src/build_pyr.c \
	../C/NCSEcw/shared_src/pack.c \
	../C/NCSEcw/shared_src/qmf_util.c \
	../C/NCSEcw/shared_src/quantize.c \
	../C/NCSEcw/shared_src/unpack.c \
	../C/NCSEcw/lcms/src/cmscnvrt.c \
	../C/NCSEcw/lcms/src/cmserr.c \
	../C/NCSEcw/lcms/src/cmsgamma.c \
	../C/NCSEcw/lcms/src/cmsgmt.c \
	../C/NCSEcw/lcms/src/cmsintrp.c \
	../C/NCSEcw/lcms/src/cmsio1.c \
	../C/NCSEcw/lcms/src/cmslut.c \
	../C/NCSEcw/lcms/src/cmsmatsh.c \
	../C/NCSEcw/lcms/src/cmsmtrx.c \
	../C/NCSEcw/lcms/src/cmsnamed.c \
	../C/NCSEcw/lcms/src/cmspack.c \
	../C/NCSEcw/lcms/src/cmspcs.c \
	../C/NCSEcw/lcms/src/cmssamp.c \
	../C/NCSEcw/lcms/src/cmsvirt.c \
	../C/NCSEcw/lcms/src/cmswtpnt.c \
	../C/NCSEcw/lcms/src/cmsxform.c \
	../C/NCSGDT2/NCSGDTEpsg.cpp \
	../C/NCSGDT2/NCSGDTEPSGKey.cpp \
	../C/NCSGDT2/NCSGDTLocation.cpp

NCSCNETSRC = \
	../C/NCSnet/NCScnet3/NCScnet.cpp \
	../C/NCSnet/NCScnet3/NCSGetPasswordDlg.cpp \
	../C/NCSnet/NCScnet3/NCSGetRequest.cpp \
	../C/NCSnet/NCScnet3/NCSPostRequest.cpp \
	../C/NCSnet/NCScnet3/NCSProxy.cpp \
	../C/NCSnet/NCScnet3/NCSRequest.cpp \
	../C/NCSnet/NCScnet3/NCSSocket.cpp

NCSUTILSRC = \
	../C/NCSUtil/CNCSBase64Coder.cpp \
	../C/NCSUtil/dynamiclib.c \
	../C/NCSUtil/error.c \
	../C/NCSUtil/file.c \
	../C/NCSUtil/log.cpp \
	../C/NCSUtil/malloc.c \
	../C/NCSUtil/mutex.c \
	../C/NCSUtil/NCSBase64.cpp \
	../C/NCSUtil/NCSError.cpp \
	../C/NCSUtil/NCSEvent.cpp \
	../C/NCSUtil/NCSLog.cpp \
	../C/NCSUtil/NCSMutex.cpp \
	../C/NCSUtil/NCSObject.cpp \
	../C/NCSUtil/NCSPrefs.cpp \
	../C/NCSUtil/NCSPrefsXML.cpp \
	../C/NCSUtil/NCSString.cpp \
	../C/NCSUtil/NCSThread.cpp \
	../C/NCSUtil/pool.c \
	../C/NCSUtil/prefs.c \
	../C/NCSUtil/queue.c \
	../C/NCSUtil/thread.c \
	../C/NCSUtil/util.c	

NCSECWCSRC = \
	../C/NCSEcw/shared_src/compress.cpp

lib_LIBRARIES =	../../lib/libecwj2.a

# The odd "____" prefixes to identifiers hereafter are caused by the 
# canonicalisation of the relative paths of the lib and bin directories.

______lib_libecwj2_a_SOURCES = \
	$(NCSECWSRC) \
	$(NCSCNETSRC) \
	$(NCSUTILSRC) \
	$(NCSECWCSRC)

# This hack forces the objects for the static build to have different
# names avoiding the collision that otherwise occurs
______lib_libecwj2_a_CPPFLAGS = $(AM_CPPFLAGS)
______lib_libecwj2_a_CFLAGS = $(AM_CFLAGS)

lib_LTLIBRARIES = ../../bin/libNCSEcw.la ../../bin/libNCSUtil.la ../../bin/libNCSCnet.la ../../bin/libNCSEcwC.la

______bin_libNCSEcw_la_LDFLAGS = @LIBECWJ2_SHARED_LDFLAGS@
______bin_libNCSUtil_la_LDFLAGS = @LIBECWJ2_SHARED_LDFLAGS@
______bin_libNCSCnet_la_LDFLAGS = @LIBECWJ2_SHARED_LDFLAGS@
______bin_libNCSEcwC_la_LDFLAGS = @LIBECWJ2_SHARED_LDFLAGS@

______bin_libNCSEcw_la_SOURCES = $(NCSECWSRC)
______bin_libNCSUtil_la_SOURCES = $(NCSUTILSRC)
______bin_libNCSCnet_la_SOURCES = $(NCSCNETSRC)
______bin_libNCSEcwC_la_SOURCES = $(NCSECWCSRC)


include_HEADERS = \
	../include/CNCSMetabaseEdit.h \
	../include/CNCSMultiSZ.h \
	../include/ECW.h \
	../include/JNCSEcwConfig.h \
	../include/JNCSFile.h \
	../include/NCSAffineTransform.h \
	../include/NCSArray.h \
	../include/NCSBase64.h \
	../include/NCSBlockFile.h \
	../include/NCSBuildNumber.h \
	../include/NCSCoordinateConverter.h \
	../include/NCSCoordinateSystem.h \
	../include/NCSCoordinateTransform.h \
	../include/NCSCrypto.h \
	../include/NCSDefs.h \
	../include/NCSDynamicLib.h \
	../include/NCSECWClient.h \
	../include/NCSECWCompress.h \
	../include/NCSECWCompressClient.h \
	../include/NCSEcw.h \
	../include/NCSError.h \
	../include/NCSErrors.h \
	../include/NCSEvent.h \
	../include/NCSExtent.h \
	../include/NCSExtents.h \
	../include/NCSFile.h \
	../include/NCSFileIO.h \
	../include/NCSGDTLocation.h \
	../include/NCSGeoTIFFBoxUtil.h \
	../include/NCSHelpContextID.h \
	../include/NCSHuffmanCoder.h \
	../include/NCSJP2Box.h \
	../include/NCSJP2File.h \
	../include/NCSJP2FileView.h \
	../include/NCSJP2SuperBox.h \
	../include/NCSJPC.h \
	../include/NCSJPCBuffer.h \
	../include/NCSJPCCOCMarker.h \
	../include/NCSJPCCODMarker.h \
	../include/NCSJPCCOMMarker.h \
	../include/NCSJPCCRGMarker.h \
	../include/NCSJPCCodeBlock.h \
	../include/NCSJPCCodingStyleParameter.h \
	../include/NCSJPCComponent.h \
	../include/NCSJPCComponentDepthType.h \
	../include/NCSJPCDCShiftNode.h \
	../include/NCSJPCDefs.h \
	../include/NCSJPCDump.h \
	../include/NCSJPCEOCMarker.h \
	../include/NCSJPCEPHMarker.h \
	../include/NCSJPCEcwpIOStream.h \
	../include/NCSJPCFileIOStream.h \
	../include/NCSJPCICCNode.h \
	../include/NCSJPCIOStream.h \
	../include/NCSJPCMCTNode.h \
	../include/NCSJPCMESNode.h \
	../include/NCSJPCMQCoder.h \
	../include/NCSJPCMainHeader.h \
	../include/NCSJPCMarker.h \
	../include/NCSJPCMemoryIOStream.h \
	../include/NCSJPCNode.h \
	../include/NCSJPCNodeTiler.h \
	../include/NCSJPCPLMMarker.h \
	../include/NCSJPCPLTMarker.h \
	../include/NCSJPCPOCMarker.h \
	../include/NCSJPCPPMMarker.h \
	../include/NCSJPCPPTMarker.h \
	../include/NCSJPCPacket.h \
	../include/NCSJPCPacketLengthType.h \
	../include/NCSJPCPaletteNode.h \
	../include/NCSJPCPrecinct.h \
	../include/NCSJPCProgression.h \
	../include/NCSJPCProgressionOrderType.h \
	../include/NCSJPCQCCMarker.h \
	../include/NCSJPCQCDMarker.h \
	../include/NCSJPCQuantizationParameter.h \
	../include/NCSJPCRCTNode.h \
	../include/NCSJPCRGNMarker.h \
	../include/NCSJPCRect.h \
	../include/NCSJPCResample.h \
	../include/NCSJPCResolution.h \
	../include/NCSJPCSIZMarker.h \
	../include/NCSJPCSOCMarker.h \
	../include/NCSJPCSODMarker.h \
	../include/NCSJPCSOPMarker.h \
	../include/NCSJPCSOTMarker.h \
	../include/NCSJPCSegment.h \
	../include/NCSJPCSubBand.h \
	../include/NCSJPCT1Coder.h \
	../include/NCSJPCTLMMarker.h \
	../include/NCSJPCTagTree.h \
	../include/NCSJPCTilePartHeader.h \
	../include/NCSJPCTypes.h \
	../include/NCSJPCYCbCr2RGBNode.h \
	../include/NCSLog.h \
	../include/NCSMalloc.h \
	../include/NCSMemPool.h \
	../include/NCSMisc.h \
	../include/NCSMutex.h \
	../include/NCSObject.h \
	../include/NCSObjectList.h \
	../include/NCSPackets.h \
	../include/NCSPoint.h \
	../include/NCSPrefs.h \
	../include/NCSQuadTree.h \
	../include/NCSQueue.h \
	../include/NCSRenderer.h \
	../include/NCSScreenPoint.h \
	../include/NCSServerState.h \
	../include/NCSString.h \
	../include/NCSThread.h \
	../include/NCSTimeStamp.h \
	../include/NCSTimer.h \
	../include/NCSUtil.h \
	../include/NCSWorldFile.h \
	../include/NCSWorldPoint.h \
	../include/NCScnet.h \
	../include/NCSnet.h \
	../include/gcs_erm.h \
	../include/gdt_pub.h \
	../include/gdt_stat.h \
	../include/pcs_erm.h \
	NCSGnuConfig.h

