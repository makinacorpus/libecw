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

// NCSFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Example3.h"
#include "NCSFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNCSFileDialog

IMPLEMENT_DYNAMIC(CNCSFileDialog, CFileDialog)

CNCSFileDialog::CNCSFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	// Add our dialog template into the child dialog at the bottom
	// of the new explorer style file dialog.
	if (m_ofn.Flags & OFN_EXPLORER) {
		m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_NCS_URL_DIALOG);
		m_ofn.Flags |= OFN_ENABLETEMPLATE;
		m_ofn.Flags |= OFN_NOVALIDATE;
		m_ofn.hInstance = AfxGetResourceHandle();
		m_bHaveECWUrl= FALSE;
	}
}


BEGIN_MESSAGE_MAP(CNCSFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CNCSFileDialog)
	ON_BN_CLICKED(IDC_OPEN_URL, OnOpenUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CNCSFileDialog::OnOpenUrl() 
{
	TCHAR ComboString[512];

	// You can use DDX to map stuff automatically if you like.
	m_bProgressive = m_pProrgressiveCheck->GetCheck();
	m_pECWCombo->GetWindowText(ComboString, 512);
	pECWUrlFileName = STRDUP(ComboString);
	m_bHaveECWUrl = TRUE;

	// Update the registry
	UpdatePrefs(pECWUrlFileName, m_bProgressive);

	// Set the text into the text box, so the dialog will validate and close.
	if(GetParent()) {
		if(GetParent()->GetDlgItem(0x480)) {
			GetParent()->GetDlgItem(0x480)->SetWindowText(ComboString);
		}
		// Send an OK to the parent.
		GetParent()->SendMessage(WM_COMMAND, IDOK);
	}
}

BOOL CNCSFileDialog::OnFileNameOK( )
{
	BOOL bReturn;

	if (STRNICMP(m_ofn.lpstrFile, _T("ecwp://"), 7) == 0) {
		bReturn = 0;
	} else {
		bReturn = CFileDialog::OnFileNameOK();
	}

	return bReturn;
}

BOOL CNCSFileDialog::GetProgressive()
{
	return m_bProgressive;
}

CString CNCSFileDialog::GetPathName( )
{
	CString pFilename;

	if (m_bHaveECWUrl) {
		pFilename = pECWUrlFileName;
	}
	else {
		pFilename = m_ofn.lpstrFile;
	}
	return pFilename;
}
 
CString CNCSFileDialog::GetFileExt( )
{
	CString FileExt;

	if (m_bHaveECWUrl) {
		FileExt = "ecw";
	}
	else {
		FileExt = CFileDialog::GetFileExt();
	}
	return FileExt;
}

CString CNCSFileDialog::GetFileName( )
{
	CString pFilename;

	if (m_bHaveECWUrl) {
		INT32 nLen = STRLEN(pECWUrlFileName);
		if (nLen) {
			nLen--;
			while(pECWUrlFileName[nLen] && pECWUrlFileName[nLen] != '/') {
				nLen--;
			}
			if (pECWUrlFileName[nLen] == '/'){
				pFilename = &(pECWUrlFileName[++nLen]); 
			}
		}
	}
	else {
		pFilename = CFileDialog::GetFileName();
	}
	return pFilename;
}

BOOL CNCSFileDialog::OnInitDialog()
{
	TCHAR KeyName[256];
	TCHAR *pString = NULL;
	BOOL bIsProgressive = TRUE;
	int nIndex;
	TCHAR *pFilenamePref;

	CFileDialog::OnInitDialog();

	// Set up the combo box
	m_pECWCombo = (CComboBox *)GetDlgItem(IDC_URL_COMBO);
	pFilenamePref = GetFilenamePref();
	m_pECWCombo->SetWindowText(pFilenamePref);
	m_pECWCombo->SetExtendedUI(TRUE);
	m_pECWCombo->SetHorizontalExtent(100);
	m_pECWCombo->LimitText(0);

	// Populate the combo from the registry.
	for (nIndex=0; nIndex<6; nIndex ++) {		
		SPRINTF(KeyName, _T(NCSFILEDLG_PREF_KEYNAME), nIndex); 
		if (GetPrefString(KeyName, &pString)){
			m_pECWCombo->AddString(pString);
			free(pString);
		}
	}

	// Set up the check box
	m_bProgressive = FALSE;
	m_pProrgressiveCheck = (CButton *)GetDlgItem(IDC_PROG_CHECK);
	GetPrefBool(_T("ECW File Dlg Progressive"), &bIsProgressive);
	m_pProrgressiveCheck->SetCheck(bIsProgressive);
	return TRUE;
}

void CNCSFileDialog::UpdatePrefs(const TCHAR *pFilename, BOOL bProgressive)
{
	TCHAR *pFilenames[MAX_NR_PREF_ENTRIES];
	TCHAR *pString;
	TCHAR KeyName[128];
	BOOL bHavePref = FALSE;
	INT32 nIndex;

	// Read in the pref strings
	for (nIndex=0; nIndex<MAX_NR_PREF_ENTRIES; nIndex ++) {	
		SPRINTF(KeyName, _T(NCSFILEDLG_PREF_KEYNAME), nIndex); 
		pFilenames[nIndex] = NULL;
		if (GetPrefString(KeyName, &pString)){
			pFilenames[nIndex] = pString;
		}
	}

	// Make sure the pref doesnt already exist in the registry
	for (nIndex=0; nIndex<MAX_NR_PREF_ENTRIES-1; nIndex ++) {
		if (pFilenames[nIndex] && STRNCMP(pFilenames[nIndex], pFilename, STRLEN(pFilename)) == 0) {
			bHavePref = TRUE;
			break;
		}
	}

	// Write out the new pref strings, drop the last one.
	if (!bHavePref) {
		for (nIndex=0; nIndex<MAX_NR_PREF_ENTRIES-1; nIndex ++) {
			if (pFilenames[nIndex]) {
				SPRINTF(KeyName, _T(NCSFILEDLG_PREF_KEYNAME), nIndex+1); 
				SetPrefString(KeyName, pFilenames[nIndex]);
			}
		}
		SPRINTF(KeyName, _T(NCSFILEDLG_PREF_KEYNAME), 0);
		SetPrefString(KeyName, (TCHAR *)pFilename);
	}

	// Write out the progressive pref
	SetPrefBool(_T("ECW File Dlg Progressive"), bProgressive);
	
	// Clean up
	for (nIndex=0; nIndex<MAX_NR_PREF_ENTRIES; nIndex ++) {	
		if (pFilenames[nIndex] != NULL) {
			free(pFilenames[nIndex]);
		}
	}
	
	return;
}

TCHAR *CNCSFileDialog::GetFilenamePref(void)
{
	TCHAR *pString = NULL;
	TCHAR KeyName[128];

	SPRINTF(KeyName, _T(NCSFILEDLG_PREF_KEYNAME), 0); 
	GetPrefString(KeyName, &pString);

	return pString;
}

BOOL CNCSFileDialog::GetPrefString(TCHAR *pKeyName, TCHAR **pString)
{
	BOOL bReturn = FALSE;
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
					 _T(NCSFILEDLG_DEFAULT_BASE_KEY),
					 0,	
					 KEY_QUERY_VALUE,
					 &hKey) == ERROR_SUCCESS) {
		
		DWORD dwType;
		LPBYTE szValueBuffer[MAX_PATH];
		DWORD dwBufferSize = MAX_PATH;

		if (pKeyName) {
			if (RegQueryValueEx(hKey, 
								pKeyName, 
								NULL, 
								&dwType, 
								(unsigned char *) szValueBuffer, 
								&dwBufferSize) != ERROR_SUCCESS) {
				szValueBuffer[0] = '\0';
				bReturn = FALSE;
			} else {
				if (dwType == REG_SZ) {
					*pString = STRDUP((TCHAR *)szValueBuffer);
					bReturn = TRUE;
				} else { 
					*pString = NULL;
					bReturn = FALSE;
				}
			}
		}
		else {
			*pString = NULL;
			bReturn = FALSE;	
		}
		RegCloseKey(hKey);
	}
	else {
		*pString = NULL;
		 bReturn = FALSE;
	}

	return bReturn;
}

BOOL CNCSFileDialog::SetPrefString(TCHAR *pKeyName, TCHAR *pString)
{
	BOOL bReturn = FALSE;
	HKEY hKey;

	if (!pString || !pKeyName)
		return FALSE;

	if (RegCreateKeyEx(HKEY_CURRENT_USER,
					 _T(NCSFILEDLG_DEFAULT_BASE_KEY),
					 0,	
					 NULL,
					 REG_OPTION_NON_VOLATILE,
					 KEY_SET_VALUE ,
					 NULL,
					 &hKey,
					 NULL) == ERROR_SUCCESS) {
		
		if (RegSetValueEx(hKey, 
						  pKeyName, 
						  (DWORD)NULL, 
						  REG_SZ, 
						  (unsigned char *) pString, 
						  STRLEN(pString)) == ERROR_SUCCESS) {
			bReturn = TRUE;
		} else {
			bReturn = FALSE;
		}
		RegCloseKey(hKey);
	}
	else {
		 bReturn = FALSE;
	}


	return bReturn;
}

BOOL CNCSFileDialog::SetPrefBool(TCHAR *pKeyName, BOOL bValue)
{
	BOOL bReturn = FALSE;


	HKEY hKey;

	if (!pKeyName)
		return FALSE;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
					 _T(NCSFILEDLG_DEFAULT_BASE_KEY),
					 0,	
					 KEY_ALL_ACCESS,
					 &hKey) == ERROR_SUCCESS) {
		
		if (RegSetValueEx(hKey, 
						  pKeyName, 
						  (DWORD)NULL, 
						  REG_DWORD, 
						  (BYTE *)&bValue, 
						  sizeof(INT32) ) == ERROR_SUCCESS) {
		
			bReturn = TRUE;
		} else {
			
			bReturn = FALSE;
		}
		RegCloseKey(hKey);
	}
	else {
		 bReturn = FALSE;
	}

	return bReturn;
}

BOOL CNCSFileDialog::GetPrefBool(TCHAR *pKeyName, BOOL *pbValue)
{
	BOOL bReturn = FALSE;
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_CURRENT_USER,
					 _T(NCSFILEDLG_DEFAULT_BASE_KEY),
					 0,	
					 KEY_QUERY_VALUE,
					 &hKey) == ERROR_SUCCESS) {
		
		DWORD dwType;
		DWORD buffer;
		DWORD dwBufferSize;

		buffer = 0;
		dwBufferSize = sizeof(DWORD);
		dwType = REG_DWORD;

		if (pKeyName) {
			if (RegQueryValueEx(hKey, 
								pKeyName, 
								NULL, 
								&dwType, 
								(LPBYTE) &buffer,
								&dwBufferSize) != ERROR_SUCCESS) {
				*pbValue = 0;
				bReturn = FALSE;
			}
			else {
				if (dwType == REG_DWORD) {
					*pbValue = (BOOL)buffer;	
				} else {
					*pbValue = 0;
					bReturn = TRUE;
				}
			}
		}
		else {
			*pbValue = 0;
			bReturn = FALSE;	
		}
		RegCloseKey(hKey);
	}
	else {
		*pbValue = 0;
		 bReturn = FALSE;
	}
	return bReturn;
}
