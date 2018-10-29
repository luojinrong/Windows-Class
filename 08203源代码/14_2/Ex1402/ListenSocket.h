#if !defined(AFX_LISTENSOCKET_H__9A866899_5725_4225_8617_91CE4772D829__INCLUDED_)
#define AFX_LISTENSOCKET_H__9A866899_5725_4225_8617_91CE4772D829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target
class CEx1402Dlg;
class CListenSocket : public CSocket
{
// Attributes
public:
	CEx1402Dlg * m_pChatDlg;

// Operations
public:
	CListenSocket(CEx1402Dlg * pChatDlg);
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__9A866899_5725_4225_8617_91CE4772D829__INCLUDED_)
