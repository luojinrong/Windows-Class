#include <windows.h>
#include "7_9.h"

long WINAPI WndProc(HWND hWnd,UINT iMessage,
					WPARAM wParam,LPARAM lParam);
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);		//对话框处理函数

HWND hDlg;				//定义对话框句柄
HINSTANCE hInst;		//定义应用程序实例句柄

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)	
{
	MSG Message;					//定义消息变量
	HWND hWnd;						//定义窗口句柄
	WNDCLASS WndClass;				//定义窗口类
	WndClass.cbClsExtra=0;			//无窗口类扩展
	WndClass.cbWndExtra=0;			//无窗口实例扩展
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标
	WndClass.hInstance=hInstance;			//当前实例
	WndClass.lpfnWndProc=WndProc;			//消息处理函数
	WndClass.lpszClassName="DlgInstance";//窗口类名称
	WndClass.lpszMenuName="Menu";			//定义菜单为Menu
	WndClass.style=0;						//缺省窗口风格

	if(!RegisterClass(&WndClass))			//注册窗口.
	{
		MessageBeep(0);			//注册失败发出警告声.
		return FALSE;
	}

	hWnd=CreateWindow("DlgInstance",		//窗口类名称
					"非模式对话框",		 	 //标题栏名称
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮
					CW_USEDEFAULT,			//窗口左上角坐标
					0,
					CW_USEDEFAULT,			//采用自定义的高度和宽度
					0,
					NULL,					//无父窗口
					NULL,					//无菜单
					hInstance,				//当前应用实例句柄
					NULL);					//指向传递给窗口的参数的指针

	ShowWindow(hWnd,nCmdShow);				//显示窗口
	UpdateWindow(hWnd);						//刷新用户区
	hInst=hInstance;						//将应用程序句柄传递给全局变量

	while(GetMessage(&Message,0,0,0))
	{
		if(!IsDialogMessage(hDlg,&Message))		//若是对话框消息,发往对话框处理函数
		{
			TranslateMessage(&Message);			//消息循环
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_SHOW:						//点击Show菜单
			hDlg=CreateDialog(hInst,"Show",hWnd,(DLGPROC)DlgProc);	//显示对话框
			break;
		case IDM_HIDE:						//点击Hide菜单
			DestroyWindow(hDlg);			//删除对话框
			break;
		case IDM_EXIT:						//点击Exit菜单
			SendMessage(hWnd,WM_DESTROY,0,0);	//发送退出消息
			break;
		}
		break;
	case WM_DESTROY:						//退出
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}


//对话框处理函数
BOOL CALLBACK DlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:			//初始化对话框
		return 1;
	}
	return 0;
}