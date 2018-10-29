#include <windows.h>
#include "7_7.h"
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.
HWND hWndMain;		//定义全局窗口句柄.

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)			//主函数
{
	MSG Message;
	if(!InitWindowsClass(hInstance))		//初始化窗口类.
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//初始化窗口.
		return FALSE;
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);			//消息循环.
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam)			//消息处理函数.
{
	switch(iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("7_7",				//窗口类名称.
					"菜单显示实例程序",		 //标题栏名称.
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,
					CW_USEDEFAULT,			//采用缺省的高度和宽度.
					0,
					NULL,					//无父窗口.
					NULL,					//无菜单.
					hInstance,				//当前应用实例句柄.
					NULL);					//指向传递给窗口的参数的指针.不用.
	if(!hWnd)		//创建失败.
		return FALSE;
	hWndMain=hWnd;	//给全局窗口句柄付值.
	ShowWindow(hWnd,nCmdShow);	//显示窗口.
	UpdateWindow(hWnd);			//刷新用户区.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;			//无窗口类扩展.
	WndClass.cbWndExtra=0;			//无窗口实例扩展.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标.
	WndClass.hInstance=hInstance;			//当前实例.
	WndClass.lpfnWndProc=WndProc;			//消息处理函数.
	WndClass.lpszClassName="7_7";			//窗口类名称.
	WndClass.lpszMenuName="Menu";			//定义菜单为Menu.
	WndClass.style=0;						//缺省窗口风格.
	return RegisterClass(&WndClass);	//返回窗口注册值.
}


