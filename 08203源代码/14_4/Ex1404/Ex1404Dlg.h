// Ex1404Dlg.h : header file
//

#if !defined(AFX_EX1404DLG_H__88AD851D_A937_418F_A2BF_20C467B98C71__INCLUDED_)
#define AFX_EX1404DLG_H__88AD851D_A937_418F_A2BF_20C467B98C71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEx1404Dlg dialog

class CEx1404Dlg : public CDialog
{
// Construction
public:
	CEx1404Dlg(CWnd* pParent = NULL);	// standard constructor
	void UpdateProxyButton();			// ¸üÐÂ°´Å¥×´Ì¬
	
// Dialog Data
	//{{AFX_DATA(CEx1404Dlg)
	enum { IDD = IDD_EX1404_DIALOG };
	CEdit	m_editPass;
	CEdit	m_editUser;
	CEdit	m_editPort;
	CEdit	m_editProxy;
	BOOL	m_bProxy;
	CString	m_strURL;
	UINT	m_nCode;
	CString	m_strProxy;
	UINT	m_nPort;
	CString	m_strUser;
	CString	m_strPass;
	CString	m_strHTML;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1404Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx1404Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckProxy();
	afx_msg void OnButtonSnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1404DLG_H__88AD851D_A937_418F_A2BF_20C467B98C71__INCLUDED_)
