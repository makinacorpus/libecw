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
** FILE:   	example1.c
** CREATED:	Tue 01/09/1999
** AUTHOR: 	Simon Cope
** PURPOSE:	ECW Compression SDK simple C Example
**			Creates an ECW v2.0 file in the current directory
**			based on image size defines below.
** EDITS:
**
********************************************************/

#include <stdio.h>
#include "NCSECWCompressClient.h"

/*
** Test image size
**
** Note: NOT limited to ^2 or square, we're just using that so we can create
** a simple pattern for the input
*/
#define TEST_NR_BANDS	3
#define TEST_WIDTH		500
#define TEST_HEIGHT		500

/*
** Structure to client read data
*/
typedef struct {
	UINT8		nPercent;
} ReadInfo;

/*
** Read callback function - called once for each input line
*/
static BOOLEAN ReadCallback(NCSEcwCompressClient *pClient,
							UINT32 nNextLine,
							IEEE4 **ppInputArray)
{
	ReadInfo *pRI = (ReadInfo*)pClient->pClientData;
	UINT32 nBand;

	for(nBand = 0; nBand < pClient->nInputBands; nBand++) {
		UINT32 nCell;
		IEEE4 *pLine = ppInputArray[nBand];

		if(pClient->nInputBands == 1) {
			/* 1 band, do a grid pattern */
			for(nCell = 0; nCell < pClient->nInOutSizeX; nCell++) {
				if(((nCell / 30) % 2 == nBand) || ((nNextLine / 30) % 2 == nBand)) {
					pLine[nCell] = 1000.0f;
				} else {
					pLine[nCell] = 0.0f;
				}
			}
		} else {
			for(nCell = 0; nCell < pClient->nInOutSizeX; nCell++) {
				if(((nCell / 30) % pClient->nInputBands == nBand) && 
				   ((nNextLine / 30) % pClient->nInputBands == nBand)) {
					pLine[nCell] = 1000.0f;
				} else {
					pLine[nCell] = 0.0f;
				}
			}
		}
	}
	return(TRUE);	/* would return FALSE on an error */
}

/*
** Status callback function (OPTIONAL)
*/
static void StatusCallback(NCSEcwCompressClient *pClient,
						   UINT32 nCurrentLine)
{
	ReadInfo *pRI = (ReadInfo*)pClient->pClientData;
	UINT32 nPercent = (nCurrentLine * 100) / (pClient->nInOutSizeY - 1);

	if(nPercent != pRI->nPercent) {
		fprintf(stdout, "%%%ld Complete\r\n", nPercent);
		fflush(stdout);
		pRI->nPercent = nPercent;
	}
}

/*
** Cancel callback function (OPTIONAL)
*/
static BOOLEAN CancelCallback(NCSEcwCompressClient *pClient)
{
	/* Return TRUE to cancel compression */
	return(FALSE);
}

/*
** main()
*/
int main(int argc, char **argv)
{
	NCSEcwCompressClient *pClient;

	if (argc != 2) 
	{
		fprintf(stderr,"Usage: %s <output filename>\r\n", argv[0]);
		exit(1);
	}

	/*
	** Initialize library resources
	*/
	NCSecwInit();
	
	/*
	** First we need to alloc a client structure
	*/
	if(pClient = NCSEcwCompressAllocClient()) {
		NCSError eError;
		ReadInfo RI = { 0 };

		/*
		** Set up the input dimensions
		*/
		pClient->nInputBands = TEST_NR_BANDS;
		pClient->nInOutSizeX = TEST_WIDTH;
		pClient->nInOutSizeY = TEST_HEIGHT;

		/*
		** Set format and ratio based on # of input bands
		**
		** Format can be:
		** COMPRESS_UINT8 (Grayscale)
		** COMPRESS_RGB   (RGB)
		** COMPRESS_MULTI (Multi band grayscale)
		** COMPRESS_YUV	  (YUV)
		*/
		if(pClient->nInputBands == 1) {
			pClient->eCompressFormat = COMPRESS_UINT8;
			pClient->fTargetCompression = 20.0f;
		} else if(pClient->nInputBands == 3) {
			pClient->eCompressFormat = COMPRESS_RGB;
			pClient->fTargetCompression = 10.0f;
		} else {
			pClient->eCompressFormat = COMPRESS_MULTI;
			pClient->fTargetCompression = 20.0f;
		}

		/*
		** Give output filename
		*/
		strcpy(pClient->szOutputFilename, argv[1]);

		/*
		** Specify the callbacks and client data ptr
		*/
		pClient->pReadCallback = ReadCallback;
		pClient->pStatusCallback = StatusCallback;
		pClient->pCancelCallback = CancelCallback;
		pClient->pClientData = (void*)&RI;

		/*
		** Open the compression
		*/
		eError = NCSEcwCompressOpen(pClient, FALSE);

		if(eError == NCS_SUCCESS) {
			/*
			** Opened OK, now do the compression
			*/
			eError = NCSEcwCompress(pClient);

			/*
			** Close the compression
			*/
			NCSEcwCompressClose(pClient);
		}
		if(eError == NCS_SUCCESS) {
			/*
			** Compressed OK, output stats
			*/
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
		} else {
			/*
			** Got an error, dump to stderr
			*/
			fprintf(stderr, "Compression error: %s\r\n", NCSGetErrorText(eError)); 
			fflush(stderr);
		}
		/*
		** Free client
		*/
		NCSEcwCompressFreeClient(pClient);
	} else {
		/*
		** Couldn't alloc client structure
		*/
		fprintf(stderr, "NCSEcwCompressAllocClient() failed!");
		fflush(stderr);
	}

	NCSecwShutdown();
	
	fprintf(stdout, "Hit Enter to exit");
	fflush(stdout);
	fgetc(stdin);
	return(0);
}
