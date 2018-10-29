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
	// ����Session
	CSnapSession(LPCTSTR szSessionName);	
	// ����Session����ָ�����ջص���Ϣ�Ĵ���
	CSnapSession(LPCTSTR szSessionName, CWnd* pStatusWnd);
	// ��������
	virtual ~CSnapSession();
	// ��ʼ����Session
    void Init();
	// ���ûص����ڵ���ʾ��Ϣ
    void SetStatus(LPCTSTR fmt, ...);
	// ���ûص�����
    void SetStatusWnd(CWnd* pWnd)     { m_pStatusWnd = pWnd; }
	// ��ȡ������Ϣ
	CString GetErrorMessage();
	// �ص�������
    virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus, 
		LPVOID lpvStatusInformation, 
		DWORD dwStatusInformationLength);
	
protected:
    CWnd* m_pStatusWnd;		// �ص�����
	CString errorMessage;	// ������Ϣ
	
};

#endif // !defined(AFX_SNAPSESSION_H__421D07FD_1EAF_4670_A469_D3FC70C9A110__INCLUDED_)
