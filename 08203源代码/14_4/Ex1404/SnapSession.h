// SnapSession.h: interface for the CSnapSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPSESSION_H__421D07FD_1EAF_4670_A469_D3FC70C9A110__INCLUDED_)
#define AFX_SNAPSESSION_H__421D07FD_1EAF_4670_A469_D3FC70C9A110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSnapSession : public CInternetSession  
{
public:
	// 创建Session
	CSnapSession(LPCTSTR szSessionName);	
	// 创建Session，并指定接收回调信息的窗口
	CSnapSession(LPCTSTR szSessionName, CWnd* pStatusWnd);
	// 析够函数
	virtual ~CSnapSession();
	// 初始化该Session
    void Init();
	// 设置回调窗口的显示信息
    void SetStatus(LPCTSTR fmt, ...);
	// 设置回调窗口
    void SetStatusWnd(CWnd* pWnd)     { m_pStatusWnd = pWnd; }
	// 获取错误信息
	CString GetErrorMessage();
	// 回调处理函数
    virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, 
		LPVOID lpvStatusInformation, 
		DWORD dwStatusInformationLength);
	
protected:
    CWnd* m_pStatusWnd;		// 回调窗口
	CString errorMessage;	// 错误信息
	
};

#endif // !defined(AFX_SNAPSESSION_H__421D07FD_1EAF_4670_A469_D3FC70C9A110__INCLUDED_)
