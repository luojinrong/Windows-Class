; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMy14_3Dlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "14_3.h"

ClassCount=4
Class1=CMy14_3App
Class2=CMy14_3Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CFTPTreeCtrl
Resource3=IDD_MY14_3_DIALOG

[CLS:CMy14_3App]
Type=0
HeaderFile=14_3.h
ImplementationFile=14_3.cpp
Filter=N

[CLS:CMy14_3Dlg]
Type=0
HeaderFile=14_3Dlg.h
ImplementationFile=14_3Dlg.cpp
Filter=D
LastObject=IDC_BUTTON_SCAN
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=14_3Dlg.h
ImplementationFile=14_3Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY14_3_DIALOG]
Type=1
Class=CMy14_3Dlg
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_ADDRESS,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_USER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_PASS,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PORT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_LEVEL,edit,1350631552
Control11=IDC_BUTTON_SCAN,button,1342242816
Control12=IDC_FTPTREE,SysTreeView32,1350631431

[CLS:CFTPTreeCtrl]
Type=0
HeaderFile=FTPTreeCtrl.h
ImplementationFile=FTPTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W

