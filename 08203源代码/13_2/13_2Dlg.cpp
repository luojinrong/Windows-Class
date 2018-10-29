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
	CreateDBAndTable();			// 创建数据库和表

	if(!IsConnected())				// 重新连接数据库
		InitConnection();
	if(!IsOpen())					// 打开结果集
		OpenTable();
	InitList();						// 初始化各个控件	
	UpdateList();					// 更新列表
	
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
	ErrorStr.Format( "Error\n\t代码 = %08lx\n\t代码表示 = %s\n\t来源 = %s\n\t描述 = %s\n",
		e.Error(), e.ErrorMessage(), (LPCSTR)bstrSource, (LPCSTR)bstrDescription );
#ifdef _DEBUG
		AfxMessageBox( ErrorStr, MB_OK | MB_ICONERROR );
#endif	

}

void CMy13_2Dlg::TestComError(HRESULT hr)
{
	if(FAILED(hr))
		_com_issue_error(hr);					// 显示HRESULT错误消息

}

void CMy13_2Dlg::InitConnection()
{
	HRESULT hr = m_pConnection.CreateInstance( __uuidof( Connection ) );
	// 创建连接对象实例
	TestComError(hr);
	hr = m_pConnection->Open(
		_bstr_t(L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=./MyDB.mdb;"),
		_bstr_t(L""),
		_bstr_t(L""),
		adModeUnknown); 					// 建立连接
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
		adCmdTable); 						// 打开表
	if(m_pRs->adoEOF || m_pRs->BOF) 			// 如果表为空则不再进行任何操作
		return TRUE;
	m_pRs->MoveFirst();						// 移动到开头
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
	hr = m_pCatalog.CreateInstance(__uuidof(ADOX::Catalog));	// 创建Catalog对象
	TestComError(hr);
	CFile db;		
	// 判断数据库是否已经存在		
	if(db.Open("./MyDB.mdb", CFile::modeRead | CFile::shareDenyWrite))
		db.Close();		// 关闭文件
	 else
	{	
	m_pCatalog->Create("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=./MyDB.mdb;");
											// 数据库不存在则创建该数据库
	ADOX::_TablePtr m_pTable = NULL;			// 分别创建表		    
	hr = m_pTable.CreateInstance(__uuidof(ADOX::Table));			
	TestComError(hr);		
	m_pTable->PutName("MyTable");			// 设置表名			
	// 添加列			
	m_pTable->Columns->Append("姓名",ADOX::adVarWChar,30);	//字符串类型	
	m_pTable->Columns->Append("年龄",ADOX::adInteger,0);		// 整数类型	
	m_pTable->Columns->Append("出生年月",ADOX::adDate,0);		// 日期类型	
	m_pTable->Columns->Append("性别",ADOX::adVarWChar,2);	// 字符串类型
	m_pTable->Columns->Append("系别",ADOX::adVarWChar,30);	// 字符串类型	
	m_pTable->Columns->Append("专业",ADOX::adVarWChar,30);	// 字符串类型
	m_pCatalog->Tables->Append(_variant_t((IDispatch *)m_pTable)); // 添加表
	InitConnection();							// 初始化ADO连接
	OpenTable();								// 打开一张表
	// 插入新记录
	static const char* names[]={"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈"};
	static const char* depts[] = {"建筑", "电子", "物理", "数学", "美术", "体育", "化工", "机械", "计算机", "自动化"};
	for(int i=0; i<10; i++)
	{
		AddNew();
		PutValue("姓名", names[i]);
		PutValue("年龄",i+20);
		PutValue("出生年月", COleDateTime::GetCurrentTime());
		if(i % 2 == 0)
			PutValue("性别", "男");
		else
			PutValue("性别", "女");
			PutValue("系别", depts[i]);
			PutValue("专业", depts[i]);
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
		// 获得字段值
		vtFld = m_pRs->Fields->GetItem(lpFieldName)->Value;
		// 根据值的类型来进行相应的转化
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
	// 设置列表的表头和宽度
	static const char* columns[] = {"姓名", "年龄", "出生年月", "性别", "系别", "专业"};
	static const int widths[] = {40, 40, 130, 40, 50, 50};
	for(int i=0; i<6; i++)
	{
		m_List.InsertColumn(i, columns[i]);
		m_List.SetColumnWidth(i, widths[i]);
	}
	// 初始化ComboBox的初选值
	m_Order = "姓名";
	m_Query = "姓名";
	m_Updown.SetCurSel(0);
	UpdateData(FALSE);

}


void CMy13_2Dlg::UpdateList()
{
try{
	m_pRs->MoveFirst();				// 移动到第一个位置
	m_List.DeleteAllItems();			// 清空列表框

	int index = 0;
	while(!m_pRs->adoEOF) 			// 遍历
{
	static const char* columns[] = {"姓名", "年龄", "出生年月", "性别", "系别", "专业"};
	CString num;
	num.Format("%d", index);
	m_List.InsertItem(index, num); 		// 插入一行
	for(int i=0; i<6; i++)				// 设置该行的各个字段
		m_List.SetItemText(index, i, GetFieldValue(columns[i]));
	m_pRs->MoveNext();				// 移动到下一个位置
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
	// 根据SQL查询并返回结果集
    hr = m_pRs->Open((LPCTSTR)sql,
        _variant_t((IDispatch*)m_pConnection,true),
        adOpenStatic,
		adLockReadOnly,
		adCmdText);
	if(m_pRs->adoEOF || m_pRs->BOF) 	// 如果表为空则不再进行任何操作
		return TRUE;
	m_pRs->MoveFirst();				// 移动到开头
	return TRUE;

}

void CMy13_2Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
		try{
		CString query = "SELECT * FROM MyTable";		// 拼接SQL字符串
		UpdateData();
		m_pRs->Close();				// 关闭原结果集		
		m_Value.TrimLeft();			// 过滤查询值
		m_Value.TrimRight();
		if(m_Value.GetLength() != 0)
{
			CString criteria; 			// 如果有查询值则添加WHERE子句
			criteria = m_Query + " = " + m_Value + ""; 	// 只支持"＝"比较
			query +=" WHERE " + criteria;
		}
		CString order = m_Order + " ";	// 添加ORDER BY子句

		if(m_Updown.GetCurSel() == 0) 	// 判断升序还是降序
			order += "ASC";
		else
			order += "DESC";
		query += " ORDER BY " + order;
		OpenCommand(query); 		// 执行查询
		UpdateList();					// 更新列表		
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
