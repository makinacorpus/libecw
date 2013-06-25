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

// Example3View.cpp : implementation of the CExample3View class
//

#include "stdafx.h"
#include "Example3.h"

#include "Example3Doc.h"
#include "Example3View.h"

#include "NCSUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample3View

IMPLEMENT_DYNCREATE(CExample3View, CView)

BEGIN_MESSAGE_MAP(CExample3View, CView)
//{{AFX_MSG_MAP(CExample3View)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_COMMAND(ID_FILE_PRINT, OnBeginPrinting)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnBeginPrinting)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnBeginPrinting)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample3View construction/destruction

CExample3View::CExample3View() {
    // TODO: add construction code here

}

CExample3View::~CExample3View() {}

BOOL CExample3View::PreCreateWindow(CREATESTRUCT& cs) {
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample3View drawing

void CExample3View::OnDraw(CDC* pDC) {
    NCSError eError;

    CExample3Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    if(pDoc->m_bHaveOpenECW) {
        if (!pDoc->m_bIsProgressive) {
            // if set to progressive mode, the Read is done in the Doc::RefreshUpdate
            eError = pDoc->ReadImage(m_nWindowWidth, m_nWindowHeight);
        } else {
            eError = NCS_SUCCESS;
        }
        if (eError == NCS_SUCCESS) {
            pDoc->DrawImage(pDC->m_hDC,
                            &m_Rect,
                            m_dTLX, m_dTLY,
                            m_dBRX, m_dBRY);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CExample3View printing

BOOL CExample3View::OnPreparePrinting(CPrintInfo* pInfo) {
    // default preparation
    return FALSE;//DoPreparePrinting(pInfo);
}

void CExample3View::OnBeginPrinting() {
    MessageBox(_T("Printing not implemented in this example"), _T("NCSRenderer Example"), MB_OK);
}

void CExample3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample3View diagnostics

#ifdef _DEBUG
void CExample3View::AssertValid() const {
    CView::AssertValid();
}

void CExample3View::Dump(CDumpContext& dc) const {
    CView::Dump(dc);
}

CExample3Doc* CExample3View::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample3Doc)));
    return (CExample3Doc*)m_pDocument;
}
#endif //_DEBUG

void CExample3View::OnInitialUpdate() {
    CView::OnInitialUpdate();

    SetView();
    Invalidate(TRUE);
}

void CExample3View::SetView() {
    CExample3Doc* pDoc = GetDocument();
    NCSError eError;
    INT32 BandsArray[3];
    INT32 i;
    INT32 nScreenWidth, nScreenHeight;
    double dWindowAspect, dImageAspect;

    if (!pDoc->m_bHaveOpenECW) {
        return;
    }

    // Get window dimensions
    GetClientRect(&m_Rect);
    m_nWindowWidth = m_Rect.right - m_Rect.left;
    m_nWindowHeight = m_Rect.bottom - m_Rect.top;

    nScreenWidth = pDoc->m_nWidth;
    nScreenHeight = pDoc->m_nHeight;

    dWindowAspect = (double)m_nWindowWidth/(double)m_nWindowHeight;
    dImageAspect = (double)(nScreenWidth)/(double)(nScreenHeight);

    // Adjust image dimensions to fit in window.  Also could adjust
    // window dimensions.
    if (dWindowAspect > dImageAspect) {
        nScreenWidth = (int)(nScreenHeight * dWindowAspect);
    } else {
        nScreenHeight = (int)(nScreenWidth / dWindowAspect);
    }

    pDoc->ConvertDatasetToWorld(0, 0, &m_dTLX, &m_dTLY);
    pDoc->ConvertDatasetToWorld(nScreenWidth-1, nScreenHeight-1, &m_dBRX, &m_dBRY);

    for(i = 0; i < pDoc->m_nNumberOfBands; i++) {
        BandsArray[i] = i;
    }
    eError = pDoc->SetView(pDoc->m_nNumberOfBands, BandsArray,
                           m_nWindowWidth, m_nWindowHeight,
                           m_dTLX, m_dTLY,
                           m_dBRX, m_dBRY);
}

void CExample3View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
    CExample3Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    if(pDoc->m_bHaveOpenECW) {
        if (!pDoc->m_bIsProgressive) {
            SetView();
        }
    }
}

void CExample3View::OnFileSave() {
    // TODO: Add your command handler code here
    OnFileSaveAs();

}

void CExample3View::OnFileSaveAs() {
	CExample3Doc* pDoc = GetDocument();

    if( pDoc->m_bHaveOpenECW ) {
        // extract filaname
        CString strFilename = "";
        strFilename = pDoc->GetECWUrl( pDoc->GetPathName() );
        CString strJPGName;
        if( strFilename.Left(5) == "ecwp:" ) {
            strJPGName = strFilename.Right( strFilename.GetLength()
                                            - strFilename.ReverseFind('/') - 1 );
            strJPGName = strJPGName.Left(
                             strJPGName.ReverseFind('.') );
        } else {
            strJPGName = strFilename.Left(
                             strFilename.ReverseFind('.') );
        }
        strJPGName += ".jpg";
        // Prompt user for filename
        CFileDialog *fileDLG = new CFileDialog(FALSE, _T("jpg"),
                                               strJPGName.GetBuffer(0) , OFN_HIDEREADONLY, _T("Jpeg Files (*.jpg)|*.jpg||"));
        if( fileDLG->DoModal() == IDOK ) {
            strJPGName = fileDLG->GetFileName();
            // Open file in non-progressive mode if not already
            if( pDoc->m_bIsProgressive ) {
                pDoc->Close(FALSE);
                NCSError eError = pDoc->Open((char*)strFilename.GetBuffer(0), FALSE);
                if( eError != NCS_SUCCESS )
                    return;

            }
            // SetView for image
            POSITION pos = pDoc->GetFirstViewPosition();
            if( pos != NULL ) {
                CExample3View* pView = (CExample3View*)pDoc->GetNextView(pos);
                pView->SetView();
            }
            // Write JPEG file of quality 50
            pDoc->WriteJPEG( CHAR_STRING(strJPGName.GetBuffer(0)), 50);
            // Re-Open file in progressive mode if needs be
            if( pDoc->m_bIsProgressive ) {
                pDoc->Close(FALSE);
                NCSError eError = pDoc->Open((char*)strFilename.GetBuffer(0), TRUE);
                if( eError != NCS_SUCCESS )
                    return;
            }
        } else
            return;
    } else
        return;

}

void CExample3View::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

void CExample3View::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

void CExample3View::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}
