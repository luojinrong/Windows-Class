#if !defined(AFX_FTPTREECTRL_H__7C742E57_3A6D_4B27_A2E5_2465CE8F6A0D__INCLUDED_)
#define AFX_FTPTREECTRL_H__7C742E57_3A6D_4B27_A2E5_2465CE8F6A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFTPTreeCtrl window

class CFTPTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CFTPTreeCtrl();

	// 用于保存FTP连接
	CFtpConnection* m_pFtpConnection;
	// 扫描的目录深度
	int	m_nLevel;
	// 扫描指定目录，将扫描结果插入hParent所表示的节点下
	void ExploreDir(const CString& strDir, HTREEITEM hParent, int nLevel=0);
	// 开始扫描
	void PopulateTree(CFtpConnection* pConnection = NULL,
			const CString& strDir = CString((LPCTSTR) NULL));


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFTPTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFTPTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFTPTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPTREECTRL_H__7C742E57_3A6D_4B27_A2E5_2465CE8F6A0D__INCLUDED_)
