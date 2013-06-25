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

// Example3Doc.h : interface of the CExample3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE3DOC_H__08DB9318_CA5D_4E5D_B573_5FCE2C536F33__INCLUDED_)
#define AFX_EXAMPLE3DOC_H__08DB9318_CA5D_4E5D_B573_5FCE2C536F33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NCSRenderer.h"

class CExample3Doc : public CDocument, public CNCSRenderer
{
protected: // create from serialization only
	CExample3Doc();
	DECLARE_DYNCREATE(CExample3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExample3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	BOOLEAN m_bHaveOpenECW;
	BOOLEAN m_bIsProgressive;

	virtual void RefreshUpdate(NCSFileViewSetInfo *pViewSetInfo);
	TCHAR *GetECWUrl(const TCHAR *pFilename);

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3DOC_H__08DB9318_CA5D_4E5D_B573_5FCE2C536F33__INCLUDED_)
