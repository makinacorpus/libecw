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

// Example3.h : main header file for the EXAMPLE3 application
//

#if !defined(AFX_EXAMPLE3_H__05EC5C7F_F92D_4D56_A3F4_134071F3DB0D__INCLUDED_)
#define AFX_EXAMPLE3_H__05EC5C7F_F92D_4D56_A3F4_134071F3DB0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "NCSFileDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CExample3App:
// See Example3.cpp for the implementation of this class
//

class CExample3App : public CWinApp
{
public:
	CExample3App();
	afx_msg void OnFileOpen( );
	BOOL m_bProgressiveDisplay;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExample3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3_H__05EC5C7F_F92D_4D56_A3F4_134071F3DB0D__INCLUDED_)
