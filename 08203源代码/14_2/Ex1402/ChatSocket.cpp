// ChatSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Ex1402.h"
#include "ChatSocket.h"

#include "Ex1402Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatSocket

CChatSocket::CChatSocket(CEx1402Dlg* pChatDlg)
{
	m_pChatDlg = pChatDlg;
}

CChatSocket::~CChatSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatSocket, CSocket)
	//{{AFX_MSG_MAP(CChatSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatSocket member functions

void CChatSocket::OnReceive(int nErrorCode) {
	CSocket::OnReceive(nErrorCode);
	m_pChatDlg->ProcessRecv();
}