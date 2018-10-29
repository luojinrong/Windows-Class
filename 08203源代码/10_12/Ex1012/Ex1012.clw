; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx1012View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Ex1012.h"
LastPage=0

ClassCount=6
Class1=CEx1012App
Class2=CEx1012Doc
Class3=CEx1012View
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CCalDlg
Resource3=IDD_DIALOG_SHOW

[CLS:CEx1012App]
Type=0
HeaderFile=Ex1012.h
ImplementationFile=Ex1012.cpp
Filter=N

[CLS:CEx1012Doc]
Type=0
HeaderFile=Ex1012Doc.h
ImplementationFile=Ex1012Doc.cpp
Filter=N

[CLS:CEx1012View]
Type=0
HeaderFile=Ex1012View.h
ImplementationFile=Ex1012View.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_CAL_EXIT


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Ex1012.cpp
ImplementationFile=Ex1012.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_CAL_SHOW
Command18=ID_CAL_EXIT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG_SHOW]
Type=1
Class=CCalDlg
ControlCount=9
Control1=IDC_BUTTON_ADD,button,1342242816
Control2=IDC_BUTTON_SUB,button,1342242816
Control3=IDC_BUTTON_MUL,button,1342242816
Control4=IDC_BUTTON_DIV,button,1342242816
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_SCROLLBAR1,scrollbar,1342177280
Control8=IDC_SCROLLBAR2,scrollbar,1342177280
Control9=IDC_EDIT3,edit,1350631552

[CLS:CCalDlg]
Type=0
HeaderFile=CalDlg.h
ImplementationFile=CalDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_DIV
VirtualFilter=dWC

