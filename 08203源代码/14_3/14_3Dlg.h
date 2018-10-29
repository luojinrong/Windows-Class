// 14_3Dlg.h : header file
//

#if !defined(AFX_14_3DLG_H__5D85AD90_6ACB_47D9_A29E_0305DEABF47A__INCLUDED_)
#define AFX_14_3DLG_H__5D85AD90_6ACB_47D9_A29E_0305DEABF47A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FTPTreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMy14_3Dlg dialog

class CMy14_3Dlg : public CDialog
{
// Construction
public:
	CMy14_3Dlg(CWnd* pParent = NULL);	// standard constructor
	~ CMy14_3Dlg ();
	CInternetSession*	m_pInetSession;
	CFtpConnection*		m_pFtpConnection;
	CImageList*			m_pImageList;

// Dialog Data
	//{{AFX_DATA(CMy14_3Dlg)
	enum { IDD = IDD_MY14_3_DIALOG };
	CFTPTreeCtrl	m_FtpTreeCtrl;
	CString	m_strAddress;
	UINT	m_uLevel;
	CString	m_strPass;
	UINT	m_uPort;
	CString	m_strUser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy14_3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy14_3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_14_3DLG_H__5D85AD90_6ACB_47D9_A29E_0305DEABF47A__INCLUDED_)
