#if !defined(AFX_CHATSOCKET_H__F312C972_F078_44B5_9DA1_66D131B51F40__INCLUDED_)
#define AFX_CHATSOCKET_H__F312C972_F078_44B5_9DA1_66D131B51F40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CChatSocket command target

class CEx1402Dlg;
class CChatSocket : public CSocket
{
// Attributes
public:
	CEx1402Dlg * m_pChatDlg;
// Operations
public:
	CChatSocket(CEx1402Dlg* pChatDlg);
	virtual ~CChatSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSocket)
	public:
		virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSOCKET_H__F312C972_F078_44B5_9DA1_66D131B51F40__INCLUDED_)
