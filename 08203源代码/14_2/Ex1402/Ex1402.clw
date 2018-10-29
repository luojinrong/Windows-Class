; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx1402Dlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Ex1402.h"

ClassCount=4
Class1=CEx1402App
Class2=CEx1402Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CListenSocket
Resource3=IDD_EX1402_DIALOG

[CLS:CEx1402App]
Type=0
HeaderFile=Ex1402.h
ImplementationFile=Ex1402.cpp
Filter=N

[CLS:CEx1402Dlg]
Type=0
HeaderFile=Ex1402Dlg.h
ImplementationFile=Ex1402Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CEx1402Dlg

[CLS:CAboutDlg]
Type=0
HeaderFile=Ex1402Dlg.h
ImplementationFile=Ex1402Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EX1402_DIALOG]
Type=1
Class=CEx1402Dlg
ControlCount=15
Control1=IDC_BUTTON_SEND,button,1342242816
Control2=IDC_BUTTON_CLEAR,button,1342242816
Control3=IDC_EDIT_SEND,edit,1352728644
Control4=65535,static,1342308352
Control5=IDC_BUTTON_CLEAR_RECV,button,1342242816
Control6=IDC_EDIT_RECV,edit,1352730692
Control7=65535,static,1342308352
Control8=65535,static,1342308352
Control9=IDC_EDIT_TIP,edit,1342244992
Control10=65535,static,1342308352
Control11=IDC_IPADDRESS,SysIPAddress32,1342242816
Control12=IDC_BUTTON_CONNECT,button,1342242816
Control13=IDC_BUTTON_CLOSE,button,1342242816
Control14=IDC_BUTTON_LISTEN,button,1342242816
Control15=IDC_BUTTON_STOP,button,1342242816

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CListenSocket

