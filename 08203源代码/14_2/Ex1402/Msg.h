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
	 CString m_strText;	// 用于传递的消息	
	 BOOL m_bClose;		// 是否是结束消息
public:	
	CMsg();				// 构造函数	
	void Init();		// 初始化
public:	
	virtual ~CMsg();	// 析够函数	
	virtual void Serialize(CArchive& ar);	// 序列化传输
};

#endif // !defined(AFX_MSG_H__2D55D82B_6034_4CC1_9FBA_ECC306FE3431__INCLUDED_)
