// 13_2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "13_2.h"
#include "13_2Dlg.h"
#include "math.h"
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
// CMy13_2Dlg dialog

CMy13_2Dlg::CMy13_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy13_2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy13_2Dlg)
	m_Order = _T("");
	m_Query = _T("");
	m_Value = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCatalog = NULL;
	m_pConnection = NULL;
	m_pRs = NULL;

}


void CMy13_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy13_2Dlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COMBO_UPDOWN, m_Updown);
	DDX_CBString(pDX, IDC_COMBO_ORDER, m_Order);
	DDX_CBString(pDX, IDC_COMBO_QUERY, m_Query);
	DDX_Text(pDX, IDC_EDIT1, m_Value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy13_2Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy13_2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy13_2Dlg message handlers

BOOL CMy13_2Dlg::OnInitDialog()
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
	CreateDBAndTable();			// �������ݿ�ͱ�

	if(!IsConnected())				// �����������ݿ�
		InitConnection();
	if(!IsOpen())					// �򿪽����
		OpenTable();
	InitList();						// ��ʼ�������ؼ�	
	UpdateList();					// �����б�
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy13_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy13_2Dlg::OnPaint() 
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
HCURSOR CMy13_2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CMy13_2Dlg::DumpComError(_com_error &e)
{
	CString ErrorStr;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format( "Error\n\t���� = %08lx\n\t�����ʾ = %s\n\t��Դ = %s\n\t���� = %s\n",
		e.Error(), e.ErrorMessage(), (LPCSTR)bstrSource, (LPCSTR)bstrDescription );
#ifdef _DEBUG
		AfxMessageBox( ErrorStr, MB_OK | MB_ICONERROR );
#endif	

}

void CMy13_2Dlg::TestComError(HRESULT hr)
{
	if(FAILED(hr))
		_com_issue_error(hr);					// ��ʾHRESULT������Ϣ

}

void CMy13_2Dlg::InitConnection()
{
	HRESULT hr = m_pConnection.CreateInstance( __uuidof( Connection ) );
	// �������Ӷ���ʵ��
	TestComError(hr);
	hr = m_pConnection->Open(
		_bstr_t(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=./MyDB.mdb;"),
		_bstr_t(L""),
		_bstr_t(L""),
		adModeUnknown); 					// ��������
	TestComError(hr);

}

BOOL CMy13_2Dlg::OpenTable()
{
	HRESULT hr = S_OK;
	if(m_pRs == NULL)
		hr = m_pRs.CreateInstance( __uuidof(Recordset));
	TestComError(hr);
    hr = m_pRs->Open("MyTable",
        _variant_t((IDispatch*)m_pConnection,true),
        adOpenKeyset,
		adLockOptimistic,
		adCmdTable); 						// �򿪱�
	if(m_pRs->adoEOF || m_pRs->BOF) 			// �����Ϊ�����ٽ����κβ���
		return TRUE;
	m_pRs->MoveFirst();						// �ƶ�����ͷ
	return TRUE;

}

BOOL CMy13_2Dlg::AddNew()
{
	if(m_pRs->AddNew() != S_OK)
		return FALSE;
	return TRUE;

}

BOOL CMy13_2Dlg::Update()
{
	BOOL bret;
	try
	{
		if(m_pRs->Update() != S_OK)
			bret = FALSE;
	}
	catch(_com_error &e)
	{
		DumpComError(e);
		bret = FALSE;
	}

	if(!bret)
		m_pRs->CancelUpdate();
	return bret;

}

void CMy13_2Dlg::Close()
{
	if(IsOpen())
		m_pRs->Close();	

}

BOOL CMy13_2Dlg::PutValue(LPCTSTR fieldName, _variant_t fieldValue)
{
	try
	{
		m_pRs->Fields->GetItem(fieldName)->PutValue(fieldValue); 
		return TRUE;
	}
	catch(_com_error &e)
	{
		DumpComError(e);
		return FALSE;	
	}

}

BOOL CMy13_2Dlg::PutValue(LPCTSTR fieldName, long fieldValue)
{
	return PutValue(fieldName, _variant_t(fieldValue));
}

BOOL CMy13_2Dlg::PutValue(LPCTSTR fieldName, COleDateTime fieldValue)
{
	_variant_t vt;
	vt.vt = VT_DATE;
	vt.date = fieldValue;
	return PutValue(fieldName, vt);

}

BOOL CMy13_2Dlg::PutValue(LPCTSTR fieldName, LPCTSTR fieldValue)
{
	return PutValue(fieldName, _variant_t(fieldValue));
}

void CMy13_2Dlg::CreateDBAndTable()
{
HRESULT hr;
try{
	hr = m_pCatalog.CreateInstance(__uuidof(ADOX::Catalog));	// ����Catalog����
	TestComError(hr);
	CFile db;		
	// �ж����ݿ��Ƿ��Ѿ�����		
	if(db.Open("./MyDB.mdb", CFile::modeRead | CFile::shareDenyWrite))
		db.Close();		// �ر��ļ�
	 else
	{	
	m_pCatalog->Create("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=./MyDB.mdb;");
											// ���ݿⲻ�����򴴽������ݿ�
	ADOX::_TablePtr m_pTable = NULL;			// �ֱ𴴽���		    
	hr = m_pTable.CreateInstance(__uuidof(ADOX::Table));			
	TestComError(hr);		
	m_pTable->PutName("MyTable");			// ���ñ���			
	// �����			
	m_pTable->Columns->Append("����",ADOX::adVarWChar,30);	//�ַ�������	
	m_pTable->Columns->Append("����",ADOX::adInteger,0);		// ��������	
	m_pTable->Columns->Append("��������",ADOX::adDate,0);		// ��������	
	m_pTable->Columns->Append("�Ա�",ADOX::adVarWChar,2);	// �ַ�������
	m_pTable->Columns->Append("ϵ��",ADOX::adVarWChar,30);	// �ַ�������	
	m_pTable->Columns->Append("רҵ",ADOX::adVarWChar,30);	// �ַ�������
	m_pCatalog->Tables->Append(_variant_t((IDispatch *)m_pTable)); // ��ӱ�
	InitConnection();							// ��ʼ��ADO����
	OpenTable();								// ��һ�ű�
	// �����¼�¼
	static const char* names[]={"��", "Ǯ", "��", "��", "��", "��", "֣", "��", "��", "��"};
	static const char* depts[] = {"����", "����", "����", "��ѧ", "����", "����", "����", "��е", "�����", "�Զ���"};
	for(int i=0; i<10; i++)
	{
		AddNew();
		PutValue("����", names[i]);
		PutValue("����",i+20);
		PutValue("��������", COleDateTime::GetCurrentTime());
		if(i % 2 == 0)
			PutValue("�Ա�", "��");
		else
			PutValue("�Ա�", "Ů");
			PutValue("ϵ��", depts[i]);
			PutValue("רҵ", depts[i]);
			Update();
		}
			Close();
	}
	}
	catch(_com_error &e)
	{
		DumpComError(e);
	}

}

BOOL CMy13_2Dlg::IsConnected()
{
	if(m_pConnection )
		return m_pConnection->GetState() != adStateClosed;
	return FALSE;

}

BOOL CMy13_2Dlg::IsOpen()
{
	if(m_pRs)
		return m_pRs->GetState() != adStateClosed;
	return FALSE;
}


BOOL CMy13_2Dlg::GetFieldValue(LPCTSTR lpFieldName, CString &strValue)
{
	CString str = _T("");
	_variant_t vtFld;
	try
	{	
		// ����ֶ�ֵ
		vtFld = m_pRs->Fields->GetItem(lpFieldName)->Value;
		// ����ֵ��������������Ӧ��ת��
		switch(vtFld.vt) 
		{
		case VT_R4:
			str.Format("%.3f", vtFld.fltVal);
			break;
		case VT_R8:
			str.Format("%.6f", vtFld.dblVal);
			break;
		case VT_BSTR:
			str = vtFld.bstrVal;
			break;
		case VT_I2:
		case VT_UI1:
			str.Format("%d", vtFld.iVal);
			break;
		case VT_INT:
			str.Format("%d", vtFld.intVal);
			break;
		case VT_I4:
			str.Format("%d", vtFld.lVal);
			break;
		case VT_UI4:
			str.Format("%d", vtFld.ulVal);
			break;
		case VT_DECIMAL:
			{
			double val = vtFld.decVal.Lo32;
			val *= (vtFld.decVal.sign == 128)? -1 : 1;
			val /= pow(10, vtFld.decVal.scale); 
			str.Format("%.6f", val);
			}
			break;
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				CString strDateFormat = _T("%Y-%m-%d %H:%M:%S");
				str = dt.Format(strDateFormat);
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			str.Empty();
			break;
		default:
			str.Empty();
			return FALSE;
		}
		strValue = str;
		return TRUE;
	}
	catch(_com_error &e)
	{
		DumpComError(e);
		return FALSE;
	}
}



CString CMy13_2Dlg::GetFieldValue(LPCTSTR lpFieldName)
{
	CString str;
	GetFieldValue(lpFieldName, str);
	return str;

}

void CMy13_2Dlg::InitList()
{
	// �����б�ı�ͷ�Ϳ��
	static const char* columns[] = {"����", "����", "��������", "�Ա�", "ϵ��", "רҵ"};
	static const int widths[] = {40, 40, 130, 40, 50, 50};
	for(int i=0; i<6; i++)
	{
		m_List.InsertColumn(i, columns[i]);
		m_List.SetColumnWidth(i, widths[i]);
	}
	// ��ʼ��ComboBox�ĳ�ѡֵ
	m_Order = "����";
	m_Query = "����";
	m_Updown.SetCurSel(0);
	UpdateData(FALSE);

}


void CMy13_2Dlg::UpdateList()
{
try{
	m_pRs->MoveFirst();				// �ƶ�����һ��λ��
	m_List.DeleteAllItems();			// ����б��

	int index = 0;
	while(!m_pRs->adoEOF) 			// ����
{
	static const char* columns[] = {"����", "����", "��������", "�Ա�", "ϵ��", "רҵ"};
	CString num;
	num.Format("%d", index);
	m_List.InsertItem(index, num); 		// ����һ��
	for(int i=0; i<6; i++)				// ���ø��еĸ����ֶ�
		m_List.SetItemText(index, i, GetFieldValue(columns[i]));
	m_pRs->MoveNext();				// �ƶ�����һ��λ��
	index++;
	}
}
	catch(_com_error e)
{
		DumpComError(e);
	}

}

BOOL CMy13_2Dlg::OpenCommand(CString sql)
{
	HRESULT hr = S_OK;
	if(m_pRs == NULL)
		hr = m_pRs.CreateInstance( __uuidof(Recordset));
	TestComError(hr);
	// ����SQL��ѯ�����ؽ����
    hr = m_pRs->Open((LPCTSTR)sql,
        _variant_t((IDispatch*)m_pConnection,true),
        adOpenStatic,
		adLockReadOnly,
		adCmdText);
	if(m_pRs->adoEOF || m_pRs->BOF) 	// �����Ϊ�����ٽ����κβ���
		return TRUE;
	m_pRs->MoveFirst();				// �ƶ�����ͷ
	return TRUE;

}

void CMy13_2Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
		try{
		CString query = "SELECT * FROM MyTable";		// ƴ��SQL�ַ���
		UpdateData();
		m_pRs->Close();				// �ر�ԭ�����		
		m_Value.TrimLeft();			// ���˲�ѯֵ
		m_Value.TrimRight();
		if(m_Value.GetLength() != 0)
{
			CString criteria; 			// ����в�ѯֵ�����WHERE�Ӿ�
			criteria = m_Query + " = " + m_Value + ""; 	// ֻ֧��"��"�Ƚ�
			query +=" WHERE " + criteria;
		}
		CString order = m_Order + " ";	// ���ORDER BY�Ӿ�

		if(m_Updown.GetCurSel() == 0) 	// �ж������ǽ���
			order += "ASC";
		else
			order += "DESC";
		query += " ORDER BY " + order;
		OpenCommand(query); 		// ִ�в�ѯ
		UpdateList();					// �����б�		
	}
	catch(_com_error e)
	{
		DumpComError(e);
	}

}

CMy13_2Dlg::~CMy13_2Dlg()
{
	m_pConnection->Close();
}
