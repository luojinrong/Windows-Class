// Ex1013Dlg.h : header file
//

#if !defined(AFX_EX1013DLG_H__6057F663_9B32_4CA0_AA0F_E840AA487B19__INCLUDED_)
#define AFX_EX1013DLG_H__6057F663_9B32_4CA0_AA0F_E840AA487B19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEx1013Dlg dialog

class CEx1013Dlg : public CDialog
{
// Construction
public:
	CEx1013Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEx1013Dlg)
	enum { IDD = IDD_EX1013_DIALOG };
	CString	m_edit1;
	CString	m_edit2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1013Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx1013Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1013DLG_H__6057F663_9B32_4CA0_AA0F_E840AA487B19__INCLUDED_)
