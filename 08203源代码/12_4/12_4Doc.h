// 12_4Doc.h : interface of the CMy12_4Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_12_4DOC_H__0915AE02_F880_419E_AAEF_89BC3CE7E98B__INCLUDED_)
#define AFX_12_4DOC_H__0915AE02_F880_419E_AAEF_89BC3CE7E98B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy12_4Doc : public CDocument
{
protected: // create from serialization only
	CMy12_4Doc();
	DECLARE_DYNCREATE(CMy12_4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12_4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMy12_4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy12_4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12_4DOC_H__0915AE02_F880_419E_AAEF_89BC3CE7E98B__INCLUDED_)
