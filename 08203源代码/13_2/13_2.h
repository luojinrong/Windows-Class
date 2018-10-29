// 13_2.h : main header file for the 13_2 application
//

#if !defined(AFX_13_2_H__36C299F6_EEE6_4CD1_8202_7A30A4B4C26E__INCLUDED_)
#define AFX_13_2_H__36C299F6_EEE6_4CD1_8202_7A30A4B4C26E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy13_2App:
// See 13_2.cpp for the implementation of this class
//

class CMy13_2App : public CWinApp
{
public:
	CMy13_2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy13_2App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy13_2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_13_2_H__36C299F6_EEE6_4CD1_8202_7A30A4B4C26E__INCLUDED_)
