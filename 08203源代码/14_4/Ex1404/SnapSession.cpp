// SnapSession.cpp: implementation of the CSnapSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ex1404.h"
#include "SnapSession.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapSession::CSnapSession(LPCTSTR szSessiontName) 
                : CInternetSession(szSessiontName) 
{
    Init();
}

CSnapSession::CSnapSession(LPCTSTR szSessiontName, CWnd* pStatusWnd) 
                : CInternetSession(szSessiontName)
{
    Init();
    m_pStatusWnd = pStatusWnd;
}

CSnapSession::~CSnapSession()
{
}

void CSnapSession::Init() 
{
    m_pStatusWnd = NULL;
    try {
		// 设置为允许回调模式
        EnableStatusCallback(TRUE);
    }
    catch (...)
    {}
}

void CSnapSession::OnStatusCallback(
	DWORD dwContext,					// 应用程序环境值
	DWORD dwInternetStatus,				// 状态码
	LPVOID lpvStatusInformation,		// 状态信息
	DWORD dwStatusInformationLength)	// 状态信息长度
{
    // 该回调函数必须调用这一句 
    AFX_MANAGE_STATE( AfxGetAppModuleState( ) );

    CString str;
	// 解析状态信息
	switch (dwInternetStatus)
	{
	case INTERNET_STATUS_RESOLVING_NAME:
		str.Format("正在解析 %s", lpvStatusInformation);
		break;

	case INTERNET_STATUS_NAME_RESOLVED:
		str.Format("解析完毕 %s", lpvStatusInformation);
		break;

	case INTERNET_STATUS_HANDLE_CREATED:
		str.Format("句柄创建成功");// hInternet;
		break;

	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		//sockaddr* pSockAddr = (sockaddr*) lpvStatusInformation;
		str.Format("正在连接"); //, pSockAddr->sa_data);
		break;

	case INTERNET_STATUS_REQUEST_SENT:
		str.Format("请求已经发送");
		break;

	case INTERNET_STATUS_SENDING_REQUEST:
		str.Format("正在发送请求...");
		break;

	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		str.Format("连接服务器成功");
		break;

	case INTERNET_STATUS_RECEIVING_RESPONSE:
        return;
		str.Format("正在接收响应...");
		break;

	case INTERNET_STATUS_RESPONSE_RECEIVED:
		str.Format("响应接收完毕");
		break;

	case INTERNET_STATUS_CLOSING_CONNECTION:
		str.Format("关闭连接");
		break;

	case INTERNET_STATUS_CONNECTION_CLOSED:
		str.Format("服务器已经断开连接");
		break;

	case INTERNET_STATUS_HANDLE_CLOSING:
        return;
		str.Format("句柄关闭");
		break;

	case INTERNET_STATUS_REQUEST_COMPLETE:
		if (dwStatusInformationLength == sizeof(INTERNET_ASYNC_RESULT))
		{
			INTERNET_ASYNC_RESULT* pResult = (INTERNET_ASYNC_RESULT*) lpvStatusInformation;
			str.Format("请求结束, dwResult = %8.8X, dwError = %8.8X",
				        pResult->dwResult, pResult->dwError);
		}
		else
			str.Format("请求结束");
		break;

	case INTERNET_STATUS_CTL_RESPONSE_RECEIVED:
	case INTERNET_STATUS_REDIRECT:
	default:
		str.Format("未知状态: %d", dwInternetStatus);
		break;
	}
	// 设置状态信息
    SetStatus(str);
}

void CSnapSession::SetStatus(LPCTSTR fmt, ...){
    va_list args;
    TCHAR buffer[512];

    va_start(args, fmt);
    _vstprintf(buffer, fmt, args);
    va_end(args);
	// 记录状态信息
	errorMessage = (CString) buffer;
    if (m_pStatusWnd){
		// 如果存在回调窗口，则显示状态信息
        m_pStatusWnd->SetWindowText(buffer);
        m_pStatusWnd->RedrawWindow();
    }
}

CString CSnapSession::GetErrorMessage()
{
	return errorMessage;
}
