// Ex1404Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex1404.h"
#include "Ex1404Dlg.h"

#include "snap.h"

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
// CEx1404Dlg dialog

CEx1404Dlg::CEx1404Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEx1404Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx1404Dlg)
	m_bProxy = FALSE;
	m_strURL = _T("");
	m_nCode = 0;
	m_strProxy = _T("");
	m_nPort = 0;
	m_strUser = _T("");
	m_strPass = _T("");
	m_strHTML = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEx1404Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx1404Dlg)
	DDX_Control(pDX, IDC_EDIT_PASS, m_editPass);
	DDX_Control(pDX, IDC_EDIT_USER, m_editUser);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_PROXY, m_editProxy);
	DDX_Check(pDX, IDC_CHECK_PROXY, m_bProxy);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strURL);
	DDX_Text(pDX, IDC_EDIT_CODE, m_nCode);
	DDX_Text(pDX, IDC_EDIT_PROXY, m_strProxy);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
	DDX_Text(pDX, IDC_EDIT_HTML, m_strHTML);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx1404Dlg, CDialog)
	//{{AFX_MSG_MAP(CEx1404Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_PROXY, OnCheckProxy)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx1404Dlg message handlers

BOOL CEx1404Dlg::OnInitDialog()
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
	m_strURL = "http://www.google.com";		// 默认网页
	m_strProxy = "ppmm.org";				// 代理地址
	m_nPort = 3128;							// 代理端口
	m_strUser = "jackflit";					// 代理用户
	m_strPass = "bhmwtbgl";					// 代理密码
	UpdateData(FALSE);						// 更新控件
	UpdateProxyButton();					// 更新按钮状态
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEx1404Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEx1404Dlg::OnPaint() 
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
HCURSOR CEx1404Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEx1404Dlg::UpdateProxyButton(){
	UpdateData();
	m_editProxy.EnableWindow(m_bProxy);
	m_editPort.EnableWindow(m_bProxy);
	m_editUser.EnableWindow(m_bProxy);
	m_editPass.EnableWindow(m_bProxy);
}

void CEx1404Dlg::OnCheckProxy() 
{
	UpdateProxyButton();	// TODO: Add your control notification handler code here
	
}

void CEx1404Dlg::OnButtonSnap() 
{
	// 更新数据
	UpdateData();
	// 如果地址为空则返回
    if (m_strURL.IsEmpty())
        return;
	// 显示等待鼠标
	CWaitCursor wait;
	// 显示状态
    SetDlgItemText(IDC_EDIT_STATUS,  _T("正在连接网站..."));
    CSnap snap;
	// 根据用户输入情况设置代理
	if(m_bProxy){
		snap.SetProxyPort(m_nPort);
		snap.SetProxyServer(m_strProxy);
		snap.SetProxyUser(m_strUser);
		snap.SetProxyUser(m_strPass);
		snap.SetUseProxy(true);
	}
	// 获取文件
    if (snap.GetFile(m_strURL, m_strHTML, _T("Snap By Jackflit"), GetDlgItem(IDC_EDIT_STATUS)))
        SetDlgItemText(IDC_EDIT_STATUS,  _T("下载成功"));
    else
        SetDlgItemText(IDC_EDIT_STATUS,  _T("下载失败"));
	// 获取HTTP代码	
	m_nCode = snap.GetPageStatusCode();
	// 更新代码和HTML显示
	UpdateData(FALSE);	// TODO: Add your control notification handler code here
	
}
