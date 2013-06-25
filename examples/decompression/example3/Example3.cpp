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

// Example3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Example3.h"

#include "MainFrm.h"
#include "Example3Doc.h"
#include "Example3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample3App

BEGIN_MESSAGE_MAP(CExample3App, CWinApp)
	//{{AFX_MSG_MAP(CExample3App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CExample3App::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

void CExample3App::OnFileOpen()
{
	CNCSFileDialog *pNCSFileDlg = new CNCSFileDialog( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("ECW Compressed Images (*.ecw)|*.ecw|All Files (*.*)|*.*||"), GetMainWnd());
	TCHAR *pFilename;

	if (pNCSFileDlg->DoModal() == IDOK) {
		pFilename = STRDUP((LPCTSTR)pNCSFileDlg->GetPathName().GetBuffer(0));
		m_bProgressiveDisplay = pNCSFileDlg->GetProgressive();
		CWinApp::OpenDocumentFile (pFilename);
		free(pFilename);
	}
	delete pNCSFileDlg;
}

/////////////////////////////////////////////////////////////////////////////
// CExample3App construction

CExample3App::CExample3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CExample3App object

CExample3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CExample3App initialization

BOOL CExample3App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CExample3Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CExample3View));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CExample3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CExample3App message handlers

