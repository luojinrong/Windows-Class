// 12_3Doc.h : interface of the CMy12_3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_12_3DOC_H__736168D5_1BB0_42F8_B4C3_5E18FC331BA4__INCLUDED_)
#define AFX_12_3DOC_H__736168D5_1BB0_42F8_B4C3_5E18FC331BA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy12_3Doc : public CDocument
{
protected: // create from serialization only
	CMy12_3Doc();
	DECLARE_DYNCREATE(CMy12_3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12_3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMy12_3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy12_3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12_3DOC_H__736168D5_1BB0_42F8_B4C3_5E18FC331BA4__INCLUDED_)
