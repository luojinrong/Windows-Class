// 12_3Doc.cpp : implementation of the CMy12_3Doc class
//

#include "stdafx.h"
#include "12_3.h"

#include "12_3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy12_3Doc

IMPLEMENT_DYNCREATE(CMy12_3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy12_3Doc, CDocument)
	//{{AFX_MSG_MAP(CMy12_3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12_3Doc construction/destruction

CMy12_3Doc::CMy12_3Doc()
{
	// TODO: add one-time construction code here

}

CMy12_3Doc::~CMy12_3Doc()
{
}

BOOL CMy12_3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy12_3Doc serialization

void CMy12_3Doc::Serialize(CArchive& ar)
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
// CMy12_3Doc diagnostics

#ifdef _DEBUG
void CMy12_3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy12_3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy12_3Doc commands
