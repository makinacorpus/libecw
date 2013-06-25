/**********************************************************
* Copyright 1989-2004 Earth Resource Mapping Pty Ltd.
*
* This document contains unpublished source code of
* Earth Resource Mapping Pty Ltd. This notice does
* not indicate any intention to publish the source
* code contained herein.
*
* Use of this product is subject to End-User License Agreement for Earth
* Resource Mapping Software.  Use of the examples provided to design, develop,
* and test your own applications is bound by the terms of the license.  Please
* refer to license.txt under the program folder for the contents
* of the license. The license contains important rights and obligations and
* should be read carefully.  If you do not agree to be bound by the terms and
* conditions of the license, you must immediately uninstall and destroy all
* copies of the product.
*  
** FILE:   	example5.cpp
** CREATED:	wed 17/11/2004
** AUTHOR: 	Simon Cope
** PURPOSE:	ECW Compression SDK: recompression from ECW or JPEG 
**		2000 input to lossless JPEG 2000 output using C++ API
**		Demonstrates using a custom IO Stream
** EDITS:
**
********************************************************/

#include "NCSFile.h"

class CMyIOStream: public CNCSJPCIOStream {
public:
	CMyIOStream() {
		m_pFile = NULL;
	}
	virtual ~CMyIOStream() {
		Close();
	}

		/** 
		 * Open the stream on the specified file.
		 * @param		pName		Full Name of JP2 stream being parsed
		 * @param		bWrite		Open for writing flag.
		 * @return      CNCSError	NCS_SUCCESS, or error code on failure.
		 */
	virtual CNCSError Open(char *pName, bool bWrite = false) {
		if(!bWrite) {
			m_pFile = fopen(pName, "rb");
		} else {
			m_pFile = fopen(pName, "w+b");
		}
		if(m_pFile) {
			return(CNCSJPCIOStream::Open(pName, bWrite));
		}
		return(NCS_FILE_OPEN_FAILED);
	};
		/** 
		 * Close the stream.
		 * @return      CNCSError	NCS_SUCCESS, or error code on failure.
		 */
	virtual CNCSError Close() {
		if(m_pFile) {
			fclose(m_pFile);
			m_pFile = NULL;
		}
		return(CNCSJPCIOStream::Close());
	}

		/** 
		 * Seek on the file to the specified location.
		 * @param		offset		Signed 64bit offset to seek by
		 * @param		origin		Origin to calculate new position from.
		 * @return      bool		true, or false on failure.  Instance inherits CNCSError object containing error value.
		 */
	virtual bool NCS_FASTCALL Seek(INT64 offset, Origin origin = CURRENT) {
		switch(origin) {
			case CNCSJPCIOStream::START: return(0 == fseek(m_pFile, offset, SEEK_SET)); break;
			case CNCSJPCIOStream::CURRENT: return(0 == fseek(m_pFile, offset, SEEK_CUR)); break;
			case CNCSJPCIOStream::END: return(0 == fseek(m_pFile, offset, SEEK_END)); break;
		}
		return(false);
	}
		/** 
		 * Is stream seekable.
		 * @return      bool		true if seekable, or false if not.
		 */
	virtual bool NCS_FASTCALL Seek() {
		return(true);
	}
		/** 
		 * Get the current file pointer position.
		 * @return      INT64		Current file pointer position, or -1 on error.
		 */
	virtual INT64 NCS_FASTCALL Tell() {
		return(ftell(m_pFile));
	}
		/** 
		 * Get the total current size of the file, in bytes.
		 * @return      INT64		Size of the file, or -1 on error.
		 */
	virtual INT64 NCS_FASTCALL Size() {
		struct stat buf;
#ifdef WIN32
		if(fstat(_fileno(m_pFile), &buf) == 0) {
#else
		if(fstat(fileno(m_pFile), &buf) == 0) {
#endif
			return(buf.st_size);
		}
		return(-1);
	}

		/** 
		 * Read some data from the stream into the supplied buffer.
		 * @param		buffer		Buffer to read the data into
		 * @param		count		How many bytes of data to read.
		 * @return      bool		true, or false on failure.  Instance inherits CNCSError object containing error value.
		 */
	virtual bool NCS_FASTCALL Read(void* buffer, UINT32 count) {
        if (count == 0) return true;
		return (1 == fread(buffer, count, 1, m_pFile));
	}
		/** 
		 * Write some data to the stream.
		 * @param		buffer		Buffer of data to write to the stream
		 * @param		count		How many bytes of data to write to the stream.
		 * @return      bool		true, or false on failure.  Instance inherits CNCSError object containing error value.
		 */
	virtual bool NCS_FASTCALL Write(void* buffer, UINT32 count) {
        if (count == 0) return true;
		return (1 == fwrite(buffer, count, 1, m_pFile));
	}

private:
	FILE *m_pFile;
};

// CLosslessCompressor class
//
// A subclass of CNCSFile.
class CLosslessCompressor: public CNCSFile {
public:
	// Default constructor
	CLosslessCompressor() 
	{
		m_nPercentComplete = 0;
	};
	// Virtual destructor.  
	virtual ~CLosslessCompressor() {};

	// Lossless recompression
	virtual CNCSError Recompress(char *pSrcFile, char *pDstFile);

	// WriteReadLine, WriteStatus, and WriteCancel are inherited from the base CNCSFile class, 
	// and overriden to perform the compression.

	// WriteReadLine() - called by SDK once for each line read.  
	// The parameters passed are the next line number being read from the input, 
	// and a pointer to a buffer into which that line's data should be loaded by 
	// your code.
	//
	// The cell type of the buffer is the same as that passed into SetFileInfo() in the 
	// NCSFileViewFileInfoEx struct.
	virtual CNCSError WriteReadLine(UINT32 nNextLine, void **ppInputArray);

	// Status update function, called for each line output during compression, and therefore 
	// useful for updating progress indicators in the interface of an application.
	virtual void WriteStatus(UINT32 nCurrentLine);

	// A cancel function called by the SDK which will cancel the compression if it returns 
	// true.  We override it here without actually introducing cancel functionality.
	virtual bool WriteCancel();

private:
	// CNCSFile member variable that is used for our input file, which may be an ECW or JPEG 
	// 2000 file in this example.
	CNCSFile m_Src;
	CMyIOStream	m_IStream;
	CMyIOStream	m_OStream;
	int m_nPercentComplete;
};


CNCSError CLosslessCompressor::Recompress(char *pSrcFile, char *pDstFile)
{
	// First open the input file, and check to make sure it opened OK.
	CNCSError Error = m_IStream.Open(pSrcFile, false);
	if(Error == NCS_SUCCESS) {

		Error = ((CNCSJP2FileView&)m_Src).Open(&m_IStream, false);
		if(Error == NCS_SUCCESS) {

				//NCSFileViewFileInfoEx has basic info about the file - dimensions, bands, 
				//georeferencing information etc.
				NCSFileViewFileInfoEx *pInfo = m_Src.GetFileInfo();

				//Create some parameters for a SetView - in this case, since we 
				//are losslessly recompressing the entire file, we simply 
				//copy the extents of the input file.
				INT32 *Bands = new INT32[pInfo->nBands];
				for (INT32 nBand = 0; nBand < pInfo->nBands; nBand++)
					Bands[nBand] = nBand;
						
				UINT32 nWidth, nHeight;			
				IEEE8 fStartX, fStartY, fEndX, fEndY;
				
				nWidth = pInfo->nSizeX;
				nHeight = pInfo->nSizeY;
				fStartX = pInfo->fOriginX;
				fStartY = pInfo->fOriginY;
				
				fEndX = fStartX + pInfo->fCellIncrementX * nWidth;
				fEndY = fStartY + pInfo->fCellIncrementY * nHeight;

				Error = m_Src.SetView(pInfo->nBands, Bands,
									  nWidth, nHeight,
									  fStartX, 
									  fStartY,
									  fEndX,
									  fEndY);
				if(Error == NCS_SUCCESS) {
					//Copy the Source NCSFileViewFileInfoEx
					NCSFileViewFileInfoEx DstInfo = *pInfo;

					DstInfo.nCompressionRate = 1; //LOSSLESS for JPEG 2000 output
					
					//Call SetFileInfo to establish the file information we are going to 
					//use for compression.  The parameters used is the NCSFileViewFileInfoEx 
					//struct we have populated using metadata derived from our input raster.
					Error = SetFileInfo(DstInfo);
					if(Error == NCS_SUCCESS) {
						Error = m_OStream.Open(pDstFile, true);
						if(Error == NCS_SUCCESS) {
							//Open the output file.  The second parameter is whether we are opening 
							//in progressive read mode (no) and the third is whether we want to write 
							//a new JPEG 2000 or ECW file (yes).
							Error = CNCSJP2FileView::Open(&m_OStream);
								
							if(Error == NCS_SUCCESS) {
								//Create the output.  Will return NCS_USER_CANCELLED_COMPRESSION if WriteCancel() 
								//returns true, another error code if something goes wrong, or NCS_SUCCESS.
								Error = Write();
								if (Error == NCS_SUCCESS)
									fprintf(stdout,"Finished compression\n");
								else if (Error == NCS_USER_CANCELLED_COMPRESSION)
									fprintf(stdout,"Compression cancelled\n");
								else fprintf(stdout,"Error during compression: %s\n",Error.GetErrorMessage());
								fflush(stdout);
								Error = Close(true);
							}
						}
					} else {
						Error = NCS_COULDNT_ALLOC_MEMORY;
					}
				}
				delete Bands;	
		}
	}
	return(Error);
}

// This is called once for each output line.
// In this example, we can simply call ReadLineBIL on m_Src.
//
CNCSError CLosslessCompressor::WriteReadLine(UINT32 nNextLine, void **ppInputArray)
{
	NCSFileViewFileInfoEx *pInfo = GetFileInfo();
	return ((m_Src.ReadLineBIL(pInfo->eCellType, pInfo->nBands, ppInputArray) == NCSECW_READ_OK) ? NCS_SUCCESS : NCS_COULDNT_READ_INPUT_LINE);
}

// Status update.  In this example, we write the percentage complete to the standard 
// output at each 1% increment.   
//
// A GUI app would run a progress/status bar from this, but would normally only
// update the GUI every now and then since this could be called _many_ times on a large output.
// The correct approach would be to schedule a fixed number of updates and call them at even 
// intervals based on the output file size.
//
void CLosslessCompressor::WriteStatus(UINT32 nCurrentLine)
{
	NCSFileViewFileInfoEx *pInfo = GetFileInfo();

	UINT32 nPercentComplete = (UINT32)((nCurrentLine * 100)/(pInfo->nSizeY));
	if (nPercentComplete > m_nPercentComplete)
	{
		m_nPercentComplete = nPercentComplete;
		fprintf(stdout, "Completed %d%%\n", m_nPercentComplete);
		fflush(stdout);
	}
}

//Cancel check.  We always return false, but an application with a graphical user interface 
//could have a "Cancel" button that when pressed caused this to return true and halt the 
//compression process.
bool CLosslessCompressor::WriteCancel(void)
{
	// Return true to cancel compression - eg from a GUI cancel button.
	return false;
}

//main() - parse command line parameters, call CLosslessCompressor.Recompress().
extern "C" int main(int argc, char **argv)
{
	NCSecwInit();
	{
	
		CLosslessCompressor compressor;

		if(argc != 3) {
			fprintf(stdout,"Usage: %s <input file> <output file>\r\n", argv[0]);
			return(1);
		}

		char *pSrcFile = argv[1];
		char *pDstFile = argv[2];

		CNCSError Error = compressor.Recompress(pSrcFile, pDstFile);

		if(Error != NCS_SUCCESS) {
			fprintf(stderr, "Error: %s", Error.GetErrorMessage());
			return(1);
		}

	}
	NCSecwShutdown();

	return(0);
}
