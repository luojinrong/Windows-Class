// Ex1402.h : main header file for the EX1402 application
//

#if !defined(AFX_EX1402_H__AB755560_A6EA_4DB5_A703_76E53A5F140C__INCLUDED_)
#define AFX_EX1402_H__AB755560_A6EA_4DB5_A703_76E53A5F140C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx1402App:
// See Ex1402.cpp for the implementation of this class
//

class CEx1402App : public CWinApp
{
public:
	CEx1402App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1402App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx1402App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1402_H__AB755560_A6EA_4DB5_A703_76E53A5F140C__INCLUDED_)
