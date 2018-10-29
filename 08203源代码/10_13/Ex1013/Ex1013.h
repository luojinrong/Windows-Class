// Ex1013.h : main header file for the EX1013 application
//

#if !defined(AFX_EX1013_H__5D9A14F5_77AD_4EB7_B0D3_38ED6D0BB027__INCLUDED_)
#define AFX_EX1013_H__5D9A14F5_77AD_4EB7_B0D3_38ED6D0BB027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx1013App:
// See Ex1013.cpp for the implementation of this class
//

class CEx1013App : public CWinApp
{
public:
	CEx1013App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1013App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx1013App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1013_H__5D9A14F5_77AD_4EB7_B0D3_38ED6D0BB027__INCLUDED_)
