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
	// ��ʼ������Ϊ��
	m_pFtpConnection = NULL;
	// ����һ��Session���󣬸ö���ֱ���ó����˳����Զ�����
	CString str("ScanFTP By Jackflit");
	m_pInetSession = new CInternetSession(str, 1, PRE_CONFIG_INTERNET_ACCESS);
	if (!m_pInetSession)
{
		AfxMessageBox("����Sessionʧ��", MB_OK);
		OnCancel();
	}
	// �������Ϳؼ�ʹ�õ�ͼƬ�б�
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
	// �������Ϳؼ���ͼƬ�б�
	m_FtpTreeCtrl.SetImageList(m_pImageList, TVSIL_NORMAL);
	m_FtpTreeCtrl.PopulateTree();			// ��ʼ�����Ϳؼ�
	// ��������Edit�ؼ���Ĭ��ֵ
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
	UpdateData();							// �������ѡ������
	if (m_pFtpConnection != NULL) 			// �ر�ǰһ������
		m_pFtpConnection->Close();
	delete m_pFtpConnection;
	m_pFtpConnection = NULL;
	try{
		// ��������
		m_pFtpConnection = m_pInetSession->GetFtpConnection(
				m_strAddress,				// ��������ַ
				m_strUser,				// �û���
				m_strPass,				// ����
				m_uPort);				// �˿�
	}
	catch (CInternetException* pEx)
	{
		// ����ʧ�ܣ���ʾʧ��ԭ��
		TCHAR szErr[1024];
		if (pEx->GetErrorMessage(szErr, 1024))
			AfxMessageBox(szErr, MB_OK);
		else
			AfxMessageBox("����ʧ��", MB_OK);
		pEx->Delete();
		m_pFtpConnection = NULL;
	}
	if (m_pFtpConnection != NULL)
	{
		m_FtpTreeCtrl.m_nLevel = m_uLevel; 	// ���ӳɹ�������ɨ����
		m_FtpTreeCtrl.PopulateTree(m_pFtpConnection,"/"); 		// ��ʼɨ��
	}
	else
		m_FtpTreeCtrl.PopulateTree();			// ����ʧ�ܣ���ʾ������Ϣ
	
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

