// Ex1402Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex1402.h"
#include "Ex1402Dlg.h"

#include "ListenSocket.h"
#include "ChatSocket.h"
#include "Msg.h"

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
// CEx1402Dlg dialog

CEx1402Dlg::CEx1402Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEx1402Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx1402Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListenSocket = NULL;
	m_pChatSocket = NULL;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
}

void CEx1402Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx1402Dlg)
	DDX_Control(pDX, IDC_EDIT_SEND, m_editSend);
	DDX_Control(pDX, IDC_EDIT_RECV, m_editRecv);
	DDX_Control(pDX, IDC_EDIT_TIP, m_editTip);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlIP);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnListen);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx1402Dlg, CDialog)
	//{{AFX_MSG_MAP(CEx1402Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, OnButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECV, OnButtonClearRecv)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx1402Dlg message handlers

BOOL CEx1402Dlg::OnInitDialog()
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
	m_nPort = 1234;					// 服务器端口为1234
	m_ctrlIP.SetAddress(127,0,0,1);	// 默认IP为本地回环
	JudgeButton();					// 设置按钮状态
	SetTip(CString("初始状态"));	// 设置当前状态
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEx1402Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEx1402Dlg::OnPaint() 
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
HCURSOR CEx1402Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEx1402Dlg::JudgeButton(){
	if(m_pListenSocket == NULL && m_pChatSocket == NULL){
		// 原始阶段
		m_btnConnect.EnableWindow(TRUE);	// 允许建立连接
		m_btnListen.EnableWindow(TRUE);		// 允许建立服务器
		m_btnClose.EnableWindow(FALSE);		// 禁止关闭客户端连接
		m_btnStop.EnableWindow(FALSE);		// 禁止停止服务器
		m_btnSend.EnableWindow(FALSE);		// 禁止发送
		m_editSend.EnableWindow(FALSE);		// 禁止接收输入
		return;
	}
	else if(m_pChatSocket != NULL){			
		// 进入聊天状态
		m_btnConnect.EnableWindow(FALSE);	// 禁止建立连接
		m_btnListen.EnableWindow(FALSE);	// 禁止建立服务器
		m_btnClose.EnableWindow(TRUE);		// 允许断开客户端连接
		m_btnStop.EnableWindow(FALSE);		// 禁止停止服务器
		m_btnSend.EnableWindow(TRUE);		// 允许发送
		m_editSend.EnableWindow(TRUE);		// 允许输入
		return;
	}
	else if(m_pListenSocket != NULL){
		// 进入服务器监听状态
		m_btnConnect.EnableWindow(FALSE);	// 禁止再建立连接
		m_btnListen.EnableWindow(FALSE);	// 禁止再建立服务器
		m_btnClose.EnableWindow(FALSE);		// 禁止关闭服务器连接
		m_btnStop.EnableWindow(TRUE);		// 允许停止服务器
		m_btnSend.EnableWindow(FALSE);		// 禁止发送
		m_editSend.EnableWindow(FALSE);		// 禁止输入
		return;
	}
}

void CEx1402Dlg::SetTip(CString str){
	m_editTip.SetWindowText(str);
}

void CEx1402Dlg::InitConnection(){
	m_pFile = new CSocketFile(m_pChatSocket);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
}

void CEx1402Dlg::ProcessAccept()
{
	// 创建新的通信Socket
	m_pChatSocket = new CChatSocket(this);

	if (m_pListenSocket->Accept(*m_pChatSocket)){
		// 服务器接收成功
		// 初始化连接
		InitConnection();
		// 关闭监听
		m_pListenSocket->Close();
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		// 设置按钮和提示信息
		JudgeButton();
		SetTip(CString("有客户连接"));
	}
	else{
		// 接收失败
		// 销毁服务器Socket和通信Socket
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		delete m_pChatSocket;
		m_pChatSocket = NULL;
		// 更新按钮和提示信息
		JudgeButton();
		SetTip(CString("连接失败"));
	}
}

void CEx1402Dlg::OnButtonListen() 
{
	// 创建服务器Socket在指定端口监听
	m_pListenSocket = new CListenSocket(this);
	if (m_pListenSocket->Create(m_nPort)){
		// 创建成功
		if (m_pListenSocket->Listen()){
			// 正在监听...
			JudgeButton();
			SetTip(CString("服务器已启动"));
			return;
		}
	}
	// 创建失败
	delete m_pListenSocket;
	m_pListenSocket = NULL;
	JudgeButton();
	SetTip(CString("服务器无法启动"));	
}

void CEx1402Dlg::OnButtonStop() 
{
	// 停止服务器Socket
	delete m_pListenSocket;
	m_pListenSocket = NULL;
	JudgeButton();
	SetTip(CString("停止服务"));	
}

void CEx1402Dlg::OnButtonConnect() 
{
	// 获得服务器IP
	BYTE a1,a2,a3,a4;
	int nBlank = m_ctrlIP.GetAddress(a1,a2,a3,a4);
	if(nBlank < 4)
		return;
	CString strIP ;
	strIP.Format("%d.%d.%d.%d",a1,a2,a3,a4);
	
	// 建立连接
	if(ConnectSocket(strIP)){
		JudgeButton();
		SetTip(CString("连接成功"));
	}
	else{
		JudgeButton();
		SetTip(CString("连接失败"));
	}	
}

BOOL CEx1402Dlg::ConnectSocket(CString strIP){
	// 创建客户端Socket
	m_pChatSocket = new CChatSocket(this);
	if (!m_pChatSocket->Create()){
		delete m_pChatSocket;
		m_pChatSocket = NULL;
		AfxMessageBox("创建Socket失败");
		return FALSE;
	}

	while (!m_pChatSocket->Connect(strIP,m_nPort)){
		// 连接失败，询问用户是否继续尝试
		if (AfxMessageBox("您想重新尝试连接吗？",MB_YESNO) == IDNO){
			// 放弃尝试
			delete m_pChatSocket;
			m_pChatSocket = NULL;
			return FALSE;
		}
	}
	// 初始化Socket工具
	InitConnection();
	return TRUE;
}

void CEx1402Dlg::OnButtonClose() 
{
	if(m_pChatSocket)
		SendMsg(CString("ByeBye"),TRUE);
	CDialog::OnClose();	
}

void CEx1402Dlg::OnButtonSend() 
{
	// 获得用户输入
	CString str;
	m_editSend.GetWindowText(str);
	if(str.GetLength() == 0)
		return;
	// 调用SendMsg来发送消息
	SendMsg(str);
	// 清空输入框
	m_editSend.SetWindowText(CString(""));	
}

void CEx1402Dlg::SendMsg(CString& strText, BOOL bClose){
	// 显示信息
	DisplayMsg("[本地]"+strText);
	if (m_pArchiveOut != NULL){
		// 构造发送消息
		CMsg msg;
		msg.m_strText = strText;
		msg.m_bClose = bClose;
		TRY{
			// 发送消息
			msg.Serialize(*m_pArchiveOut);
			m_pArchiveOut->Flush();
		}
		CATCH(CFileException, e){
			// 如果发生异常则放弃本次发送
			// 通常是由于本次连接已经中断了
			// 因袭需要销毁Socket和相关的文档
			m_pArchiveOut->Abort();
			delete m_pArchiveOut;
			m_pArchiveOut = NULL;

			delete m_pChatSocket;
			m_pChatSocket = NULL;
			JudgeButton();
			CString strTemp;
			strTemp.Format("服务器断开连接了");
			SetTip(strTemp);
		}
		END_CATCH
	}
}

void CEx1402Dlg::ProcessRecv(){
	// 循环接收，知道接收完毕
	do{
		// 接收一次缓冲
		ReceiveMsg();
		if (m_pChatSocket == NULL)
			return;
	}while(!m_pArchiveIn->IsBufferEmpty());
}

void CEx1402Dlg::ReceiveMsg(){
	CMsg msg;
	TRY{
		// 接收消息
		msg.Serialize(*m_pArchiveIn);
		DisplayMsg("[远端]"+msg.m_strText);
	}
	CATCH(CFileException, e){
		// 如果发生异常，则是因为流发生中断
		// 终止此次接收
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
	}
	END_CATCH

	if (msg.m_bClose){
		// 如果是最后一条消息则关闭Socket
		// 首先关闭相关的文档
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
		delete m_pFile;
		m_pFile = NULL;
		// 最后关闭Socket
		delete m_pChatSocket;
		m_pChatSocket = NULL;
		// 更新按钮和提示
		JudgeButton();
		CString strTemp;
		strTemp.Format("对方已断开连接");
		SetTip(strTemp);
	}
}

void CEx1402Dlg::DisplayMsg(LPCTSTR lpszText){
	// 获得原来的消息
	CString str;
	m_editRecv.GetWindowText(str);
	// 追加新消息
	str = str+lpszText+"\r\n";
	m_editRecv.SetWindowText(str);
	// 滚动到最后一行可视状态
	int nLines = m_editRecv.GetLineCount();
	m_editRecv.LineScroll(nLines, 0);
}

void CEx1402Dlg::OnButtonClearRecv() 
{
	m_editRecv.SetWindowText(CString(""));	
}

void CEx1402Dlg::OnButtonClear() 
{
	m_editSend.SetWindowText(CString(""));	
}

BOOL CEx1402Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// 过滤按键消息
	if(pMsg->message == WM_KEYDOWN){
		int vKey = pMsg->wParam;
		// 过滤具体键值
		if(vKey == VK_RETURN){
			// 如果是回车键
			if(m_btnSend.IsWindowEnabled())
				// 发送本行输入
				OnButtonSend();
			return TRUE;
		}
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
