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
** FILE:   	ecw_example2.c
** CREATED:	5th April 1999
** AUTHOR: 	NCS
**
** PURPOSE:	Example program demonstrating use of the callback
**			based interface into the NCSECW Client Library.
**
** COMPILE:	To compile this example, use VC++ 6.0, and set
**			the following parameters under the Project Settings
**			menu:
**
**			DEBUG:
**				C,C++/Code Generation:		Debug Multithreaded DLL
**				Link/General/Object Files:	add "NCSecw.lib"
**			RELEASE:
**				C,C++/Code Generation:		Multithreaded DLL
**				Link/General/Object Files:	add "NCSecw.lib"
**
**			To run the program, specify a path to a local or
**			remote ECW file, for example:
**				ecwp://earth.ermapper.com/images/usa/SanDiego3i.ecw
**
** NOTES:
**	(1) This example demonstrates the CALLBACK interface into the NCSECW
**	library.  The application opens the view, then sets the view whenever
**	appropriate (these may be done at any time).
**
**	The library will call back to the application whenever a view
**	should be read. The application must ensure the image structures
**	match the view size in the callback (which may well be different
**	to recent set views that are still pending), and then read the
**	data for the view.
**
**	The library always performs the callback in a thread, so the application
**	automatically gets a thread safe interface into the library with
**	the CALLBACK approach.
**
**	(2) During the callback reads, if the library ever returns NCSECW_READ_CANCELLED
**	from a read, this means that the view has changed internally (or been closed),
**	in which case the application MUST return this value from the callback, and
**	MUST no longer access the view in any way in the callback routine (as it may
**	no longer exist).
**
**	(3) This example demonstrates the use of two image buffers, so that the main
**	application can refresh using one image buffer at any time, while the other
**	buffer is being read from the library.
**
**	(4) This example uses the RGB read call; you could instead use the BIP call if
**	you want to manage the exact bands (for example for 3D height) rather than
**	getting a RGB view regardless of source data.
**
 *******************************************************/

#define _CRTDBG_MAP_ALLOC 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "NCSECWClient.h"
#include "NCSErrors.h"
#ifdef WIN32
#include "crtdbg.h"
#endif // WIN32

#define RAND()		(((double)rand())/RAND_MAX)
#define MAX_WINDOW	500					// maximum window size for the demo

extern void NCSSleep(NCSTimeStampMs tsSleepTime);

/*
**	Set up a handy structure to track a view. You could use one of these
**	for each file view you currently have open. Each view tracks two
**	image buffers, so one can be used by the application to refresh a window
**	whenever desired, while the other image buffer reads the image from the NCSECW
**	library.
*/

typedef struct {
	UINT32	nFromX, nFromY, nToY, nToX;		// The image area covered by this image buffer
	UINT32	nViewSizeX, nViewSizeY;			// The size of this image buffer
	UINT8	*pImageArray;					// the image array to be written to for this setview
} MyImage;

typedef struct {
	char	*szInputFilename;
	NCSFileView			*pNCSFileView;		// the file view
	NCSFileViewFileInfo	*pFileInfo;			// file information, not view specific
	NCSFileViewSetInfo	*pViewInfo;			// view information, different for each view into the file
	// The last setview done. Kept so we can randomly change these for the example, otherwise not needed
	UINT32	nBands;
	UINT32	*pBandList;
	UINT32	nFromX, nFromY, nToY, nToX;
	UINT32	nViewSizeX, nViewSizeY;
	UINT32	nViewNum;
	// image flipping done with two images
	MyImage	*pReadImage;					// the image to be read into from the library
	MyImage	*pDisplayImage;					// the image to be displayed from by the application

	MyImage	Image0, Image1;					// images flipped, pointed to by pReadImage and pDisplayImage
} MyView;


static int ShowViews(MyView *pMyView, UINT32 nSetViewsToDo);
NCSEcwReadStatus ShowViewCallback(NCSFileView *pNCSFileView);
void ShowViewDisplay(MyView *pMyView);
void SetViewExtents(MyView *pMyView);

/*
**	Main() - open the file, do multiple SetViews on it
*/

int main(int argc, char **argv)
{
	MyView *pMyView;
       
	// initialize resources if we are linking statically
	NCSecwInit();

	pMyView	= (MyView *) calloc(1,sizeof(MyView));	// example logic requires structure starting as zero's

	// get input file name to display
	if (argc != 2) {
	  printf("Usage:  %s file.ecw\n", argv[0]);
	  return(1);
	}
	pMyView->szInputFilename = argv[1];
	pMyView->pReadImage = &pMyView->Image0;
	pMyView->pDisplayImage = &pMyView->Image1;
	pMyView->nViewSizeX = MAX_WINDOW;
	pMyView->nViewSizeY = MAX_WINDOW;

	if( ShowViews(pMyView, 20) ) {
		printf("ShowViews on %s returned with an error\n", pMyView->szInputFilename);
		return(1);
	}

	free(pMyView);

	// free initialized resources
	NCSecwShutdown();
	
	return(0);
}

/*
**	ShowViews() - open the file, do multiple SetViews on it
**
**	Program flow:
**		-	Open the View and get file size details
**		-	For nSetViews (simulating user input):
**			-	Do a SetView
**			-	Sleep for a while
**		-	Close the View and return
**
**	The routine that actually reads the view is the
**	ShowViewRefresh() function.
**	
*/

static int ShowViews(MyView *pMyView, UINT32 nSetViewsToDo)
{

	UINT32	nBands, nCount;
	NCSError nError;
	int nReturnValue = 0;

	nError = NCScbmOpenFileView(pMyView->szInputFilename,
										 &pMyView->pNCSFileView,
										 ShowViewCallback);
	if (nError != NCS_SUCCESS) {
		printf("Unable to open view for %s\n",pMyView->szInputFilename);
		printf("Error = %s\n", NCSGetErrorText(nError));
		return(1);
	}
	nError = NCScbmGetViewFileInfo(pMyView->pNCSFileView, &pMyView->pFileInfo);
	if (nError != NCS_SUCCESS) {
		printf("Unable to get file information for %s\n",pMyView->szInputFilename);
		printf("Error = %s\n", NCSGetErrorText(nError));
		return(1);
	}

	// Get the view specific info, so we can save a pointer to our image info for the callback to use
	nError = NCScbmGetViewInfo(pMyView->pNCSFileView, &pMyView->pViewInfo);
	if (nError != NCS_SUCCESS) {
		printf("Unable to get information for current view.\n");
		printf("Error = %s\n", NCSGetErrorText(nError));
		return(1);
	}

	pMyView->pViewInfo->pClientData = (void *) pMyView;

	printf("Opened view into %s\n",pMyView->szInputFilename);
	printf("Image size: [%d rows x %d colums x %d bands]\n",
		pMyView->pFileInfo->nSizeX,pMyView->pFileInfo->nSizeY,pMyView->pFileInfo->nBands);

	// set up band list. We could use anything here. For now, we just pick the
	// lowest 3 bands.
	nBands = pMyView->pFileInfo->nBands;
	if( nBands > 3 )
		nBands = 3;			// set to 3, because we are using the RGB output mode, so no point having more

	pMyView->pBandList = (UINT32 *) malloc(sizeof(UINT32) * nBands);
	for( nCount = 0; nCount < nBands; nCount ++ )
		pMyView->pBandList[nCount] = nCount;

	while(nSetViewsToDo--) {
		pMyView->nViewNum = nSetViewsToDo;
		SetViewExtents(pMyView);
		nError = NCScbmSetFileView(pMyView->pNCSFileView,
					nBands,pMyView->pBandList,
					pMyView->nFromX, pMyView->nFromY, pMyView->nToX, pMyView->nToY,
					pMyView->nViewSizeX, pMyView->nViewSizeY);
		if (nError != NCS_SUCCESS) {
			printf("Error setting view.\n");
			printf("Error = %s\n", NCSGetErrorText(nError));
			NCScbmCloseFileView(pMyView->pNCSFileView);
			return(1);
		}

		// Wait a random time - up to 5 seconds - before doing the next setview
		NCSSleep((UINT32)(5000 * RAND()));
	}

	// Note that there might still be pending read callbacks during a close. The library sorts it all out
	nError = NCScbmCloseFileView(pMyView->pNCSFileView);
	if (nError != NCS_SUCCESS) {
		printf("Error closing file view.\n");
		printf("Error = %s\n", NCSGetErrorText(nError));
		nReturnValue = 1;
	}

	free(pMyView->pBandList);
	if(pMyView->Image0.pImageArray)
		free(pMyView->Image0.pImageArray);
	if(pMyView->Image1.pImageArray)
		free(pMyView->Image1.pImageArray);

	return(nReturnValue);
}


/*
**	ShowViewRefresh() - refresh the view
**
**	This routine is called whenever the view needs to
**	be refreshed (decided by the library, based on what
**	imagery information is available or has been received).
*/

NCSEcwReadStatus ShowViewCallback(NCSFileView *pNCSFileView)
{
	NCSFileViewSetInfo	*pViewInfo;
	MyView *pMyView;
	UINT32	nViewX, nViewY;
	NCSEcwReadStatus	eReadStatus = NCSECW_READ_OK;
	MyImage *pReadImage;
	UINT32	nBytesPerLine;		// using Win32 style 4 byte boundaries for our example
	UINT8	*pRGBTriplets;

	// recover the pointer to our application image information
	NCScbmGetViewInfo(pNCSFileView, &pViewInfo);
	pMyView = (MyView *) pViewInfo->pClientData;
	pReadImage = pMyView->pReadImage;

	// Get the size of this view. Note this might be different from recent setviews
	nViewX = pViewInfo->nSizeX;
	nViewY = pViewInfo->nSizeY;

	/*
	**	Now see if the old bitmap size was different to this bitmap size.
	**	If so, free the old bitmap, and allocate a new one. We use the
	**	WIN32 BITMAP style here for demonstration (each line must end on a 4 byte boundary)
	*/
	nBytesPerLine = (nViewX * 3);
	nBytesPerLine += (nBytesPerLine % 4);	// round to a long word

	if( nViewX != pReadImage->nViewSizeX
	 || nViewY != pReadImage->nViewSizeY ) {
		if( pReadImage->pImageArray )
			free(pReadImage->pImageArray);
		pReadImage->pImageArray = (UINT8 *) malloc(3 * nViewY * nBytesPerLine);
		// If you have an internal error, best just to return an error to the library
		if( !pReadImage->pImageArray )
			return( NCSECW_READ_FAILED );
		pReadImage->nViewSizeX = nViewX;
		pReadImage->nViewSizeY = nViewY;
	}
	// Copy the extents, so when image flipping we can re-use them later even while
	// another image read is in progress
	pReadImage->nFromX = pViewInfo->nTopX;
	pReadImage->nFromY = pViewInfo->nLeftY;
	pReadImage->nToX = pViewInfo->nBottomX;
	pReadImage->nToY = pViewInfo->nRightY;

	pRGBTriplets = pReadImage->pImageArray;

	while(nViewY--) {
		eReadStatus = NCScbmReadViewLineRGB( pNCSFileView, pRGBTriplets);
		/*
		** IMPORTANT: If the read was CANCELLED, the view may no longer be
		** valid (or it was changed), so you must return with the status to the library,
		** and do no further reads
		*/
		if( eReadStatus == NCSECW_READ_CANCELLED ) {
			printf("*** Read was cancelled.\n");
			return( eReadStatus );
		}

		pRGBTriplets += nBytesPerLine;
	}

	printf("View #%d block stats: when set%4d, now%4d, missed%4d, in view%4d\n",
			pMyView->nViewNum,
			pViewInfo->nBlocksAvailableAtSetView,
			pViewInfo->nBlocksAvailable,
			pViewInfo->nMissedBlocksDuringRead,
			pViewInfo->nBlocksInView);

	// flip between the display and read images, and trigger a display
	pMyView->pReadImage	= pMyView->pDisplayImage;
	pMyView->pDisplayImage = pReadImage;
	ShowViewDisplay(pMyView);

	return(eReadStatus);
}

/*
**	Display the image. If you wish, you could do this in a different
**	thread.
*/

void ShowViewDisplay(MyView *pMyView)
{
	if (!pMyView->pDisplayImage->pImageArray) {
		return;		// no image to display at present
	}
	// now compute the image location on the window,
	// and display it
}


/*
**	SetViewExtents - works out some new extents. Typically driven
**	by the user. In this case, we pick random values
*/

void SetViewExtents(MyView *pMyView)
{
	UINT32	nFromX, nFromY, nToX, nToY;
	UINT32	nSize;

	srand( (unsigned)clock() );


	// Work out size of view area. Must be less than smallest axis, and greater than window size
	nSize = (pMyView->pFileInfo->nSizeX < pMyView->pFileInfo->nSizeY ? pMyView->pFileInfo->nSizeX : pMyView->pFileInfo->nSizeY);
	nSize = (UINT32) (nSize * RAND());

	if( nSize < MAX_WINDOW )
		nSize = MAX_WINDOW;

	nFromX = (UINT32) ((pMyView->pFileInfo->nSizeX - nSize) * RAND());
	nFromY = (UINT32) ((pMyView->pFileInfo->nSizeY - nSize) * RAND());
	nToX = nFromX + nSize;
	nToY = nFromY + nSize;

	pMyView->nFromX = nFromX;
	pMyView->nFromY = nFromY;
	pMyView->nToX = nToX;
	pMyView->nToY = nToY;

}
