// Ex1012Doc.h : interface of the CEx1012Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX1012DOC_H__4DD2DC87_1261_4DAD_BD6E_0E1F299A51DD__INCLUDED_)
#define AFX_EX1012DOC_H__4DD2DC87_1261_4DAD_BD6E_0E1F299A51DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEx1012Doc : public CDocument
{
protected: // create from serialization only
	CEx1012Doc();
	DECLARE_DYNCREATE(CEx1012Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1012Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx1012Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx1012Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1012DOC_H__4DD2DC87_1261_4DAD_BD6E_0E1F299A51DD__INCLUDED_)
