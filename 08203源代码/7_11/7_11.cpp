#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "7_11.h"

LRESULT CALLBACK WndProc(HWND hWnd,	UINT iMessage,
					UINT wParam,LONG lParam);	

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明
HWND hWndMain;										//定义全局窗口句柄
HINSTANCE hInst;									//定义实例句柄

OPENFILENAME ofn;
CHOOSECOLOR  chc;
CHOOSEFONT   chf;


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	HACCEL hAccel;
	hInst = hInstance;

	if(!InitWindowsClass(hInstance))		//初始化窗口类
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//初始化窗口
		return FALSE;

	hAccel = LoadAccelerators(hInstance,"Menu");	//加载加速键资源
	while(GetMessage(&Message,0,0,0))
	{
		if(!TranslateAccelerator(hWndMain,hAccel,&Message))//截获加速键消息
		{
			TranslateMessage(&Message);			//消息循环
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	static char lpstrFileName[] = ""; 
	static COLORREF clref[16]={0x00ff0000};

	switch(iMessage)
	{
	case WM_CREATE:			
		//注意:此处只标注了一些常用的OPENFILENAME结构的成员
		ofn.lStructSize = sizeof(OPENFILENAME);				//数据结构长度
		ofn.hwndOwner = hWnd;								//拥有该结构的窗口句柄
		ofn.hInstance = hInst;								//应用程序实例句柄
		ofn.lpstrFilter = "Text Files(*.TXT)\0*.txt\0"\
						"All Files (*.*)\0*.*\0";			//文件过滤器
		ofn.lpstrCustomFilter = NULL;						//自定义的文件过滤器
		ofn.nMaxCustFilter = 0;
		ofn.nFilterIndex = 1;								//文件过滤器正文串索引值
		ofn.lpstrFile = NULL;								//指向列表框文件的指针
		ofn.nMaxFile = 0;
		ofn.lpstrFileTitle = NULL;							//指向选定文件名的指针
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;
		ofn.Flags = 0;										//对话框标志
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = NULL;
		ofn.lCustData = 0;
		ofn.lpfnHook = NULL;						//钩子函数指针.同对话框处理函数功能一样
		ofn.lpTemplateName = NULL;

		//选择颜色通用对话框
		chc.lStructSize = sizeof(CHOOSECOLOR);		//结构大小
		chc.hwndOwner = hWnd;						//父窗口句柄
		chc.rgbResult = 0;							//设定默认颜色
		chc.lpCustColors = clref;					//指向用户自定义颜色数组的指针
		chc.Flags = 0;								//标志
		chc.lCustData = 0;							
		chc.lpfnHook = NULL;						//钩子函数指针.同对话框处理函数功能一样
		chc.lpTemplateName = NULL;

		//选择字通用体对话框
		chf.lStructSize = sizeof(CHOOSEFONT);		//结构大小
		chf.hwndOwner = hWnd;						//父窗口句柄
		chf.Flags = CF_BOTH | CF_TTONLY | CF_EFFECTS;//通用对话框属性

		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_NEW:
			break;
		case IDM_OPEN:
			//设置通用对话框样式
			ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
			ofn.lpstrTitle = "打开";				//通用对话框标题
			GetOpenFileName(&ofn);					//显示对话框
			break;
		case IDM_SAVEAS:
			//设置通用对话框样式.
			ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST
				|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
			ofn.lpstrTitle = "另存为...";				//通用对话框标题
			GetOpenFileName(&ofn);					//显示对话框
			break;
		case IDM_FONT:
			ChooseFont(&chf);
			break;
		case IDM_COLOR:
			ChooseColor(&chc);
			break;
		case IDM_ABOUT:
			MessageBox(hWnd,"通用对话框程序示例","关于",MB_OK);
			break;
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);
			break;
		}
		break;
	case WM_DESTROY:		//处理退出窗口信息.
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
	HMENU hMenu;

	hMenu = LoadMenu(hInstance,"Menu");
	hWnd=CreateWindow("7_11",				//窗口类名称.
					"通用对话框显示实例程序",//标题栏名称.
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,
					CW_USEDEFAULT,			//采用缺省的高度和宽度.
					0,
					NULL,					//无父窗口.
					hMenu,					//菜单.
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

	WndClass.cbClsExtra=0;			//无窗口类扩展
	WndClass.cbWndExtra=0;			//无窗口实例扩展
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标
	WndClass.hInstance=hInstance;			//当前实例
	WndClass.lpfnWndProc=WndProc;			//消息处理函数
	WndClass.lpszClassName="7_11";			//窗口类名称
	WndClass.lpszMenuName=NULL;				//无菜单
	WndClass.style=0;						//缺省窗口风格
	return RegisterClass(&WndClass);	//返回窗口注册值
}

