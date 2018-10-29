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
	// �ͷ�ǰһ��Session�������µ�Session
    Close();
	m_infoStatusCode=0;
    m_pSession = new CSnapSession(szSessionName, pWnd);
	
	// ���ó�ʱʱ��
	if (m_timeOut != 0)
		m_pSession->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT  ,m_timeOut);

	// ���ô���
	if (m_useProxy)
	{
		char buf[10];
		itoa(m_Port,buf,10);
		CString temp = m_Proxy+":"+(CString)buf;
		// ���ô����ַ�Ͷ˿�
		INTERNET_PROXY_INFO proxyinfo;
		proxyinfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
		proxyinfo.lpszProxy = temp;
		proxyinfo.lpszProxyBypass = NULL;
		m_pSession->SetOption(INTERNET_OPTION_PROXY, (LPVOID)&proxyinfo, sizeof(INTERNET_PROXY_INFO));
		// ���ô����û�
		LPCTSTR proxyUser = m_ProxyUser;
		m_pSession->SetOption(INTERNET_OPTION_PROXY_USERNAME, (LPVOID)proxyUser, strlen(proxyUser)+1);
		// ���ô�������
		LPCTSTR proxyPass = m_ProxyPass;
		m_pSession->SetOption(INTERNET_OPTION_PROXY_PASSWORD, (LPVOID)proxyPass, strlen(proxyPass)+1);
	}
	return (m_pSession != NULL);
}

void CSnap::Close()
{
    if (m_pSession)
	{
		// �ر�Session���ͷ�
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
	// ��ʼ��
	m_rawHeaders ="";
	m_infoStatusCode=0;
	strBuffer.Empty();
    if (!m_pSession && !Initialise(szAgentName, pWnd))
        return FALSE;
	// ���ûص�����
    if (pWnd)
        m_pSession->SetStatusWnd(pWnd);
    DWORD dwCount = 0;
    CHttpFile* pFile = NULL;
    try{
		// ʹ��CHTTPFile������
        pFile = (CHttpFile*) m_pSession->OpenURL(szURL, 1,INTERNET_FLAG_TRANSFER_BINARY);
	}
    catch (CInternetException* e)
	{
		// ��������쳣
		// ��ʾ������Ϣ
        TCHAR   szCause[255];
        e->GetErrorMessage(szCause, 255);
        m_pSession->SetStatus(szCause);
		// �ͷžֲ���Դ
        e->Delete();
        delete pFile;
        pFile = NULL;
        return FALSE;
    }
	// ��¼��ʼʱ��
    COleDateTime startTime = COleDateTime::GetCurrentTime();
    LPSTR pBuf = NULL;
    if (pFile){
		// ����ȡ
        pBuf = (LPSTR) ::GlobalAlloc(GMEM_FIXED, BUFFER_SIZE+1);
        if (!pBuf)
		{
			// ����ʧ��
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
					// ΪstrBuffer���仺����
                    LPTSTR ptr = strBuffer.GetBufferSetLength(dwCount + nRead + 1);
					// ׷��������
                    memcpy(ptr+dwCount, buffer, nRead);
					// ���³���
                    dwCount += nRead;
					// �ͷ�û���õ��Ŀռ�
                    strBuffer.ReleaseBuffer(dwCount+1);
					// ��¼����ʱ��
                    COleDateTimeSpan elapsed = COleDateTime::GetCurrentTime() - startTime;
					// ���㴫�����ʣ�����ʾ
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
			// ��ʾ������Ϣ
            TCHAR   szCause[255];
            e->GetErrorMessage(szCause, 255);
			m_ErrorMessage = szCause;
            m_pSession->SetStatus(szCause);
            // �ͷ���Դ
            e->Delete();
            delete pFile;
            ::GlobalFree(pBuf);	// mem leak fix by Niek Albers 
            return FALSE;
        }
		// ���û�����Ϣ
        pFile->QueryInfoStatusCode(m_infoStatusCode);       
		pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS,m_rawHeaders);
        pFile->Close();
		// �ͷ�
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
