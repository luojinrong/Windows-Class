// 14_3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "14_3.h"
#include "14_3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy14_3Dlg dialog

CMy14_3Dlg::CMy14_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy14_3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy14_3Dlg)
	m_strAddress = _T("");
	m_uLevel = 0;
	m_strPass = _T("");
	m_uPort = 0;
	m_strUser = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy14_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy14_3Dlg)
	DDX_Control(pDX, IDC_FTPTREE, m_FtpTreeCtrl);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_LEVEL, m_uLevel);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy14_3Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy14_3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SCAN, OnButtonScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy14_3Dlg message handlers

BOOL CMy14_3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// 初始化连接为空
	m_pFtpConnection = NULL;
	// 创建一个Session对象，该对象直到该程序退出才自动撤销
	CString str("ScanFTP By Jackflit");
	m_pInetSession = new CInternetSession(str, 1, PRE_CONFIG_INTERNET_ACCESS);
	if (!m_pInetSession)
{
		AfxMessageBox("创建Session失败", MB_OK);
		OnCancel();
	}
	// 创建树型控件使用的图片列表
	m_pImageList = new CImageList();
	m_pImageList->Create(16, 15, TRUE, 3, 2);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_ERROR);
	m_pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
	bitmap.DeleteObject();
	bitmap.LoadBitmap(IDB_DIR);
	m_pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
	bitmap.DeleteObject();
	bitmap.LoadBitmap(IDB_FILE);
	m_pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
	bitmap.DeleteObject();
	// 设置树型控件的图片列表
	m_FtpTreeCtrl.SetImageList(m_pImageList, TVSIL_NORMAL);
	m_FtpTreeCtrl.PopulateTree();			// 初始化树型控件
	// 设置其它Edit控件的默认值
	m_strAddress.Format("127.0.0.1");
	m_strUser.Format("a");
	m_strPass.Format("a");
	m_uPort = 21;
	m_uLevel = m_FtpTreeCtrl.m_nLevel;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy14_3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy14_3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy14_3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy14_3Dlg::OnButtonScan() 
{
	// TODO: Add your control notification handler code here
	UpdateData();							// 获得连接选项数据
	if (m_pFtpConnection != NULL) 			// 关闭前一次连接
		m_pFtpConnection->Close();
	delete m_pFtpConnection;
	m_pFtpConnection = NULL;
	try{
		// 建立连接
		m_pFtpConnection = m_pInetSession->GetFtpConnection(
				m_strAddress,				// 服务器地址
				m_strUser,				// 用户名
				m_strPass,				// 密码
				m_uPort);				// 端口
	}
	catch (CInternetException* pEx)
	{
		// 连接失败，显示失败原因
		TCHAR szErr[1024];
		if (pEx->GetErrorMessage(szErr, 1024))
			AfxMessageBox(szErr, MB_OK);
		else
			AfxMessageBox("连接失败", MB_OK);
		pEx->Delete();
		m_pFtpConnection = NULL;
	}
	if (m_pFtpConnection != NULL)
	{
		m_FtpTreeCtrl.m_nLevel = m_uLevel; 	// 连接成功，设置扫描层次
		m_FtpTreeCtrl.PopulateTree(m_pFtpConnection,"/"); 		// 开始扫描
	}
	else
		m_FtpTreeCtrl.PopulateTree();			// 连接失败，显示错误信息
	
}

CMy14_3Dlg::~ CMy14_3Dlg ()
{
	if(m_pImageList)
	{
		m_pImageList->DeleteImageList();
		delete m_pImageList;
	}
	if (m_pFtpConnection != NULL)
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
	}
	if (m_pInetSession != NULL)	
	{
		m_pInetSession->Close();
		delete m_pInetSession;
	}
}

