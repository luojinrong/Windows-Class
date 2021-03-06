#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.
HWND hWndMain;							//定义全局窗口句柄.
RECT rect1;				//定义矩形结构体.记录了图形的信息.

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
	HDC hDC;				//定义设备环境句柄.
	static BOOL bCircle=FALSE,bRect=FALSE;	//设置绘制圆和矩形的标志变量.
	PAINTSTRUCT ps;			//定义绘图结构体变量.

	switch(iMessage)
	{
	case WM_KEYDOWN:	
		if(wParam == VK_CONTROL)		//按下Ctrl键时.
		{
			bCircle = TRUE;				//画圆.
			bRect = FALSE;
			rect1.left = 0;				//初始化矩形结构体.
			rect1.right = 0;
			rect1.top = 0;
			rect1.bottom = 0;
		}
		else if(wParam == VK_SHIFT)		//按下shift键时.
		{
			bRect = TRUE;				//画矩形.
			bCircle = FALSE;
			rect1.left = 0;				//初始化矩形结构体.
			rect1.right = 0;
			rect1.top = 0;
			rect1.bottom = 0;
		}
		else if(wParam == VK_RIGHT)
		{
			rect1.right +=10;			//按下右箭头时矩形框长度加10.
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息.
			}
		}
		else if(wParam == VK_DOWN)
		{
			rect1.bottom +=10;			//按下下箭头矩形框高度加10.
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息.
			}
		}
		else if(wParam == VK_PRIOR)
		{								//按pageup键时,向上移动.
			rect1.top -=10;
			rect1.bottom -=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息.
			}
		}
		else if(wParam == VK_NEXT)
		{								//按pagedown键,向下移动.
			rect1.top +=10;
			rect1.bottom +=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息.
			}
		}
		else if(wParam == VK_HOME)
		{								//按home键,向左移动.
			rect1.left -=10;
			rect1.right -=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息.
			}
		}
		else if(wParam == VK_END)
		{								//按end键,向右移动.
			rect1.left +=10;
			rect1.right +=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//发出重绘信息.
			}
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);
		if(bCircle == TRUE)
		{						//绘制圆形.
			Ellipse(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		if(bRect == TRUE)
		{						//绘制矩形.
			Rectangle(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		EndPaint(hWnd,&ps);
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
	hWnd=CreateWindow("6_4",				//窗口类名称.
					"鼠标显示实例程序",		 //标题栏名称.
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
	WndClass.lpszClassName="6_4";			//窗口类名称.
	WndClass.lpszMenuName=NULL;				//无菜单.
	WndClass.style=0;						//缺省窗口风格.
	return RegisterClass(&WndClass);	//返回窗口注册值.
}

