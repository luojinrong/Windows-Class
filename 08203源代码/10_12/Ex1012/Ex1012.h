// Ex1012.h : main header file for the EX1012 application
//

#if !defined(AFX_EX1012_H__E2C94FDD_86B4_4C78_B738_031B41DD4D17__INCLUDED_)
#define AFX_EX1012_H__E2C94FDD_86B4_4C78_B738_031B41DD4D17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx1012App:
// See Ex1012.cpp for the implementation of this class
//

class CEx1012App : public CWinApp
{
public:
	CEx1012App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1012App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEx1012App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1012_H__E2C94FDD_86B4_4C78_B738_031B41DD4D17__INCLUDED_)
