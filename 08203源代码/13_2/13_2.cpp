// 13_2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "13_2.h"
#include "13_2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy13_2App

BEGIN_MESSAGE_MAP(CMy13_2App, CWinApp)
	//{{AFX_MSG_MAP(CMy13_2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy13_2App construction

CMy13_2App::CMy13_2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy13_2App object

CMy13_2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy13_2App initialization

BOOL CMy13_2App::InitInstance()
{
		// 初始化COM环境
	if(FAILED(::CoInitialize(NULL)))        
		return FALSE;

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMy13_2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CMy13_2App::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	// 释放COM环境
	::CoUninitialize();	
	
	return CWinApp::ExitInstance();
}
