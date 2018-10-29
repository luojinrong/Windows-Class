// Ex1402Dlg.h : header file
//

#if !defined(AFX_EX1402DLG_H__D433758F_2C53_405E_92E3_9DC0D9EDA9F9__INCLUDED_)
#define AFX_EX1402DLG_H__D433758F_2C53_405E_92E3_9DC0D9EDA9F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEx1402Dlg dialog
class CListenSocket;
class CChatSocket;

class CEx1402Dlg : public CDialog
{
// Construction
public:
	CEx1402Dlg(CWnd* pParent = NULL);	// standard constructor
	CListenSocket * m_pListenSocket;	// ���ڷ�����������Socket
	CChatSocket* m_pChatSocket;			// ���ڽ�������ͨ�ŵ�Socket
	CSocketFile* m_pFile;				// ����Socketͨ��
	CArchive* m_pArchiveIn;				// ͬ��
	CArchive* m_pArchiveOut;			// ͬ��
	int			m_nPort;

	void ProcessAccept();				// ����ͻ���������
	void ProcessRecv();					// ������Ϣ����
	void InitConnection();				// ��ʼ������
	BOOL ConnectSocket(CString strIP);	// ���ӷ�����
	void SendMsg(CString& strText,BOOL bClose = FALSE);
										// ������Ϣ
	void ReceiveMsg();					// ������Ϣ
	void DisplayMsg(LPCTSTR lpszText);	// ��ʾ��Ϣ
	void JudgeButton();					// ���ݵ�ǰSocket״̬���ù��ܰ�ť״̬
	void SetTip(CString str);			// ��ʾ��ǰSocket״̬
	
// Dialog Data
	//{{AFX_DATA(CEx1402Dlg)
	enum { IDD = IDD_EX1402_DIALOG };
	CEdit	m_editSend;
	CEdit	m_editRecv;
	CEdit	m_editTip;
	CIPAddressCtrl	m_ctrlIP;
	CButton	m_btnStop;
	CButton	m_btnSend;
	CButton	m_btnListen;
	CButton	m_btnConnect;
	CButton	m_btnClose;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1402Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx1402Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonListen();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonClearRecv();
	afx_msg void OnButtonClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1402DLG_H__D433758F_2C53_405E_92E3_9DC0D9EDA9F9__INCLUDED_)
