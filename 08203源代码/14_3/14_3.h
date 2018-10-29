// 14_3.h : main header file for the 14_3 application
//

#if !defined(AFX_14_3_H__6C9F3C93_A4C6_46F1_9783_96AF448B2325__INCLUDED_)
#define AFX_14_3_H__6C9F3C93_A4C6_46F1_9783_96AF448B2325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy14_3App:
// See 14_3.cpp for the implementation of this class
//

class CMy14_3App : public CWinApp
{
public:
	CMy14_3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy14_3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy14_3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_14_3_H__6C9F3C93_A4C6_46F1_9783_96AF448B2325__INCLUDED_)
