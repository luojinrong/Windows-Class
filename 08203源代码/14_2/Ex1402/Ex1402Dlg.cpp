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
	m_nPort = 1234;					// �������˿�Ϊ1234
	m_ctrlIP.SetAddress(127,0,0,1);	// Ĭ��IPΪ���ػػ�
	JudgeButton();					// ���ð�ť״̬
	SetTip(CString("��ʼ״̬"));	// ���õ�ǰ״̬
	
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
		// ԭʼ�׶�
		m_btnConnect.EnableWindow(TRUE);	// ����������
		m_btnListen.EnableWindow(TRUE);		// ������������
		m_btnClose.EnableWindow(FALSE);		// ��ֹ�رտͻ�������
		m_btnStop.EnableWindow(FALSE);		// ��ֹֹͣ������
		m_btnSend.EnableWindow(FALSE);		// ��ֹ����
		m_editSend.EnableWindow(FALSE);		// ��ֹ��������
		return;
	}
	else if(m_pChatSocket != NULL){			
		// ��������״̬
		m_btnConnect.EnableWindow(FALSE);	// ��ֹ��������
		m_btnListen.EnableWindow(FALSE);	// ��ֹ����������
		m_btnClose.EnableWindow(TRUE);		// ����Ͽ��ͻ�������
		m_btnStop.EnableWindow(FALSE);		// ��ֹֹͣ������
		m_btnSend.EnableWindow(TRUE);		// ������
		m_editSend.EnableWindow(TRUE);		// ��������
		return;
	}
	else if(m_pListenSocket != NULL){
		// �������������״̬
		m_btnConnect.EnableWindow(FALSE);	// ��ֹ�ٽ�������
		m_btnListen.EnableWindow(FALSE);	// ��ֹ�ٽ���������
		m_btnClose.EnableWindow(FALSE);		// ��ֹ�رշ���������
		m_btnStop.EnableWindow(TRUE);		// ����ֹͣ������
		m_btnSend.EnableWindow(FALSE);		// ��ֹ����
		m_editSend.EnableWindow(FALSE);		// ��ֹ����
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
	// �����µ�ͨ��Socket
	m_pChatSocket = new CChatSocket(this);

	if (m_pListenSocket->Accept(*m_pChatSocket)){
		// ���������ճɹ�
		// ��ʼ������
		InitConnection();
		// �رռ���
		m_pListenSocket->Close();
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		// ���ð�ť����ʾ��Ϣ
		JudgeButton();
		SetTip(CString("�пͻ�����"));
	}
	else{
		// ����ʧ��
		// ���ٷ�����Socket��ͨ��Socket
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		delete m_pChatSocket;
		m_pChatSocket = NULL;
		// ���°�ť����ʾ��Ϣ
		JudgeButton();
		SetTip(CString("����ʧ��"));
	}
}

void CEx1402Dlg::OnButtonListen() 
{
	// ����������Socket��ָ���˿ڼ���
	m_pListenSocket = new CListenSocket(this);
	if (m_pListenSocket->Create(m_nPort)){
		// �����ɹ�
		if (m_pListenSocket->Listen()){
			// ���ڼ���...
			JudgeButton();
			SetTip(CString("������������"));
			return;
		}
	}
	// ����ʧ��
	delete m_pListenSocket;
	m_pListenSocket = NULL;
	JudgeButton();
	SetTip(CString("�������޷�����"));	
}

void CEx1402Dlg::OnButtonStop() 
{
	// ֹͣ������Socket
	delete m_pListenSocket;
	m_pListenSocket = NULL;
	JudgeButton();
	SetTip(CString("ֹͣ����"));	
}

void CEx1402Dlg::OnButtonConnect() 
{
	// ��÷�����IP
	BYTE a1,a2,a3,a4;
	int nBlank = m_ctrlIP.GetAddress(a1,a2,a3,a4);
	if(nBlank < 4)
		return;
	CString strIP ;
	strIP.Format("%d.%d.%d.%d",a1,a2,a3,a4);
	
	// ��������
	if(ConnectSocket(strIP)){
		JudgeButton();
		SetTip(CString("���ӳɹ�"));
	}
	else{
		JudgeButton();
		SetTip(CString("����ʧ��"));
	}	
}

BOOL CEx1402Dlg::ConnectSocket(CString strIP){
	// �����ͻ���Socket
	m_pChatSocket = new CChatSocket(this);
	if (!m_pChatSocket->Create()){
		delete m_pChatSocket;
		m_pChatSocket = NULL;
		AfxMessageBox("����Socketʧ��");
		return FALSE;
	}

	while (!m_pChatSocket->Connect(strIP,m_nPort)){
		// ����ʧ�ܣ�ѯ���û��Ƿ��������
		if (AfxMessageBox("�������³���������",MB_YESNO) == IDNO){
			// ��������
			delete m_pChatSocket;
			m_pChatSocket = NULL;
			return FALSE;
		}
	}
	// ��ʼ��Socket����
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
	// ����û�����
	CString str;
	m_editSend.GetWindowText(str);
	if(str.GetLength() == 0)
		return;
	// ����SendMsg��������Ϣ
	SendMsg(str);
	// ��������
	m_editSend.SetWindowText(CString(""));	
}

void CEx1402Dlg::SendMsg(CString& strText, BOOL bClose){
	// ��ʾ��Ϣ
	DisplayMsg("[����]"+strText);
	if (m_pArchiveOut != NULL){
		// ���췢����Ϣ
		CMsg msg;
		msg.m_strText = strText;
		msg.m_bClose = bClose;
		TRY{
			// ������Ϣ
			msg.Serialize(*m_pArchiveOut);
			m_pArchiveOut->Flush();
		}
		CATCH(CFileException, e){
			// ��������쳣��������η���
			// ͨ�������ڱ��������Ѿ��ж���
			// ��Ϯ��Ҫ����Socket����ص��ĵ�
			m_pArchiveOut->Abort();
			delete m_pArchiveOut;
			m_pArchiveOut = NULL;

			delete m_pChatSocket;
			m_pChatSocket = NULL;
			JudgeButton();
			CString strTemp;
			strTemp.Format("�������Ͽ�������");
			SetTip(strTemp);
		}
		END_CATCH
	}
}

void CEx1402Dlg::ProcessRecv(){
	// ѭ�����գ�֪���������
	do{
		// ����һ�λ���
		ReceiveMsg();
		if (m_pChatSocket == NULL)
			return;
	}while(!m_pArchiveIn->IsBufferEmpty());
}

void CEx1402Dlg::ReceiveMsg(){
	CMsg msg;
	TRY{
		// ������Ϣ
		msg.Serialize(*m_pArchiveIn);
		DisplayMsg("[Զ��]"+msg.m_strText);
	}
	CATCH(CFileException, e){
		// ��������쳣��������Ϊ�������ж�
		// ��ֹ�˴ν���
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
	}
	END_CATCH

	if (msg.m_bClose){
		// ��������һ����Ϣ��ر�Socket
		// ���ȹر���ص��ĵ�
		delete m_pArchiveIn;
		m_pArchiveIn = NULL;
		delete m_pArchiveOut;
		m_pArchiveOut = NULL;
		delete m_pFile;
		m_pFile = NULL;
		// ���ر�Socket
		delete m_pChatSocket;
		m_pChatSocket = NULL;
		// ���°�ť����ʾ
		JudgeButton();
		CString strTemp;
		strTemp.Format("�Է��ѶϿ�����");
		SetTip(strTemp);
	}
}

void CEx1402Dlg::DisplayMsg(LPCTSTR lpszText){
	// ���ԭ������Ϣ
	CString str;
	m_editRecv.GetWindowText(str);
	// ׷������Ϣ
	str = str+lpszText+"\r\n";
	m_editRecv.SetWindowText(str);
	// ���������һ�п���״̬
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
	// ���˰�����Ϣ
	if(pMsg->message == WM_KEYDOWN){
		int vKey = pMsg->wParam;
		// ���˾����ֵ
		if(vKey == VK_RETURN){
			// ����ǻس���
			if(m_btnSend.IsWindowEnabled())
				// ���ͱ�������
				OnButtonSend();
			return TRUE;
		}
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
