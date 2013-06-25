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
** FILE:   	example2.c
** CREATED:	Tue 09/12/1999
** AUTHOR: 	David Hayward
** PURPOSE:	Reads an ECW file and writes it out again
** EDITS:
**
********************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include "NCSECWCompressClient.h"

// Structure to store client read data
typedef struct ReadInfo {
	NCSFileView *pNCSFileView;
	UINT8 **ppInputBandBufferArray;
	UINT32 nPercentComplete;
	// buffer to store an error message in (1024 is an arbitrary size)
	char pErrorBuffer[1024];
} ReadInfo;

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

// Print an error message

static void ReportError(char *format, ... )
{
	va_list args;
    va_start(args, format);

	fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
	fprintf(stderr, "\n");

    va_end(args);
}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

// Read callback function - called once for each input line

static BOOLEAN ReadCallback(NCSEcwCompressClient *pClient,
							UINT32 nNextLine,
							IEEE4 **ppOutputBandBufferArray)
{
	ReadInfo *pReadInfo = (ReadInfo *)pClient->pClientData;
	UINT32 nBand;
	NCSEcwReadStatus eReadStatus;

	eReadStatus = NCScbmReadViewLineBIL(pReadInfo->pNCSFileView,
										pReadInfo->ppInputBandBufferArray);
	if (eReadStatus != NCSECW_READ_OK) {
		sprintf(pReadInfo->pErrorBuffer, "Read error %d at line %d.",
				eReadStatus, nNextLine);
		return(FALSE);
	}

	for(nBand = 0; nBand < pClient->nInputBands; nBand++) {
		UINT32 nCell;
		UINT8 *pInputValue = pReadInfo->ppInputBandBufferArray[nBand];
		IEEE4 *pOutputValue = ppOutputBandBufferArray[nBand];

		// Compression needs input to be IEEE4
		for (nCell = 0; nCell < pClient->nInOutSizeX; nCell++) {
			*pOutputValue++ = (IEEE4)*pInputValue++;
		}
	}

	return(TRUE);	/* would return FALSE on an error */
}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

// Status callback function (OPTIONAL)

static void StatusCallback(NCSEcwCompressClient *pClient,
						   UINT32 nCurrentLine)
{
	ReadInfo *pReadInfo = (ReadInfo *)pClient->pClientData;
	UINT32 nPercentComplete = (nCurrentLine * 100) / (pClient->nInOutSizeY - 1);

	if (nPercentComplete != pReadInfo->nPercentComplete) {
		fprintf(stdout, "%%%ld Complete\r\n", nPercentComplete);
		fflush(stdout);
		pReadInfo->nPercentComplete = nPercentComplete;
	}
}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

// Cancel callback function (OPTIONAL)

static BOOLEAN CancelCallback(NCSEcwCompressClient *pClient)
{
	/* Return TRUE to cancel compression */
	return(FALSE);
}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

// main program

int main(int argc, char **argv)
{
	NCSEcwCompressClient *pClient;
	char *szInputFilename;
	char *szOutputFilename;
	NCSFileView *pNCSFileView;
	NCSFileViewFileInfo	*pNCSFileInfo;
	UINT8 *pReadBuffer;
	UINT8 **ppInputBandBufferArray;
	NCSError eError;
	INT32 nBand;
	IEEE4 fTargetCompressionOverride = 0.0;

	// Check user has specified a file on command line
	if (argc < 3 || argc > 4) {
		ReportError(
			"Usage: %s InputFilename OutputFilename [Target Compression]",
			argv[0]);
		exit(1);
	}
	else {
		szInputFilename = argv[1];
		szOutputFilename = argv[2];
		if (argc == 4) {
			fTargetCompressionOverride = (float)atof(argv[3]);
		}
	}

	// Initialize the ECW JPEG 2000 SDK libraries
	NCSecwInit();
	
	// Open the input file
	eError = NCScbmOpenFileView(szInputFilename, &pNCSFileView, NULL);
	if (eError != NCS_SUCCESS) {
		ReportError("Could not open view for file:%s, Error = %s",
			szInputFilename, NCSGetErrorText(eError));
		exit(1);
	}

	// Get input file information
	eError = NCScbmGetViewFileInfo(pNCSFileView, &pNCSFileInfo);
	if (eError != NCS_SUCCESS) {
		ReportError("Could not get file information for file:%s, Error = %s",
			szInputFilename, NCSGetErrorText(eError));
		exit(1);
	}

	// Set up the input band list and set the view
	{
		INT32 *pBandList;

		pBandList = (UINT32 *)malloc(sizeof(UINT32) * pNCSFileInfo->nBands);
		if (pBandList == NULL) {
			ReportError("Unable to malloc band list.");
			// NOTREACHED
		}
		for (nBand = 0; nBand < pNCSFileInfo->nBands; nBand++) {
			pBandList[nBand] = nBand;
		}

		// Set the view we want to read (the whole file)
		eError = NCScbmSetFileView(
			pNCSFileView,
			pNCSFileInfo->nBands,
			pBandList,
			0,
			0,
			pNCSFileInfo->nSizeX-1,
			pNCSFileInfo->nSizeY-1,
			pNCSFileInfo->nSizeX,
			pNCSFileInfo->nSizeY);
		if (eError != NCS_SUCCESS) {
			ReportError("Error setting file view: %s",
						NCSGetErrorText(eError));
			exit(1);
		}
	}

	// The read function wants an array of band buffers to store
	// the data in. We allocate one block of memory and then point
	// set up the band points to point to different locations within
	// it. Alternatively, we could allocate a separate buffer for each
	// band.

	pReadBuffer = (UINT8 *)malloc(sizeof(UINT8) *
								  pNCSFileInfo->nSizeX *
								  pNCSFileInfo->nBands);
	if (pReadBuffer == NULL) {
		ReportError("Could not malloc read buffer");
		exit(1);
	}

	ppInputBandBufferArray = (UINT8 **)malloc(sizeof(UINT8 *) *
								   pNCSFileInfo->nBands);
	if (ppInputBandBufferArray == NULL) {
		ReportError("Could not malloc band buffer array");
		exit(1);
	}

	for (nBand = 0; nBand < pNCSFileInfo->nBands; nBand++) {
		ppInputBandBufferArray[nBand] = pReadBuffer + 
			(nBand * pNCSFileInfo->nSizeX * sizeof(UINT8));
	}

	// Now set up the output side of the task. First we need to
	// allocate and set up a client structure for the compression

	if (pClient = NCSEcwCompressAllocClient()) {
		NCSError eError;
		ReadInfo CompressReadInfo;

		// output filename
		strcpy(pClient->szOutputFilename, szOutputFilename);

		// Set up the target compression
		if (fTargetCompressionOverride != 0.0) {
			// User has specified a compression
			pClient->fTargetCompression = fTargetCompressionOverride;
		}
		else {
			// Use the same compression it was originally compressed with
			pClient->fTargetCompression = (float)pNCSFileInfo->nCompressionRate;
		}
		
		// Set up the input dimensions
		pClient->nInOutSizeX = pNCSFileInfo->nSizeX;
		pClient->nInOutSizeY = pNCSFileInfo->nSizeY;
		pClient->nInputBands = pNCSFileInfo->nBands;

		// Currently there isn't a way to find out what type of file we have,
		// so we make a guess based on the # of input bands.
		if(pClient->nInputBands == 1) {
			pClient->eCompressFormat = COMPRESS_UINT8;
		}
		else if(pClient->nInputBands == 3) {
			pClient->eCompressFormat = COMPRESS_RGB;
		}
		else {
			pClient->eCompressFormat = COMPRESS_MULTI;
		}

		// Set up optional projection information
		pClient->fCellIncrementX = pNCSFileInfo->fCellIncrementX;
		pClient->fCellIncrementY = pNCSFileInfo->fCellIncrementY;
		pClient->fOriginX = pNCSFileInfo->fOriginX;
		pClient->fOriginY = pNCSFileInfo->fOriginY;
		pClient->eCellSizeUnits = pNCSFileInfo->eCellSizeUnits;
		strcpy(pClient->szDatum, pNCSFileInfo->szDatum);
		strcpy(pClient->szProjection, pNCSFileInfo->szProjection);

		// Specify the callbacks and client data ptr
		pClient->pReadCallback = ReadCallback;
		pClient->pStatusCallback = StatusCallback;
		pClient->pCancelCallback = CancelCallback;

		// Set up client data for read callback
		CompressReadInfo.pNCSFileView = pNCSFileView;
		CompressReadInfo.ppInputBandBufferArray = ppInputBandBufferArray;
		CompressReadInfo.nPercentComplete = 0;
		CompressReadInfo.pErrorBuffer[0] = '\0';
		pClient->pClientData = (void *)&CompressReadInfo;

		// Open the compression
		eError = NCSEcwCompressOpen(pClient, FALSE);
		if (eError != NCS_SUCCESS) {
			ReportError("NCSCompressOpen failed: %s", NCSGetErrorText(eError));
		}
		else {
			// Opened OK, now do the compression
			eError = NCSEcwCompress(pClient);
			if (eError == NCS_COULDNT_READ_INPUT_LINE) {
				ReportError("Compression error: %s (%s)",
					NCSGetErrorText(eError), CompressReadInfo.pErrorBuffer);
			}
			else if (eError != NCS_SUCCESS) {
				ReportError("Compression error: %s", NCSGetErrorText(eError));
			}
			else {		// Compressed ok

				// Close the compression
				eError = NCSEcwCompressClose(pClient);
				if (eError != NCS_SUCCESS) {
					ReportError("NCSEcwCompressClose failed: %s",
						NCSGetErrorText(eError));
				}

				// output stats
				fprintf(stdout, "Target ratio:    %.1lf\r\n"
								"Actual ratio:    %.1lf\r\n"
#ifdef WIN32
								"Output size:     %I64d bytes\r\n"
#else
								"Output size:     %lld bytes\r\n"
#endif
								"Time taken:      %.1lf seconds\r\n"
								"Data Rate:       %.1lf MB/s\r\n",
								pClient->fTargetCompression,
								pClient->fActualCompression,
								pClient->nOutputSize,
								pClient->fCompressionSeconds,
								pClient->fCompressionMBSec);
				fflush(stdout);
			}
		}

		// Free client
		NCSEcwCompressFreeClient(pClient);
	}
	else {
		// Couldn't alloc client structure
		ReportError("NCSEcwCompressAllocClient() failed!");
	}

	// Shutdown library resources
	NCSecwShutdown();
	
	fprintf(stdout, "Hit Enter to exit");
	fflush(stdout);
	fgetc(stdin);
	return(0);
}

/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/
