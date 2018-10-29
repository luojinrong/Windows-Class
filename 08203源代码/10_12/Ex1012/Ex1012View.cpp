// Ex1012View.cpp : implementation of the CEx1012View class
//

#include "stdafx.h"
#include "Ex1012.h"

#include "Ex1012Doc.h"
#include "Ex1012View.h"

#include "CalDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx1012View

IMPLEMENT_DYNCREATE(CEx1012View, CView)

BEGIN_MESSAGE_MAP(CEx1012View, CView)
	//{{AFX_MSG_MAP(CEx1012View)
	ON_COMMAND(ID_CAL_SHOW, OnCalShow)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_CAL_EXIT, OnCalExit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx1012View construction/destruction

CEx1012View::CEx1012View()
{
	// TODO: add construction code here

}

CEx1012View::~CEx1012View()
{
}

BOOL CEx1012View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx1012View drawing

void CEx1012View::OnDraw(CDC* pDC)
{
	CEx1012Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx1012View printing

BOOL CEx1012View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx1012View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx1012View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx1012View diagnostics

#ifdef _DEBUG
void CEx1012View::AssertValid() const
{
	CView::AssertValid();
}

void CEx1012View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx1012Doc* CEx1012View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx1012Doc)));
	return (CEx1012Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx1012View message handlers

void CEx1012View::OnCalShow() 
{
	CCalDlg dlg;
	dlg.DoModal();
}

void CEx1012View::OnAppExit() 
{
	// TODO: Add your command handler code here
//	AfxMessageBox("haha");
	PostQuitMessage(0);
	
}

void CEx1012View::OnCalExit() 
{
	PostQuitMessage(0);
}
