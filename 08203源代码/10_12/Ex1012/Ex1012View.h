// Ex1012View.h : interface of the CEx1012View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX1012VIEW_H__2971117D_CA88_4BFB_A2D1_837980785C4D__INCLUDED_)
#define AFX_EX1012VIEW_H__2971117D_CA88_4BFB_A2D1_837980785C4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx1012View : public CView
{
protected: // create from serialization only
	CEx1012View();
	DECLARE_DYNCREATE(CEx1012View)

// Attributes
public:
	CEx1012Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1012View)
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
	virtual ~CEx1012View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx1012View)
	afx_msg void OnCalShow();
	afx_msg void OnAppExit();
	afx_msg void OnCalExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex1012View.cpp
inline CEx1012Doc* CEx1012View::GetDocument()
   { return (CEx1012Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1012VIEW_H__2971117D_CA88_4BFB_A2D1_837980785C4D__INCLUDED_)
