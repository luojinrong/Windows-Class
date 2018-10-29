// 13_2Dlg.h : header file
//

#if !defined(AFX_13_2DLG_H__53558715_ACFB_4CD9_92C3_AA6CE6E16A05__INCLUDED_)
#define AFX_13_2DLG_H__53558715_ACFB_4CD9_92C3_AA6CE6E16A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy13_2Dlg dialog

class CMy13_2Dlg : public CDialog
{
// Construction
public:
	~CMy13_2Dlg();
	BOOL OpenCommand(CString sql);
	void UpdateList();
	void InitList();
	CString GetFieldValue(LPCTSTR lpFieldName);
	BOOL GetFieldValue(LPCTSTR lpFieldName, CString& strValue);
	BOOL IsOpen();
	BOOL IsConnected();
	void CreateDBAndTable();
	BOOL PutValue(LPCTSTR fieldName, LPCTSTR fieldValue);
	BOOL PutValue(LPCTSTR fieldName, COleDateTime fieldValue);
	BOOL PutValue(LPCTSTR fieldName, long fieldValue);
	BOOL PutValue(LPCTSTR fieldName, _variant_t fieldValue);
	void Close();
	BOOL Update();
	BOOL AddNew();
	BOOL OpenTable();
	void InitConnection();
	void TestComError(HRESULT hr);
	void DumpComError(_com_error &e);
	CMy13_2Dlg(CWnd* pParent = NULL);	// standard constructor

	ADOX::_CatalogPtr 	m_pCatalog;		// ADOX对象，用于建表
	_ConnectionPtr	m_pConnection;		// 数据库连接对象，用于保持连接
	_RecordsetPtr		m_pRs;				// 结果集对象，用于访问数据库

// Dialog Data
	//{{AFX_DATA(CMy13_2Dlg)
	enum { IDD = IDD_MY13_2_DIALOG };
	CListCtrl	m_List;
	CComboBox	m_Updown;
	CString	m_Order;
	CString	m_Query;
	CString	m_Value;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy13_2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy13_2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_13_2DLG_H__53558715_ACFB_4CD9_92C3_AA6CE6E16A05__INCLUDED_)
