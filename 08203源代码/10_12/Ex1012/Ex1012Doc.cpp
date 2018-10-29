// Ex1012Doc.cpp : implementation of the CEx1012Doc class
//

#include "stdafx.h"
#include "Ex1012.h"

#include "Ex1012Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx1012Doc

IMPLEMENT_DYNCREATE(CEx1012Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx1012Doc, CDocument)
	//{{AFX_MSG_MAP(CEx1012Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx1012Doc construction/destruction

CEx1012Doc::CEx1012Doc()
{
	// TODO: add one-time construction code here

}

CEx1012Doc::~CEx1012Doc()
{
}

BOOL CEx1012Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx1012Doc serialization

void CEx1012Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx1012Doc diagnostics

#ifdef _DEBUG
void CEx1012Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx1012Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx1012Doc commands
