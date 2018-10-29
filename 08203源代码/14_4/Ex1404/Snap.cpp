// Snap.cpp: implementation of the CSnap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ex1404.h"
#include "Snap.h"

#include "SnapSession.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BUFFER_SIZE 4095

/////////////////////////////////////////////////////////////////////////////
// CWebGrab

CSnap::CSnap()
{
	m_pSession = NULL;
	m_timeOut = 0;
	m_useProxy = false;
	m_infoStatusCode=0;
}

CSnap::~CSnap()
{
    Close();
}

BOOL CSnap::Initialise(LPCTSTR szSessionName /*=NULL*/, CWnd* pWnd /*=NULL*/)
{
	// 释放前一次Session，创建新的Session
    Close();
	m_infoStatusCode=0;
    m_pSession = new CSnapSession(szSessionName, pWnd);
	
	// 设置超时时间
	if (m_timeOut != 0)
		m_pSession->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT  ,m_timeOut);

	// 设置代理
	if (m_useProxy)
	{
		char buf[10];
		itoa(m_Port,buf,10);
		CString temp = m_Proxy+":"+(CString)buf;
		// 设置代理地址和端口
		INTERNET_PROXY_INFO proxyinfo;
		proxyinfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
		proxyinfo.lpszProxy = temp;
		proxyinfo.lpszProxyBypass = NULL;
		m_pSession->SetOption(INTERNET_OPTION_PROXY, (LPVOID)&proxyinfo, sizeof(INTERNET_PROXY_INFO));
		// 设置代理用户
		LPCTSTR proxyUser = m_ProxyUser;
		m_pSession->SetOption(INTERNET_OPTION_PROXY_USERNAME, (LPVOID)proxyUser, strlen(proxyUser)+1);
		// 设置代理密码
		LPCTSTR proxyPass = m_ProxyPass;
		m_pSession->SetOption(INTERNET_OPTION_PROXY_PASSWORD, (LPVOID)proxyPass, strlen(proxyPass)+1);
	}
	return (m_pSession != NULL);
}

void CSnap::Close()
{
    if (m_pSession)
	{
		// 关闭Session并释放
        m_pSession->Close();
        delete m_pSession;
    }
    m_pSession = NULL;
}

CString CSnap::GetErrorMessage()
{
	return m_pSession->GetErrorMessage();
}

void CSnap::SetTimeOut(DWORD timeOut)
{
	m_timeOut = timeOut;
}

double CSnap::GetRate()
{
	return m_transferRate;
}

void CSnap::SetProxyServer(LPCSTR server)
{
	m_Proxy = server;
}

void CSnap::SetProxyPort(UINT port)
{
	m_Port = port;
}

void CSnap::SetUseProxy(bool use)
{
	m_useProxy = use;
}

void    CSnap::SetProxyUser(LPCSTR user)
{
	m_ProxyUser = user;
}

void    CSnap::SetProxyPass(LPCSTR pass)
{
	m_ProxyPass = pass;
}


void CSnap::SetProxy(LPCSTR proxy, WORD port, LPCSTR user, LPCSTR pass, bool useProxy )
{
	SetProxyServer(proxy);
	SetProxyPort(port);
	SetProxyUser(user);
	SetProxyPass(pass);
	SetUseProxy(useProxy);
}

BOOL CSnap::GetFile(LPCTSTR szURL, CString& strBuffer, LPCTSTR szAgentName /*=NULL*/, CWnd* pWnd /*=NULL*/)
                       
{
	// 初始化
	m_rawHeaders ="";
	m_infoStatusCode=0;
	strBuffer.Empty();
    if (!m_pSession && !Initialise(szAgentName, pWnd))
        return FALSE;
	// 设置回调窗口
    if (pWnd)
        m_pSession->SetStatusWnd(pWnd);
    DWORD dwCount = 0;
    CHttpFile* pFile = NULL;
    try{
		// 使用CHTTPFile来下载
        pFile = (CHttpFile*) m_pSession->OpenURL(szURL, 1,INTERNET_FLAG_TRANSFER_BINARY);
	}
    catch (CInternetException* e)
	{
		// 如果发生异常
		// 显示错误信息
        TCHAR   szCause[255];
        e->GetErrorMessage(szCause, 255);
        m_pSession->SetStatus(szCause);
		// 释放局部资源
        e->Delete();
        delete pFile;
        pFile = NULL;
        return FALSE;
    }
	// 记录开始时刻
    COleDateTime startTime = COleDateTime::GetCurrentTime();
    LPSTR pBuf = NULL;
    if (pFile){
		// 逐块读取
        pBuf = (LPSTR) ::GlobalAlloc(GMEM_FIXED, BUFFER_SIZE+1);
        if (!pBuf)
		{
			// 分配失败
            pFile->Close();
            delete pFile;
            return FALSE;
        }
        BYTE buffer[BUFFER_SIZE+1];
        try {
            UINT nRead = 0;
            dwCount = 0;
            do{
                nRead = pFile->Read(buffer, BUFFER_SIZE);
                if (nRead > 0)
				{
                    buffer[nRead] = 0;
					// 为strBuffer分配缓冲区
                    LPTSTR ptr = strBuffer.GetBufferSetLength(dwCount + nRead + 1);
					// 追加新内容
                    memcpy(ptr+dwCount, buffer, nRead);
					// 更新长度
                    dwCount += nRead;
					// 释放没有用到的空间
                    strBuffer.ReleaseBuffer(dwCount+1);
					// 记录结束时刻
                    COleDateTimeSpan elapsed = COleDateTime::GetCurrentTime() - startTime;
					// 计算传输速率，并显示
                    double dSecs = elapsed.GetTotalSeconds();
                    if (dSecs > 0.0)
					{
                        m_transferRate = (double)dwCount / 1024.0 / dSecs;
						m_pSession->SetStatus("Read %d bytes (%0.1f Kb/s)",dwCount, m_transferRate ); 
					}
					else
					{
                        m_pSession->SetStatus("Read %d bytes", dwCount);
						m_transferRate = dwCount;
					}
                }
            }while (nRead > 0);
        }
        catch (CFileException *e)
		{
			// 显示错误信息
            TCHAR   szCause[255];
            e->GetErrorMessage(szCause, 255);
			m_ErrorMessage = szCause;
            m_pSession->SetStatus(szCause);
            // 释放资源
            e->Delete();
            delete pFile;
            ::GlobalFree(pBuf);	// mem leak fix by Niek Albers 
            return FALSE;
        }
		// 设置基本信息
        pFile->QueryInfoStatusCode(m_infoStatusCode);       
		pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS,m_rawHeaders);
        pFile->Close();
		// 释放
		GlobalFree(pBuf);	
        delete pFile;
    }
    return TRUE;
}

DWORD CSnap::GetPageStatusCode()
{
	return m_infoStatusCode;
}

CString CSnap::GetRawHeaders()
{
	return m_rawHeaders;
}
