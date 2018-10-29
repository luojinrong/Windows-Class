#include<windows.h>	//包含应用程序中所需的数据类型和数据结构的定义
#include<tchar.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); //窗口函数说明

//--------------- 以下初始化窗口类 ----------------------
int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
	HWND hwnd ;
	MSG Msg ;
	WNDCLASSEX wndclass ;
	TCHAR lpszClassName[] = L"窗口";	//窗口类名
	TCHAR lpszTitle[]= L"My_Windows";	//窗口标题名
	//窗口类的定义
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style=0;			//窗口类型为缺省类型
	wndclass.lpfnWndProc=WndProc;	//定义窗口处理函数
	wndclass.cbClsExtra=0;		//窗口类无扩展
	wndclass.cbWndExtra=0;		//窗口实例无扩展
	wndclass.hInstance=hInstance;	//当前实例句柄
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	//窗口的最小化图标为缺省图标
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW) ;
	//窗口采用箭头光标
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	//窗口背景为白色
	wndclass.lpszMenuName=NULL;	//窗口中无菜单
	wndclass.lpszClassName=lpszClassName ;
	wndclass.hIconSm = LoadIcon(wndclass.hInstance,MAKEINTRESOURCE(IDI_APPLICATION));

	//窗口类名为"窗口"
	//--------------- 以下进行窗口类的注册 -------
	if(!RegisterClassEx( &wndclass))//如果注册失败则发出警告
	{ 
		MessageBeep(0) ;
		MessageBox(NULL,_T("窗口注册失败！"),_T("窗口注册"),NULL);
		return FALSE ;	
	}

	hwnd=CreateWindow(
		lpszClassName,		//窗口类名
		lpszTitle,			//窗口实例的标题名
		WS_OVERLAPPEDWINDOW,	//窗口的风格
		CW_USEDEFAULT,
		CW_USEDEFAULT,		//窗口左上角坐标为缺省值
		CW_USEDEFAULT,
		CW_USEDEFAULT,		//窗口的高和宽为缺省值
		NULL,				//此窗口无父窗口
		NULL,				//此窗口无主菜单
		hInstance,			//创建此窗口的应用程序的当前句柄
		NULL 				//不使用该值
		);
	//--------------- 显示窗口 ----------------------
	ShowWindow( hwnd, nCmdShow) ;
	//-------------- 绘制用户区 ---------------------
	UpdateWindow(hwnd);
	//----------------- 消 息 循 环 ---------------------- 
	while( GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage( &Msg) ;
		DispatchMessage( &Msg) ;
	}
	return Msg.wParam;	//消息循环结束即程序终止时将信息返回系统
}
LRESULT CALLBACK WndProc(	HWND hwnd,UINT message, WPARAM  wParam,LPARAM  lParam )
{  
	switch(message)
	{ 
	case WM_DESTROY:
		PostQuitMessage(0);
	default:	//缺省时采用系统消息缺省处理函数
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return(0);
}
