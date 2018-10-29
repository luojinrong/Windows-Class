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
		// ����Ϊ����ص�ģʽ
        EnableStatusCallback(TRUE);
    }
    catch (...)
    {}
}

void CSnapSession::OnStatusCallback(
	DWORD dwContext,					// Ӧ�ó��򻷾�ֵ
	DWORD dwInternetStatus,				// ״̬��
	LPVOID lpvStatusInformation,		// ״̬��Ϣ
	DWORD dwStatusInformationLength)	// ״̬��Ϣ����
{
    // �ûص��������������һ�� 
    AFX_MANAGE_STATE( AfxGetAppModuleState( ) );

    CString str;
	// ����״̬��Ϣ
	switch (dwInternetStatus)
	{
	case INTERNET_STATUS_RESOLVING_NAME:
		str.Format("���ڽ��� %s", lpvStatusInformation);
		break;

	case INTERNET_STATUS_NAME_RESOLVED:
		str.Format("������� %s", lpvStatusInformation);
		break;

	case INTERNET_STATUS_HANDLE_CREATED:
		str.Format("��������ɹ�");// hInternet;
		break;

	case INTERNET_STATUS_CONNECTING_TO_SERVER:
		//sockaddr* pSockAddr = (sockaddr*) lpvStatusInformation;
		str.Format("��������"); //, pSockAddr->sa_data);
		break;

	case INTERNET_STATUS_REQUEST_SENT:
		str.Format("�����Ѿ�����");
		break;

	case INTERNET_STATUS_SENDING_REQUEST:
		str.Format("���ڷ�������...");
		break;

	case INTERNET_STATUS_CONNECTED_TO_SERVER:
		str.Format("���ӷ������ɹ�");
		break;

	case INTERNET_STATUS_RECEIVING_RESPONSE:
        return;
		str.Format("���ڽ�����Ӧ...");
		break;

	case INTERNET_STATUS_RESPONSE_RECEIVED:
		str.Format("��Ӧ�������");
		break;

	case INTERNET_STATUS_CLOSING_CONNECTION:
		str.Format("�ر�����");
		break;

	case INTERNET_STATUS_CONNECTION_CLOSED:
		str.Format("�������Ѿ��Ͽ�����");
		break;

	case INTERNET_STATUS_HANDLE_CLOSING:
        return;
		str.Format("����ر�");
		break;

	case INTERNET_STATUS_REQUEST_COMPLETE:
		if (dwStatusInformationLength == sizeof(INTERNET_ASYNC_RESULT))
		{
			INTERNET_ASYNC_RESULT* pResult = (INTERNET_ASYNC_RESULT*) lpvStatusInformation;
			str.Format("�������, dwResult = %8.8X, dwError = %8.8X",
				        pResult->dwResult, pResult->dwError);
		}
		else
			str.Format("�������");
		break;

	case INTERNET_STATUS_CTL_RESPONSE_RECEIVED:
	case INTERNET_STATUS_REDIRECT:
	default:
		str.Format("δ֪״̬: %d", dwInternetStatus);
		break;
	}
	// ����״̬��Ϣ
    SetStatus(str);
}

void CSnapSession::SetStatus(LPCTSTR fmt, ...){
    va_list args;
    TCHAR buffer[512];

    va_start(args, fmt);
    _vstprintf(buffer, fmt, args);
    va_end(args);
	// ��¼״̬��Ϣ
	errorMessage = (CString) buffer;
    if (m_pStatusWnd){
		// ������ڻص����ڣ�����ʾ״̬��Ϣ
        m_pStatusWnd->SetWindowText(buffer);
        m_pStatusWnd->RedrawWindow();
    }
}

CString CSnapSession::GetErrorMessage()
{
	return errorMessage;
}
