// 12_4Doc.cpp : implementation of the CMy12_4Doc class
//

#include "stdafx.h"
#include "12_4.h"

#include "12_4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy12_4Doc

IMPLEMENT_DYNCREATE(CMy12_4Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy12_4Doc, CDocument)
	//{{AFX_MSG_MAP(CMy12_4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12_4Doc construction/destruction

CMy12_4Doc::CMy12_4Doc()
{
	// TODO: add one-time construction code here

}

CMy12_4Doc::~CMy12_4Doc()
{
}

BOOL CMy12_4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy12_4Doc serialization

void CMy12_4Doc::Serialize(CArchive& ar)
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
// CMy12_4Doc diagnostics

#ifdef _DEBUG
void CMy12_4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy12_4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy12_4Doc commands
