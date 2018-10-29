// CalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex1012.h"
#include "CalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalDlg dialog


CCalDlg::CCalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalDlg)
	m_edit1 = 1;
	m_edit2 = 1;
	m_edit3 = _T("0");
	//}}AFX_DATA_INIT
}


void CCalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalDlg)
	DDX_Control(pDX, IDC_SCROLLBAR2, m_bar2);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_bar1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalDlg, CDialog)
	//{{AFX_MSG_MAP(CCalDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, OnButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, OnButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, OnButtonDiv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalDlg message handlers

BOOL CCalDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// ���÷�ΧΪ1~10����ʼλ��Ϊ1
	m_bar1.SetScrollRange(1, 10);
	m_bar1.SetScrollPos(1);
	m_bar2.SetScrollRange(1, 10);
	m_bar2.SetScrollPos(1);
	return TRUE;
}

void CCalDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
   // ��¼�������������Сλ�ú͵�ǰλ��
   int minpos;
   int maxpos;
   pScrollBar->GetScrollRange(&minpos, &maxpos); 
   int curpos = pScrollBar->GetScrollPos();

   // ȷ��������Ϣ����.
   switch (nSBCode)
   {
   case SB_LEFT:      // �����������
      curpos = minpos;
      break;

   case SB_RIGHT:      // �����������
      curpos = maxpos;
      break;

   case SB_ENDSCROLL:   // 
      break;

   case SB_LINELEFT:      // ���һ��
      if (curpos > minpos)
         curpos--;
      break;

   case SB_LINERIGHT:   // �ҹ�һ��
      if (curpos < maxpos)
         curpos++;
      break;

   case SB_PAGELEFT:    // ���һҳ
   {
      SCROLLINFO   info;
      pScrollBar->GetScrollInfo(&info, SIF_ALL);
   
      if (curpos > minpos)
      curpos = max(minpos, curpos - (int) info.nPage);
   }
      break;

   case SB_PAGERIGHT:      // ���һҳ
   {
      SCROLLINFO   info;
      pScrollBar->GetScrollInfo(&info, SIF_ALL);

      if (curpos < maxpos)
         curpos = min(maxpos, curpos + (int) info.nPage);
   }
      break;

   case SB_THUMBPOSITION: // �϶�
      curpos = nPos;      
      break;

   case SB_THUMBTRACK:   // �϶�
      curpos = nPos;     
      break;
   }

   // ���ù�������λ��
   pScrollBar->SetScrollPos(curpos);

	// ���ݹ��������������ı�������
   if (pScrollBar->GetDlgCtrlID() == IDC_SCROLLBAR1){
	   m_edit1 = curpos;
   }
   if (pScrollBar->GetDlgCtrlID() == IDC_SCROLLBAR2){
	   m_edit2 = curpos;
   }
   UpdateData(FALSE);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCalDlg::OnButtonAdd() 
{
	UpdateData(TRUE);
	m_edit3.Format("%d", m_edit1+m_edit2);
	UpdateData(FALSE);
}

void CCalDlg::OnButtonSub() 
{
	UpdateData(TRUE);
	m_edit3.Format("%d", m_edit1-m_edit2);
	UpdateData(FALSE);
}

void CCalDlg::OnButtonMul() 
{
	UpdateData(TRUE);
	m_edit3.Format("%d", m_edit1*m_edit2);
	UpdateData(FALSE);
}

void CCalDlg::OnButtonDiv() 
{
	UpdateData(TRUE);
	m_edit3.Format("%.3f", m_edit1*1.0/m_edit2);
	UpdateData(FALSE);
}
