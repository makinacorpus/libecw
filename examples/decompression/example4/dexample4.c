/****************************************************
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
** 
** FILE:   	example4.c
** CREATED:	26th October 2000
** AUTHOR: 	SJC
**
** PURPOSE:	Example program demonstrating use of the NCSecwSetIOCallbacks()
**			interface into the NCSECW library
**
** COMPILE:	To compile this example, use VC++ 6.0, and set
**			the following parameters under the Project Settings
**			menu:
**
**			DEBUG:
**				C,C++/Code Generation:		Debug Multithreaded DLL
**				Link/General/Object Files:	add "NCSecw.lib"
**
**			RELEASE:
**				C,C++/Code Generation:		Multithreaded DLL
**				Link/General/Object Files:	add "NCSecw.lib"
**
**			To run the program, specify a path to a local ECW file, for example:
**				c:/images/usa/SanDiego3i.ecw
**
** NOTES:
**	(1) This example demonstrates the BLOCKING interface into the NCSECW
**	library.  The application opens the view, reads the view, then closes
**	the view.
**
**	(2) This example uses the RGB read call.
**
**  (3) This example demonstrates use of the NCSecwSetIOCallbacks() call to
**      provide custom read routines.
**
 *******************************************************/

#ifndef HPUX
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#else
#include <stdio.h>
#include <stdlib.h>

#endif

#include "NCSECWClient.h"
#include "NCSErrors.h"

/*
** Define a basic struct to hold our FILE pointer
*/
typedef struct {
	FILE *pFile;
} MyDataStruct;

/*
** Open File CB - open the file, fill in MyDataStruct
*/
static NCSError NCS_CALL FileOpenCB(char *szFileName, void **ppClientData)
{
	MyDataStruct *pData;

	if(NULL != (pData = (MyDataStruct*)malloc(sizeof(MyDataStruct)))) {
		pData->pFile = fopen(szFileName, "rb");

		if(pData->pFile) {
			*ppClientData = (void*)pData;
			return(NCS_SUCCESS);
		}
		return(NCS_FILE_OPEN_FAILED);
	}
	return(NCS_COULDNT_ALLOC_MEMORY);
}

/*
** Close File CB - close file, free MyDataStruct
*/
static NCSError NCS_CALL FileCloseCB(void *pClientData)
{
	MyDataStruct *pData = (MyDataStruct*)pClientData;

	if(pData) {
		if(pData->pFile) {
			fclose(pData->pFile);
		}
		free((void*)pData);

		return(NCS_SUCCESS);
	}
	return(NCS_INVALID_PARAMETER);
}

/*
** Read File CB - read given length from current offset into buffer
*/
static NCSError NCS_CALL FileReadCB(void *pClientData, void *pBuffer, UINT32 nLength)
{
	MyDataStruct *pData = (MyDataStruct*)pClientData;

	if(pData && pData->pFile) {
		size_t nRead;
			
		nRead = fread(pBuffer, 1, nLength, pData->pFile);

		if(nRead == nLength) {
			return(NCS_SUCCESS);
		}
		return(NCS_FILEIO_ERROR);
	}
	return(NCS_INVALID_PARAMETER);
}

/*
** Seek File CB - seek file to given offset
*/
static NCSError NCS_CALL FileSeekCB(void *pClientData, UINT64 nOffset)
{
	MyDataStruct *pData = (MyDataStruct*)pClientData;

	if(pData && pData->pFile) {
		int nRet;
		
		nRet = fseek(pData->pFile, (long)nOffset, SEEK_SET);
			
		if(nRet == 0) {
			return(NCS_SUCCESS);
		}
		return(NCS_FILEIO_ERROR);
	}
	return(NCS_INVALID_PARAMETER);
}

/*
** Tell File CB - get the current file offset
*/
static NCSError NCS_CALL FileTellCB(void *pClientData, UINT64 *pOffset) 
{
	MyDataStruct *pData = (MyDataStruct*)pClientData;

	if(pData && pData->pFile && pOffset) {
		long nOffset;

		nOffset = ftell(pData->pFile);

		if(nOffset >= 0) {
			*pOffset = (UINT64)nOffset;
			return(NCS_SUCCESS);
		}
		
		// Error
		*pOffset = 0;

		if(errno == EBADF || errno == EINVAL) {
			return(NCS_INVALID_PARAMETER);
		} 
		return(NCS_FILEIO_ERROR);
	}
	return(NCS_INVALID_PARAMETER);	
}

/*
** main()
*/
int main(int argc, char **argv)
{
	NCSFileView *pNCSFileView;
	NCSFileViewFileInfo	*pNCSFileInfo;
	NCSError eError = NCS_SUCCESS;

	// Check params, output usage if wrong
	if (argc != 4) {
	  printf("Usage:  %s file.ecw width height\n", argv[0]);
	  return(1);
	}

	/*
	**  Initialize library explicitly in case of static linkage
	*/
	NCSecwInit();

	/*
	** Set up the callbacks
	*/
	NCSecwSetIOCallbacks(FileOpenCB, FileCloseCB, FileReadCB, FileSeekCB, FileTellCB);
	/*
	**	Open the input NCSFileView
	*/
	eError = NCScbmOpenFileView(argv[1], &pNCSFileView, NULL);

	if(eError == NCS_SUCCESS) {
		UINT32 Bands[3] = { 0, 1, 2 };
		INT32 nBands;
		UINT8 *pRGBTriplets;
		INT32 nTLX, nTLY;
		INT32 nBRX, nBRY;
		INT32 nWidth, nHeight;

		// Get the file info (width, height etc)
		NCScbmGetViewFileInfo(pNCSFileView, &pNCSFileInfo);

		// 1 or 3 bands only (RGB or Grayscale)
		nBands = pNCSFileInfo->nBands < 3 ? 1 : 3;

		// Setup view dimensions
		nTLX = 0;
		nTLY = 0;
		nBRX = pNCSFileInfo->nSizeX - 1;
		nBRY = pNCSFileInfo->nSizeY - 1;
		nWidth = MIN((INT32)pNCSFileInfo->nSizeX - 1, atoi(argv[2]));
		nHeight = MIN((INT32)pNCSFileInfo->nSizeY - 1, atoi(argv[3]));

		// Allocate scanline RGB triplet buffer
		pRGBTriplets = (UINT8 *) malloc(nWidth * 3);		// RGB triplet buffer

		if(pRGBTriplets) {
			// Set the view, using dimensions calculated above
			eError = NCScbmSetFileView(pNCSFileView, 
										nBands, Bands,
										nTLX, nTLY,			
										nBRX, nBRY,
										nWidth, nHeight);

			if(eError == NCS_SUCCESS) {
				INT32 nLine;

				// Read all scanlines
				for(nLine = 0; nLine < nHeight; nLine++) {
					NCSEcwReadStatus eStatus;

					eStatus = NCScbmReadViewLineRGB(pNCSFileView, pRGBTriplets);
					if(eStatus == NCSECW_READ_OK) {
						INT32 nCell;

						// Dump RGB triplets to stdout as HEX
						for(nCell = 0; nCell < nWidth; nCell++) {
							fprintf(stdout, "(%lx,%lx,%lx)", 
									(unsigned long)pRGBTriplets[nCell * 3], 
									(unsigned long)pRGBTriplets[nCell * 3 + 1], 
									(unsigned long)pRGBTriplets[nCell * 3 + 2]);
						}
					} else {
						// Abort on error
						eError = NCS_FILEIO_ERROR;
						break;
					}
				}
	
			}
			// free RGB triplet buffer
			free(pRGBTriplets);
		}
		// Close file view
		NCScbmCloseFileView(pNCSFileView);
	}
	if(eError != NCS_SUCCESS) {
		// We got an error, output message to stdout
		fprintf(stderr, "Error: %s\n", NCSGetErrorText(eError));
	}
	
	NCSecwShutdown();

	return(eError);
}
