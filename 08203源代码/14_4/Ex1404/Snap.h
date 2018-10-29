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
	CSnap();			// 构造函数
	virtual ~CSnap();	// 析够函数
	// 初始化环境信息
    BOOL Initialise(LPCTSTR szSessionName = NULL, CWnd* pWnd = NULL);
	// 下载文件 
    BOOL GetFile(LPCTSTR szURL, CString& strBuffer, 
		LPCTSTR szSessionName = NULL, CWnd* pWnd = NULL);
	// 释放
	void Close();
public:
	CString GetRawHeaders();			// 获取HTTP头信息
	CString GetErrorMessage();			// 获取Session的状态信息 
	DWORD	GetPageStatusCode();		// 获取返回页的HTTP状态码
	double  GetRate();					// 获取下载速率
	
	void    SetUseProxy(bool use);			// 设置是否使用Proxy
	void    SetProxyPort(UINT port);		// 设置Proxy端口
	void    SetProxyServer(LPCSTR server);	// 设置Proxy地址
	void    SetProxyUser(LPCSTR user);		// 设置Proxy用户
	void    SetProxyPass(LPCSTR pass);		// 设置Proxy密码
	void    SetProxy(LPCSTR proxy, WORD port, LPCSTR user = "", LPCSTR pass = "", bool use = true);
	void    SetTimeOut(DWORD timeOut);		// 连接超时时限
	
protected:
    CSnapSession* m_pSession;				// Session对象
	DWORD   m_timeOut;						// 超时时限
	double  m_transferRate;					// 传输速率
	bool    m_useProxy;						// 是否使用Proxy
	DWORD	m_infoStatusCode;				// HTTP代码
	CString m_ErrorMessage;					// Session状态信息
	UINT    m_Port;							// Proxy端口
	CString m_Proxy;						// Proxy地址
	CString m_ProxyUser;					// Proxy用户
	CString m_ProxyPass;					// Proxy密码
	CString	m_rawHeaders;					// HTTP头
	
};

#endif // !defined(AFX_SNAP_H__5CF8F570_BBF9_48DD_8BD1_DE38CE149F53__INCLUDED_)
