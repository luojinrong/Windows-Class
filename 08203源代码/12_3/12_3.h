// 12_3.h : main header file for the 12_3 application
//

#if !defined(AFX_12_3_H__EB1B5D6F_D2DB_4ABD_852E_13EA9E853E2D__INCLUDED_)
#define AFX_12_3_H__EB1B5D6F_D2DB_4ABD_852E_13EA9E853E2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy12_3App:
// See 12_3.cpp for the implementation of this class
//

class CMy12_3App : public CWinApp
{
public:
	CMy12_3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12_3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy12_3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12_3_H__EB1B5D6F_D2DB_4ABD_852E_13EA9E853E2D__INCLUDED_)
