// 12_4View.cpp : implementation of the CMy12_4View class
//

#include "stdafx.h"
#include "12_4.h"

#include "12_4Doc.h"
#include "12_4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy12_4View

IMPLEMENT_DYNCREATE(CMy12_4View, CView)

BEGIN_MESSAGE_MAP(CMy12_4View, CView)
	//{{AFX_MSG_MAP(CMy12_4View)
	ON_COMMAND(ID_OPER_MIRROR, OnOperMirror)
	ON_COMMAND(ID_OPER_RESET, OnOperReset)
	ON_COMMAND(ID_OPER_ROTATE, OnOperRotate)
	ON_COMMAND(ID_OPER_ZOOMIN, OnOperZoomin)
	ON_COMMAND(ID_OPER_ZOOMOUT, OnOperZoomout)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12_4View construction/destruction

CMy12_4View::CMy12_4View()
{
	// TODO: add construction code here
	m_pDC = NULL;
}

CMy12_4View::~CMy12_4View()
{
	if(m_pDC)
		delete m_pDC;
}

BOOL CMy12_4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy12_4View drawing

void CMy12_4View::OnDraw(CDC* pDC)
{
	CMy12_4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(m_pDC == NULL) 				// 第一次载入位图
		LoadBitmapFromResource();
	pDC->BitBlt(0, 0, m_nWidth, m_nHeight, m_pDC, 0, 0, SRCCOPY); // 绘制位图
}

/////////////////////////////////////////////////////////////////////////////
// CMy12_4View printing

BOOL CMy12_4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy12_4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy12_4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy12_4View diagnostics

#ifdef _DEBUG
void CMy12_4View::AssertValid() const
{
	CView::AssertValid();
}

void CMy12_4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12_4Doc* CMy12_4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12_4Doc)));
	return (CMy12_4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy12_4View message handlers

void CMy12_4View::LoadBitmapFromResource()
{
	
	if(m_pDC != NULL) 				// 释放DC
		delete m_pDC;
	CDC * pDesktopDC = CDC::FromHandle(::GetDC(NULL));	 // 获得桌面DC
	m_pDC = new CDC; 				// 创建新的DC，与当前DC兼容
	m_pDC->CreateCompatibleDC(pDesktopDC);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1); 	// 载入资源位图
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap); 			// 获得位图的尺寸，并保存
	m_nWidth = bitmap.bmWidth;
	m_nHeight = bitmap.bmHeight;
	m_pDC->SelectObject(bmp); 		// 将位图选入DC
	::ReleaseDC(::GetDesktopWindow(), pDesktopDC->GetSafeHdc());	// 释放桌面DC
}


void CMy12_4View::OnOperMirror() 
{
	// TODO: Add your command handler code here
	Mirror();
	Invalidate();
	UpdateWindow();
}

void CMy12_4View::OnOperReset() 
{
	// TODO: Add your command handler code here
	LoadBitmapFromResource();
	Invalidate();
	UpdateWindow();
}

void CMy12_4View::OnOperRotate() 
{
	// TODO: Add your command handler code here
	Rotate();
	Invalidate();
	UpdateWindow();
}

void CMy12_4View::OnOperZoomin() 
{
	// TODO: Add your command handler code here
	ZoomIn();
	Invalidate();
	UpdateWindow();
}

void CMy12_4View::OnOperZoomout() 
{
	// TODO: Add your command handler code here
	ZoomOut();
	Invalidate();
	UpdateWindow();
}


void CMy12_4View::Mirror()
{
	CDC* pDC = CreateNewBitmap(m_nWidth, m_nHeight);
	for(int i=0; i<m_nHeight; i++)
{
		for(int j=0; j<m_nWidth; j++)
			pDC->SetPixel(j, i, m_pDC->GetPixel(m_nWidth-1-j, i)); // 左右互换
	}
	delete m_pDC;
	m_pDC = pDC;
}

void CMy12_4View::ZoomIn()
{
	CDC* pDC = CreateNewBitmap(m_nWidth*2, m_nHeight*2);
	for(int i=0; i<m_nHeight*2; i++)
{
		for(int j=0; j<m_nWidth*2; j++)
			pDC->SetPixel(j, i, m_pDC->GetPixel(j/2,i/2)); 	// 新图(j, i):=原图(j/2, i/2)
	}
	m_nHeight = m_nHeight*2;
	m_nWidth = m_nWidth*2;
	delete m_pDC;
	m_pDC = pDC;
}


void CMy12_4View::ZoomOut()
{
	CDC* pDC = CreateNewBitmap(m_nWidth/2, m_nHeight/2);
	for(int i=0; i<m_nHeight/2; i++)
{
		for(int j=0; j<m_nWidth/2; j++)
			pDC->SetPixel(j, i, m_pDC->GetPixel(j*2,i*2)); // 新图(j, i):=原图(j*2, i*2)
	}
	m_nHeight = m_nHeight/2;
	m_nWidth = m_nWidth/2;
	delete m_pDC;
	m_pDC = pDC;
}


void CMy12_4View::Rotate()
{
	CDC* pDC = CreateNewBitmap(m_nHeight, m_nWidth);
	for(int i=0; i<m_nHeight; i++)
	{
		for(int j=0; j<m_nWidth; j++)
			pDC->SetPixel(i, j, m_pDC->GetPixel(j, -i+m_nHeight-1)); // 绕原点旋转并平移
	}
	int tmp = m_nHeight;
	m_nHeight = m_nWidth;
	m_nWidth = tmp;
	delete m_pDC;
	m_pDC = pDC;
}


CDC* CMy12_4View::CreateNewBitmap(int width, int height)
{
	CDC * pDesktopDC = CDC::FromHandle(::GetDC(NULL)); 	// 获得桌面DC
	CDC* pDC = new CDC; 								// 创建新DC
	pDC->CreateCompatibleDC(pDesktopDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDesktopDC, width, height); 	// 创建指定尺寸位图
	pDC->SelectObject(bmp); 								// 选择位图
	::ReleaseDC(::GetDesktopWindow(), pDesktopDC->GetSafeHdc());	// 释放桌面DC
	return pDC;
}
