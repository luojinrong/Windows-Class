// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ex1402.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CMsg, CObject)

CMsg::CMsg()
{	
	Init();
}

CMsg::~CMsg()
{
}

void CMsg::Init()
{	
	m_bClose = FALSE;	
	m_strText = _T("");
}

void CMsg::Serialize(CArchive& ar)
{	
	if (ar.IsStoring())	
	{		
		ar << (WORD)m_bClose;		
		ar << m_strText;	
	}	
	else
	{		
		WORD wd;		
		ar >> wd;		
		m_bClose = (BOOL)wd;		
		ar >> m_strText;	
	}
}
