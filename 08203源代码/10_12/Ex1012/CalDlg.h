#if !defined(AFX_CALDLG_H__C56B1C56_B5CB_42D0_9174_8AF87160C149__INCLUDED_)
#define AFX_CALDLG_H__C56B1C56_B5CB_42D0_9174_8AF87160C149__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalDlg dialog

class CCalDlg : public CDialog
{
// Construction
public:
	CCalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalDlg)
	enum { IDD = IDD_DIALOG_SHOW };
	CScrollBar	m_bar2;
	CScrollBar	m_bar1;
	int		m_edit1;
	int		m_edit2;
	CString	m_edit3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonSub();
	afx_msg void OnButtonMul();
	afx_msg void OnButtonDiv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALDLG_H__C56B1C56_B5CB_42D0_9174_8AF87160C149__INCLUDED_)
