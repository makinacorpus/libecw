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
***************************************************/

// Example3Doc.cpp : implementation of the CExample3Doc class
//

#include "stdafx.h"
#include "Example3.h"

#include "Example3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample3Doc

IMPLEMENT_DYNCREATE(CExample3Doc, CDocument)

BEGIN_MESSAGE_MAP(CExample3Doc, CDocument)
	//{{AFX_MSG_MAP(CExample3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample3Doc construction/destruction

CExample3Doc::CExample3Doc()
{
	m_bHaveOpenECW = FALSE;
	m_bIsProgressive = FALSE;

}

CExample3Doc::~CExample3Doc()
{
	if(m_bHaveOpenECW) {
		CNCSFile::Close(false);
	}
}

BOOL CExample3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample3Doc serialization

void CExample3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExample3Doc diagnostics

#ifdef _DEBUG
void CExample3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample3Doc commands

BOOL CExample3Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	NCSError eError;

	// The document framework munges up the name, rather than change MFC, just decode it here.
	lpszPathName = GetECWUrl(lpszPathName);
	m_bIsProgressive = ((CExample3App*)AfxGetApp())->m_bProgressiveDisplay;
	
	if(m_bHaveOpenECW) {
		CNCSFile::Close(false);
	}
	eError = Open(CHAR_STRING(lpszPathName), m_bIsProgressive);
	
	if (eError == NCS_SUCCESS) {
		m_bHaveOpenECW = TRUE;
	}

	if ((m_nNumberOfBands != 1)&&(m_nNumberOfBands != 3)) {
		Close(TRUE);
		::MessageBox(NULL, _T("Only 1 or 3 band data can be viewed in this sample."), _T("Example3"), MB_OK);
		m_bHaveOpenECW = FALSE;
	}

	return TRUE;
}

// Here we overwrite RefreshUpdate to Read the data and Invalidate the view
void CExample3Doc::RefreshUpdate(NCSFileViewSetInfo *pViewSetInfo)
{
	NCSError eError;

	eError = ReadImage(pViewSetInfo);

	if (eError == NCS_SUCCESS) {
		m_bHaveOpenECW = TRUE;
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			pView->Invalidate(FALSE);
		}
	}
	return;
}

// Fix the MFC path string to return the ecwp URL
TCHAR *CExample3Doc::GetECWUrl(const TCHAR *pInFilename)
{
	TCHAR Filename [1024];
	TCHAR *pFilename = NULL;
	TCHAR *pMarker = NULL;

	pMarker = STRSTR(pInFilename, _T("ecwp:"));
	if (!pMarker) {
		pMarker = STRSTR(pInFilename, _T("ECWP:"));
	}
	if (pMarker) {
		// The protocol
		SPRINTF(Filename, _T("%s"), _T("ecwp://"));
		pMarker+=6;

		while ((*pMarker == '\\') || (*pMarker == '/'))
			pMarker++;

		// copy the rest of the string
		STRNCPY(Filename+7, pMarker, _MAX_PATH);

		// Convert the slashes
		pMarker = Filename;
		while (*pMarker) {
			if (*pMarker == '\\') {
				*pMarker = '/';
			}
			pMarker++;
		}
		pFilename = STRDUP(Filename);
	}
	else {
		// Just copy the filename
		pFilename = STRDUP(pInFilename);
	}
	return pFilename;
}