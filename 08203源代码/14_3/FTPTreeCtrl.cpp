// FTPTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "14_3.h"
#include "FTPTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFTPTreeCtrl

CFTPTreeCtrl::CFTPTreeCtrl()
{
	m_pFtpConnection = NULL;  // ��ʼΪ������״̬
	m_nLevel = 1;  // ɨ�����Ϊ1��Ҳ����ֻɨ���Ŀ¼

}

CFTPTreeCtrl::~CFTPTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CFTPTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CFTPTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTPTreeCtrl message handlers

void CFTPTreeCtrl::PopulateTree(CFtpConnection* pConnection, const CString& strDir)
{
	// ��ʾ�ȴ����
	CWaitCursor cursor;

	// ���������
	DeleteAllItems();

	// ������Ӳ��Ϸ�
	if (!pConnection)
	{

		// ȥ��TVS_LINESATROOT����
		ModifyStyle(TVS_LINESATROOT, 0);
		// ����һ����ʾ������Ϣ�ĸ����
		TV_INSERTSTRUCT tvstruct;
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_FIRST;
		tvstruct.item.iImage = 0;
		tvstruct.item.iSelectedImage = 0;
		tvstruct.item.pszText = _T("û�н���FTP����");
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		InsertItem(&tvstruct);
		m_pFtpConnection = NULL;
	}
	else
	{
		m_pFtpConnection = pConnection;
		CString cstr = _T("/");				// �Ӹ�Ŀ��ʼɨ��
		TV_INSERTSTRUCT tvstruct; 		// ����Ŀ¼�������ĸ����
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = 1;
		tvstruct.item.iSelectedImage = 1;
		tvstruct.item.pszText = _T("/");
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		HTREEITEM hThisItem = InsertItem(&tvstruct);
		ExploreDir("/", hThisItem); 		// ��ʼɨ��
		if (!ItemHasChildren(GetRootItem()))	// ��Ŀ¼Ϊ�գ�ȥ��TVS_LINESATROOT����
		{
			ModifyStyle(TVS_LINESATROOT, 0);
			return;
		}
		ModifyStyle(0, TVS_LINESATROOT); 	// ��������TVS_LINESATROOT����
	}
}


void CFTPTreeCtrl::ExploreDir(const CString& strDir, HTREEITEM hParent, int nLevel)
{
	if(nLevel >= m_nLevel) 					// �ж��Ƿ񵽴�ָ�����
		return;
	TV_INSERTSTRUCT tvstruct;
	CString strSearchDir;

	// �����ǰ�ڵ��Ѿ����ӽڵ㣬������ȫ��ɾ��
    // ����ӽڵ�
	HTREEITEM hIT = GetChildItem(hParent);
	HTREEITEM hTemp;
while (hIT != NULL) 						// �ж��Ƿ�����ӽڵ�
	{
        // ���ڣ������ɾ��
		hTemp = GetNextSiblingItem(hIT);
		DeleteItem(hIT);
		hIT = hTemp;
	}

	// ���������ַ���
	if (hParent != GetRootItem())
		strSearchDir = strDir + _T("/*");			// ����������ͨĿ¼
	else
		strSearchDir = _T("/*");				// �������Ǹ�Ŀ¼
	CFtpFileFind ftpFind(m_pFtpConnection); 	// ����CFtpFileFind����
	BOOL bContinue = ftpFind.FindFile(strSearchDir); 	// ����ָ�����������ļ�
	if (!bContinue)
{
		ftpFind.Close();						// ��Ŀ¼�����ټ���ɨ��
		return;
	}

	BOOL bDir = FALSE;
	HTREEITEM hThisItem;
	CString strFileName;
	while (bContinue) 				// ���������ļ�����Ϊ�ӽڵ���뵱ǰ�ڵ�֮��
	{
		bContinue = ftpFind.FindNextFile();		// ��ʼ����
		strFileName = ftpFind.GetFileName();		// ����ļ���
		if (ftpFind.IsDirectory())
{
			// �ҵ�Ŀ¼
			bDir = TRUE;
			tvstruct.item.iImage = 1;
			tvstruct.item.iSelectedImage = 1;
		}
		else
{
			// �ҵ��ļ�
			tvstruct.item.iImage = 2;
			tvstruct.item.iSelectedImage = 2;
		}
		// ���뵱ǰ�ڵ�֮�����һ��λ�ã��������ΪĿ¼�������ļ���
		tvstruct.hParent = hParent;			
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.pszText = (LPTSTR)(LPCTSTR)strFileName; 
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		hThisItem = InsertItem(&tvstruct);
	}
	ftpFind.Close();							// ������Ŀ¼����
	// �����ǰĿ¼֮�»���Ŀ¼�������ɨ��
	// �κ�ʱ��ֻ����һ��CFtpFileFind������һ��Session����
	if (bDir)
	{
		int nImage, nSelectedImage;
		hThisItem = GetChildItem(hParent); 		// �ӵ�һ���ڵ㿪ʼ����
		while (hThisItem != NULL)
		{
			// ����ͼƬ�������ж��ļ�����
			GetItemImage(hThisItem, nImage, nSelectedImage);
			if (nImage == 1)
			{
				strFileName = GetItemText(hThisItem); 	// ���Ŀ¼��
				// �ж��Ƿ�������������Ŀ¼
				if(strFileName == "." || strFileName == "..")
				{
					// ��������������Ŀ¼��Ϊ�˷�ֹѭ���ݹ飬��������ɨ��
					// ����ɨ����һ���ֵܽڵ�
					hThisItem = GetNextSiblingItem(hThisItem);
					continue;
				}
				CString strNewDir = strDir+"/"+strFileName; 	// ����������ʼĿ¼
				ExploreDir(strNewDir,hThisItem,nLevel+1); 	// ��������
			}
			hThisItem = GetNextSiblingItem(hThisItem); 		// ����ɨ����һ���ڵ�
		}
	}
	return;
}

