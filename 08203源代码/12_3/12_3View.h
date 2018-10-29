// 12_3View.h : interface of the CMy12_3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_12_3VIEW_H__26BA0345_116E_437C_86AA_F200D767CB89__INCLUDED_)
#define AFX_12_3VIEW_H__26BA0345_116E_437C_86AA_F200D767CB89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWMPPlayer4;

class CMy12_3View : public CView
{
protected: // create from serialization only
	CMy12_3View();
	DECLARE_DYNCREATE(CMy12_3View)

// Attributes
public:
	CMy12_3Doc* GetDocument();
	CWMPPlayer4		* m_pPlayer;	// 播放器
	CString			m_strFile;	// 文件名
	BOOL			m_bPaused;  // 记录暂停状态

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12_3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMy12_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy12_3View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOperOpen();
	afx_msg void OnOperPause();
	afx_msg void OnOperPlay();
	afx_msg void OnOperStop();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 12_3View.cpp
inline CMy12_3Doc* CMy12_3View::GetDocument()
   { return (CMy12_3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12_3VIEW_H__26BA0345_116E_437C_86AA_F200D767CB89__INCLUDED_)
