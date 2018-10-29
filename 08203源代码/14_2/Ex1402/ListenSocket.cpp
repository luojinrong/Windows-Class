// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Ex1402.h"
#include "ListenSocket.h"

#include "Ex1402Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CEx1402Dlg * pChatDlg)
{
	m_pChatDlg = pChatDlg;
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode) 
{
	CSocket::OnAccept(nErrorCode);
	m_pChatDlg->ProcessAccept();
}
