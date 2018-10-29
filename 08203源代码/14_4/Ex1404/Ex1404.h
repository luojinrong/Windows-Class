// Ex1404.h : main header file for the EX1404 application
//

#if !defined(AFX_EX1404_H__CC13040C_6F96_4E74_8229_6305604EBC4F__INCLUDED_)
#define AFX_EX1404_H__CC13040C_6F96_4E74_8229_6305604EBC4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx1404App:
// See Ex1404.cpp for the implementation of this class
//

class CEx1404App : public CWinApp
{
public:
	CEx1404App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1404App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx1404App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1404_H__CC13040C_6F96_4E74_8229_6305604EBC4F__INCLUDED_)
