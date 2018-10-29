// 12_4View.h : interface of the CMy12_4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_12_4VIEW_H__421B05E6_4145_4140_A37D_494A2CFD9596__INCLUDED_)
#define AFX_12_4VIEW_H__421B05E6_4145_4140_A37D_494A2CFD9596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy12_4View : public CView
{
protected: // create from serialization only
	CMy12_4View();
	DECLARE_DYNCREATE(CMy12_4View)

// Attributes
public:
	CMy12_4Doc* GetDocument();
	void	LoadBitmapFromResource();				// 从资源中载入位图
	void	ZoomOut();								// 缩小
	void	ZoomIn();								// 放大
	void	Rotate();									// 旋转90度
	void	Mirror();									// 镜像
	CDC*	CreateNewBitmap(int width, int height);	// 创建指定尺寸的位图
	CDC*	m_pDC;								// 位图DC
	int		m_nWidth;							// 位图宽度
	int		m_nHeight;							// 位图高度

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12_4View)
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
	virtual ~CMy12_4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy12_4View)
	afx_msg void OnOperMirror();
	afx_msg void OnOperReset();
	afx_msg void OnOperRotate();
	afx_msg void OnOperZoomin();
	afx_msg void OnOperZoomout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 12_4View.cpp
inline CMy12_4Doc* CMy12_4View::GetDocument()
   { return (CMy12_4Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12_4VIEW_H__421B05E6_4145_4140_A37D_494A2CFD9596__INCLUDED_)
