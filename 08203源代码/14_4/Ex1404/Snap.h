// Snap.h: interface for the CSnap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAP_H__5CF8F570_BBF9_48DD_8BD1_DE38CE149F53__INCLUDED_)
#define AFX_SNAP_H__5CF8F570_BBF9_48DD_8BD1_DE38CE149F53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSnapSession;
class CSnap : public CObject  
{
public:
	CSnap();			// ���캯��
	virtual ~CSnap();	// ��������
	// ��ʼ��������Ϣ
    BOOL Initialise(LPCTSTR szSessionName = NULL, CWnd* pWnd = NULL);
	// �����ļ� 
    BOOL GetFile(LPCTSTR szURL, CString& strBuffer, 
		LPCTSTR szSessionName = NULL, CWnd* pWnd = NULL);
	// �ͷ�
	void Close();
public:
	CString GetRawHeaders();			// ��ȡHTTPͷ��Ϣ
	CString GetErrorMessage();			// ��ȡSession��״̬��Ϣ 
	DWORD	GetPageStatusCode();		// ��ȡ����ҳ��HTTP״̬��
	double  GetRate();					// ��ȡ��������
	
	void    SetUseProxy(bool use);			// �����Ƿ�ʹ��Proxy
	void    SetProxyPort(UINT port);		// ����Proxy�˿�
	void    SetProxyServer(LPCSTR server);	// ����Proxy��ַ
	void    SetProxyUser(LPCSTR user);		// ����Proxy�û�
	void    SetProxyPass(LPCSTR pass);		// ����Proxy����
	void    SetProxy(LPCSTR proxy, WORD port, LPCSTR user = "", LPCSTR pass = "", bool use = true);
	void    SetTimeOut(DWORD timeOut);		// ���ӳ�ʱʱ��
	
protected:
    CSnapSession* m_pSession;				// Session����
	DWORD   m_timeOut;						// ��ʱʱ��
	double  m_transferRate;					// ��������
	bool    m_useProxy;						// �Ƿ�ʹ��Proxy
	DWORD	m_infoStatusCode;				// HTTP����
	CString m_ErrorMessage;					// Session״̬��Ϣ
	UINT    m_Port;							// Proxy�˿�
	CString m_Proxy;						// Proxy��ַ
	CString m_ProxyUser;					// Proxy�û�
	CString m_ProxyPass;					// Proxy����
	CString	m_rawHeaders;					// HTTPͷ
	
};

#endif // !defined(AFX_SNAP_H__5CF8F570_BBF9_48DD_8BD1_DE38CE149F53__INCLUDED_)
