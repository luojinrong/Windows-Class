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
	m_pFtpConnection = NULL;  // 初始为无连接状态
	m_nLevel = 1;  // 扫描深度为1，也就是只扫描根目录

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
	// 显示等待鼠标
	CWaitCursor cursor;

	// 清空整棵树
	DeleteAllItems();

	// 如果连接不合法
	if (!pConnection)
	{

		// 去除TVS_LINESATROOT属性
		ModifyStyle(TVS_LINESATROOT, 0);
		// 插入一个显示错误信息的根结点
		TV_INSERTSTRUCT tvstruct;
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_FIRST;
		tvstruct.item.iImage = 0;
		tvstruct.item.iSelectedImage = 0;
		tvstruct.item.pszText = _T("没有建立FTP连接");
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		InsertItem(&tvstruct);
		m_pFtpConnection = NULL;
	}
	else
	{
		m_pFtpConnection = pConnection;
		CString cstr = _T("/");				// 从根目开始扫描
		TV_INSERTSTRUCT tvstruct; 		// 将根目录插入树的根结点
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = 1;
		tvstruct.item.iSelectedImage = 1;
		tvstruct.item.pszText = _T("/");
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		HTREEITEM hThisItem = InsertItem(&tvstruct);
		ExploreDir("/", hThisItem); 		// 开始扫描
		if (!ItemHasChildren(GetRootItem()))	// 若目录为空，去除TVS_LINESATROOT属性
		{
			ModifyStyle(TVS_LINESATROOT, 0);
			return;
		}
		ModifyStyle(0, TVS_LINESATROOT); 	// 否则设置TVS_LINESATROOT属性
	}
}


void CFTPTreeCtrl::ExploreDir(const CString& strDir, HTREEITEM hParent, int nLevel)
{
	if(nLevel >= m_nLevel) 					// 判断是否到达指定深度
		return;
	TV_INSERTSTRUCT tvstruct;
	CString strSearchDir;

	// 如果当前节点已经有子节点，将它们全部删除
    // 获得子节点
	HTREEITEM hIT = GetChildItem(hParent);
	HTREEITEM hTemp;
while (hIT != NULL) 						// 判断是否存在子节点
	{
        // 存在，则逐个删除
		hTemp = GetNextSiblingItem(hIT);
		DeleteItem(hIT);
		hIT = hTemp;
	}

	// 设置搜索字符串
	if (hParent != GetRootItem())
		strSearchDir = strDir + _T("/*");			// 搜索的是普通目录
	else
		strSearchDir = _T("/*");				// 搜索的是根目录
	CFtpFileFind ftpFind(m_pFtpConnection); 	// 构造CFtpFileFind对象
	BOOL bContinue = ftpFind.FindFile(strSearchDir); 	// 按照指定条件查找文件
	if (!bContinue)
{
		ftpFind.Close();						// 空目录，不再继续扫描
		return;
	}

	BOOL bDir = FALSE;
	HTREEITEM hThisItem;
	CString strFileName;
	while (bContinue) 				// 遍历所有文件，作为子节点插入当前节点之下
	{
		bContinue = ftpFind.FindNextFile();		// 开始查找
		strFileName = ftpFind.GetFileName();		// 获得文件名
		if (ftpFind.IsDirectory())
{
			// 找到目录
			bDir = TRUE;
			tvstruct.item.iImage = 1;
			tvstruct.item.iSelectedImage = 1;
		}
		else
{
			// 找到文件
			tvstruct.item.iImage = 2;
			tvstruct.item.iSelectedImage = 2;
		}
		// 插入当前节点之下最后一个位置，结点文字为目录名或者文件名
		tvstruct.hParent = hParent;			
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.pszText = (LPTSTR)(LPCTSTR)strFileName; 
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		hThisItem = InsertItem(&tvstruct);
	}
	ftpFind.Close();							// 结束本目录查找
	// 如果当前目录之下还有目录，则继续扫描
	// 任何时候只能有一个CFtpFileFind对象与一个Session关联
	if (bDir)
	{
		int nImage, nSelectedImage;
		hThisItem = GetChildItem(hParent); 		// 从第一个节点开始遍历
		while (hThisItem != NULL)
		{
			// 根据图片类型来判断文件类型
			GetItemImage(hThisItem, nImage, nSelectedImage);
			if (nImage == 1)
			{
				strFileName = GetItemText(hThisItem); 	// 获得目录名
				// 判断是否是这两个特殊目录
				if(strFileName == "." || strFileName == "..")
				{
					// 对于这两个特殊目录，为了防止循环递归，不予深入扫描
					// 继续扫描下一个兄弟节点
					hThisItem = GetNextSiblingItem(hThisItem);
					continue;
				}
				CString strNewDir = strDir+"/"+strFileName; 	// 设置搜索起始目录
				ExploreDir(strNewDir,hThisItem,nLevel+1); 	// 深入搜索
			}
			hThisItem = GetNextSiblingItem(hThisItem); 		// 继续扫描下一个节点
		}
	}
	return;
}

