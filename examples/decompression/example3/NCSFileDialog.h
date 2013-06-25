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

#if !defined(AFX_NCSFILEDIALOG_H__AFB49BA5_13D5_43FF_B700_BC6AEA19A3A6__INCLUDED_)
#define AFX_NCSFILEDIALOG_H__AFB49BA5_13D5_43FF_B700_BC6AEA19A3A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NCSFILEDLG_DEFAULT_BASE_KEY "Software\\Earth Resource Mapping\\Image Web Server"

#define NCSFILEDLG_PREF_KEYNAME "ECW File Dlg URL Pref %d"
#define MAX_NR_PREF_ENTRIES 6
// NCSFileDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNCSFileDialog dialog

class CNCSFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CNCSFileDialog)

public:
	CNCSFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	
	CString GetFileName(void);
	CString GetPathName(void);
	CString GetFileExt (void);
	BOOL GetProgressive();

	virtual BOOL OnFileNameOK();
private:

	CComboBox *m_pECWCombo;
	CButton *m_pProrgressiveCheck;
	BOOL m_bProgressive;
	TCHAR *pECWUrlFileName;
	BOOL m_bHaveECWUrl;

	virtual BOOL OnInitDialog();
	TCHAR *GetFilenamePref(void);
	void UpdatePrefs(const TCHAR *pFilename, BOOL bProgressive);
	static BOOL GetPrefString(TCHAR *pKeyName, TCHAR **pString);
	static BOOL GetPrefBool(TCHAR *pKeyName, BOOL *pbValue);
	static BOOL SetPrefString(TCHAR *pKeyName, TCHAR *pString);
	static BOOL SetPrefBool(TCHAR *pKeyName, BOOL bValue);

protected:
	//{{AFX_MSG(CNCSFileDialog)
	afx_msg void OnOpenUrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NCSFILEDIALOG_H__AFB49BA5_13D5_43FF_B700_BC6AEA19A3A6__INCLUDED_)
