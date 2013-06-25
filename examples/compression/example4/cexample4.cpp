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
** FILE:   	example4.cpp
** CREATED:	Fri 24/09/2004
** AUTHOR: 	Tom Lynch
** PURPOSE:	ECW Compression SDK: recompression from an input image whose 
**			format is supported by Microsoft GDI+ to ECW or JPEG 2000 output
** EDITS:
**
********************************************************/

#include <windows.h>
#include <gdiplus.h>
#include "NCSFile.h"

using namespace Gdiplus;

// CGdiplusRecompressor class
//
// A subclass of CNCSFile.
class CGdiplusRecompressor: public CNCSFile {
public:
	// Default constructor
	CGdiplusRecompressor() 
	{
		m_nPercentComplete = 0;
	};
	// Virtual destructor.  
	virtual ~CGdiplusRecompressor() {};

	// Lossless recompression
	virtual CNCSError Recompress(char *pSrcFile, char *pDstFile, UINT32 nRate);

	// WriteReadLine and WriteStatus are inherited from the base CNCSFile class, 
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

private:
	// Member variable used for our input file.  Here we use a GDI+ Bitmap, and so 
	// various raster formats can be used as input data, including TIFF, GIF, BMP, and JPEG.
	Bitmap *m_pSrc;
	int m_nPercentComplete;
};


CNCSError CGdiplusRecompressor::Recompress(char *pSrcFile, char *pDstFile, UINT32 nRate)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
   
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//First open the input file, and check to make sure it opened OK.
	wchar_t *pWideSrcFile = (wchar_t *)NCSMalloc(sizeof(wchar_t)*strlen(pSrcFile)+sizeof(wchar_t),true);
	
	printf("Input file: %s\n",pSrcFile);
	printf("Output file: %s\n",pDstFile);
	fflush(stdout);

	int nChars = strlen(pSrcFile);
#ifdef WIN32
	MultiByteToWideChar(CP_ACP, 0, (LPSTR)pSrcFile, -1, (LPWSTR)pWideSrcFile, nChars);
#else
	mbstowcs(pWideSrcFile, pSrcFile, nChars);
#endif

	m_pSrc = NULL;
	m_pSrc = Bitmap::FromFile(pWideSrcFile);

	if (m_pSrc == NULL) 
	{
		printf("Error opening input file\n");
		fflush(stdout);
		return (NCS_FILE_OPEN_FAILED);
	}

	//NCSFileViewFileInfoEx has basic info about the file - dimensions, bands, 
	//georeferencing information etc.
	NCSFileViewFileInfoEx *pDstInfo = (NCSFileViewFileInfoEx *)NCSMalloc(sizeof(NCSFileViewFileInfoEx), true);
	NCSFileViewFileInfoEx DstInfo = *pDstInfo;
	CNCSError Error;
			
	DstInfo.nSizeX = m_pSrc->GetWidth();
	DstInfo.nSizeY = m_pSrc->GetHeight();
	DstInfo.eCellType = NCSCT_UINT8;
	DstInfo.nBands = 3;
	DstInfo.nCompressionRate = nRate;
	DstInfo.eColorSpace = NCSCS_sRGB;
	DstInfo.szProjection = "RAW";
	DstInfo.szDatum = "RAW";
	DstInfo.eCellSizeUnits = ECW_CELL_UNITS_METERS;
	DstInfo.fCellIncrementX = 1.0;
	DstInfo.fCellIncrementY = 1.0;
	DstInfo.fOriginX = 0.0;
	DstInfo.fOriginY = 0.0;

	DstInfo.pBands = (NCSFileBandInfo *)(new NCSFileBandInfo[DstInfo.nBands]);
	for (int b = 0; b < DstInfo.nBands; b++)
	{
		DstInfo.pBands[b].nBits = 8;
		DstInfo.pBands[b].bSigned = false;
	}
	DstInfo.pBands[0].szDesc = "Red";
	DstInfo.pBands[1].szDesc = "Green";
	DstInfo.pBands[2].szDesc = "Blue";

	//Call SetFileInfo to establish the file information we are going to 
	//use for compression.  The parameters used are those from the NCSFileViewFileInfoEx 
	//struct we have populated using metadata derived from our input raster.
	Error = SetFileInfo(DstInfo);
	Error = Open(pDstFile, false, true);
	if(Error == NCS_SUCCESS) {
		Error = Write();
		if (Error == NCS_SUCCESS)
			fprintf(stdout,"Finished compression\n");
		else if (Error == NCS_USER_CANCELLED_COMPRESSION)
			fprintf(stdout,"Compression cancelled\n");
		else fprintf(stdout,"Error during compression: %s\n",Error.GetErrorMessage());
		fflush(stdout);
		Error = Close(true);
	}
	
	GdiplusShutdown(gdiplusToken);
	return(Error);
}

// This is called once for each output line.
// In this example the input data is obtained pixel by pixel from the input image 
// using the GetPixel method of the GDI+ Bitmap object created from the source image 
// file above.
//
CNCSError CGdiplusRecompressor::WriteReadLine(UINT32 nNextLine, void **ppInputArray)
{
	CNCSError Error = NCS_SUCCESS;
	Status PixelResult;
	Color Buffer;
	NCSFileViewFileInfoEx *pInfo = GetFileInfo();
	for (int nB = 0; nB < pInfo->nBands; nB++)
	{
		int nX;
		UINT8 *pLine = (UINT8 *)ppInputArray[nB];
		switch (nB)
		{
		case 0: 
			for (nX = 0; nX < pInfo->nSizeX; nX++)
			{
				PixelResult = m_pSrc->GetPixel(nX,nNextLine, &Buffer);
				if (PixelResult == Ok)
					pLine[nX] = (UINT8)Buffer.GetRed();
				else Error = NCS_FILEIO_ERROR;
			}
			break;
		case 1:
			for (nX = 0; nX < pInfo->nSizeX; nX++)
			{
				PixelResult = m_pSrc->GetPixel(nX,nNextLine, &Buffer);
				if (PixelResult == Ok)
					pLine[nX] = (UINT8)Buffer.GetGreen();
				else Error = NCS_FILEIO_ERROR;
			}
			break;
		case 2:
			for (nX = 0; nX < pInfo->nSizeX; nX++)
			{
				PixelResult = m_pSrc->GetPixel(nX,nNextLine, &Buffer);
				if (PixelResult == Ok)
					pLine[nX] = (UINT8)Buffer.GetBlue();
				else Error = NCS_FILEIO_ERROR;
			}
			break;
		}
	}

	return NCS_SUCCESS;
}

// Status update.  In this example, we write the percentage complete to the standard 
// output at each 1% increment.   
void CGdiplusRecompressor::WriteStatus(UINT32 nCurrentLine)
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

//main() - parse command line parameters, call CGdiplusRecompressor.Recompress().
extern "C" int main(int argc, char **argv)
{
	// Initialize library resources in case of static linkage
	NCSecwInit();
	{
	
		CGdiplusRecompressor compressor;

		if(argc != 4) {
			fprintf(stdout,"Usage: %s <input file> <output file> <ratio>\r\n", argv[0]);
			return(1);
		}

		char *pSrcFile = argv[1];
		char *pDstFile = argv[2];
		UINT32 nRate = atoi(argv[3]);

		CNCSError Error = compressor.Recompress(pSrcFile, pDstFile, nRate);

		if(Error != NCS_SUCCESS) {
			fprintf(stderr, "Error: %s", Error.GetErrorMessage());
			return(1);
		}

	}
	// Free resources
	NCSecwShutdown();

	return(0);
}
