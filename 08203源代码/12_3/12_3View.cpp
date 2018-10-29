// 12_3View.cpp : implementation of the CMy12_3View class
//

#include "stdafx.h"
#include "12_3.h"

#include "12_3Doc.h"
#include "12_3View.h"

#include "wmpplayer4.h"
#include "wmpcontrols.h"
#include "wmpsettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy12_3View

IMPLEMENT_DYNCREATE(CMy12_3View, CView)

BEGIN_MESSAGE_MAP(CMy12_3View, CView)
	//{{AFX_MSG_MAP(CMy12_3View)
	ON_WM_CREATE()
	ON_COMMAND(ID_OPER_OPEN, OnOperOpen)
	ON_COMMAND(ID_OPER_PAUSE, OnOperPause)
	ON_COMMAND(ID_OPER_PLAY, OnOperPlay)
	ON_COMMAND(ID_OPER_STOP, OnOperStop)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy12_3View construction/destruction

CMy12_3View::CMy12_3View()
{
	// TODO: add construction code here
	m_pPlayer = new CWMPPlayer4;
	m_bPaused = FALSE;

}

CMy12_3View::~CMy12_3View()
{
	delete m_pPlayer;
}

BOOL CMy12_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy12_3View drawing

void CMy12_3View::OnDraw(CDC* pDC)
{
	CMy12_3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMy12_3View printing

BOOL CMy12_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy12_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy12_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy12_3View diagnostics

#ifdef _DEBUG
void CMy12_3View::AssertValid() const
{
	CView::AssertValid();
}

void CMy12_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy12_3Doc* CMy12_3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy12_3Doc)));
	return (CMy12_3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy12_3View message handlers

int CMy12_3View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	HCURSOR hCursor=::LoadCursor(NULL, IDC_ARROW);	// 获得标准箭头鼠标指针
	CRect rect;	
	GetClientRect(rect);							// 获得客户区大小	
	// 创建播放器
	m_pPlayer->Create(
		AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | 
			CS_DBLCLKS | CS_PARENTDC, hCursor, 0, 0),
		NULL, 
		WS_VISIBLE|WS_CHILD, 
		rect, this, 0);	
//	m_pPlayer->SetShowControls(FALSE); 	// 隐藏控制面板
	
	return 0;
}

void CMy12_3View::OnOperOpen() 
{
	// TODO: Add your command handler code here
	// 只允许打开多媒体文件	
	static char BASED_CODE szFilter[] = 
		"视频文件 (*.avi;*.mpg;*.mpeg)|*.avi;*.mpg;*.mpeg|"\
		"音频文件 (*.wav;*.mp3)|*.wav;*.mp3|";
	CFileDialog	fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);	
	if(fileDlg.DoModal() == IDOK)		
		m_strFile = fileDlg.GetPathName();			// 获得文件名		
	
}

void CMy12_3View::OnOperPause() 
{
	// TODO: Add your command handler code here
	// 判断是否处于暂停状态
	if(m_bPaused)
	{
		m_bPaused = FALSE;
		m_pPlayer->GetControls().play();
	}
	else
	{
		m_bPaused = TRUE;
		m_pPlayer->GetControls().pause();
	}
	
}

void CMy12_3View::OnOperPlay() 
{
	// TODO: Add your command handler code here
	m_bPaused = FALSE;
	m_pPlayer->GetControls().stop();
	m_pPlayer->GetSettings().SetAutoStart(TRUE);
	m_pPlayer->SetUrl(m_strFile);

}

void CMy12_3View::OnOperStop() 
{
	// TODO: Add your command handler code here
	m_bPaused = FALSE;
	m_pPlayer->GetControls().stop();
	
}

void CMy12_3View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CView::OnSize(nType, cx, cy);
	CRect rect;	
	GetClientRect(rect);	
	m_pPlayer->MoveWindow(rect);	
	
}
