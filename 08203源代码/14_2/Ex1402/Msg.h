// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__2D55D82B_6034_4CC1_9FBA_ECC306FE3431__INCLUDED_)
#define AFX_MSG_H__2D55D82B_6034_4CC1_9FBA_ECC306FE3431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsg : public CObject  {
protected:	
	DECLARE_DYNCREATE(CMsg)
public:	
	 CString m_strText;	// ���ڴ��ݵ���Ϣ	
	 BOOL m_bClose;		// �Ƿ��ǽ�����Ϣ
public:	
	CMsg();				// ���캯��	
	void Init();		// ��ʼ��
public:	
	virtual ~CMsg();	// ��������	
	virtual void Serialize(CArchive& ar);	// ���л�����
};

#endif // !defined(AFX_MSG_H__2D55D82B_6034_4CC1_9FBA_ECC306FE3431__INCLUDED_)
