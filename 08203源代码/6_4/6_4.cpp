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
	WORD x,y;				//定义鼠标的位置坐标.
	HCURSOR hCursor;		//定义光标句柄.
	HBRUSH hBrush;
	LPSIZE lpSize;		//窗口尺寸结构.
	static char cLeftBtn[]="LEFT BUTTON";	//定义单击左键时的输出字符.
	static char cRightBtn[]="RIGHT BUTTON";	//定义单击右键时的输出字符.
	RECT ClientRect;

	switch(iMessage)
	{
	case WM_MOUSEMOVE:			//处理鼠标移动信息.
		x=LOWORD(lParam);		//获得鼠标的X坐标.
		y=HIWORD(lParam);		//获得鼠标的Y坐标.
		GetClientRect(hWnd,&ClientRect);	//得到窗口大小
		if(y>=0&&y<=ClientRect.bottom)
		{
			if(y>=0&&y<=ClientRect.bottom/5)		//在此区域,是箭头.
			{
				hCursor=LoadCursor(NULL,IDC_ARROW);
				SetCursor(hCursor);
			}
			else if(y>=ClientRect.bottom/5&&y<=ClientRect.bottom/5*2)	//在此区域为十字图标.
			{
				hCursor=LoadCursor(NULL,IDC_CROSS);
				SetCursor(hCursor);
			}
			else if(y>=ClientRect.bottom/5*2&&y<=ClientRect.bottom/5*3)	//在此区域为东北西南方向的箭头光标.
			{
				hCursor=LoadCursor(NULL,IDC_SIZENESW);
				SetCursor(hCursor);
			}
			else if(y>=ClientRect.bottom/5*3&&y<=ClientRect.bottom/5*4)	//在此区域为西北东南方向的箭头光标.
			{
				hCursor=LoadCursor(NULL,IDC_SIZENS);
				SetCursor(hCursor);
			}
			else				//在此区域为等待光标.
			{
				hCursor=LoadCursor(NULL,IDC_WAIT);
				SetCursor(hCursor);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:		//单击左建.
		hDC=GetDC(hWnd);		//得到设备环境指针.
		SetBkColor(hDC,RGB(255,255,0));		//设置背景色.
		TextOut(hDC,0,0,cLeftBtn,strlen(cLeftBtn));		//输出.
		ReleaseDC(hWnd,hDC);	//释放设备环境指针.
		break;
	case WM_RBUTTONDOWN:		//单击右建.
		hDC=GetDC(hWnd);		//得到设备环境指针.
		SetBkColor(hDC,RGB(255,255,0));	//设置背景色.
		TextOut(hDC,0,0,cRightBtn,strlen(cRightBtn));	//输出.
		ReleaseDC(hWnd,hDC);	//释放设备环境指针.
		break;
	case WM_SIZE:
		hDC=GetDC(hWnd);	//得到设备环境指针.
		SetMapMode(hDC,MM_ANISOTROPIC);	//设置映象模式.
		SetViewportExtEx(hDC,LOWORD(lParam),HIWORD(lParam),lpSize);	//设置试口区域.
		SetWindowExtEx(hDC,100,50,lpSize);	//设置窗口区域.

		hBrush=CreateSolidBrush(RGB(255,255,255));	//定义白画刷.	
		SelectObject(hDC,hBrush);				//选入白画刷.
		Rectangle(hDC,0,0,100,10);				//填充矩形
		DeleteObject(hBrush);					//删除画刷.

		hBrush=CreateSolidBrush(RGB(0,255,0));	//定义绿画刷.
		SelectObject(hDC,hBrush);				//选入绿画刷.
		Rectangle(hDC,0,10,100,20);				//填充矩形.
		DeleteObject(hBrush);					//删除画刷.

		hBrush=CreateSolidBrush(RGB(0,0,255));	//定义蓝画刷.
		SelectObject(hDC,hBrush);				//选入蓝画刷.
		Rectangle(hDC,0,20,100,30);				//填充矩形.
		DeleteObject(hBrush);					//删除画刷.

		hBrush=CreateSolidBrush(RGB(255,255,0));	//定义黄画刷.
		SelectObject(hDC,hBrush);					//选入黄画刷.
		Rectangle(hDC,0,30,100,40);					//填充矩形.
		DeleteObject(hBrush);						//删除画刷.

		hBrush=CreateSolidBrush(RGB(255,0,0));		//定义红画刷.
		SelectObject(hDC,hBrush);					//选入红画刷.
		Rectangle(hDC,0,40,100,50);					//填充矩形.
		DeleteObject(hBrush);						//删除画刷.

		ReleaseDC(hWnd,hDC);						//删除设备环境指针.
		break;
	case WM_DESTROY:								//处理退出窗口信息.
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
	hWnd=CreateWindow("6_4",						//窗口类名称.
					"鼠标显示实例程序",				//标题栏名称.
					WS_OVERLAPPEDWINDOW,			//窗口样式.有标题栏和最大最小化按钮.
					CW_USEDEFAULT,					//窗口左上角坐标.
					0,
					600,							//采用缺省的高度和宽度.
					400,
					NULL,							//无父窗口.
					NULL,							//无菜单.
					hInstance,						//当前应用实例句柄.
					NULL);							//指向传递给窗口的参数的指针.不用.
	if(!hWnd)										//创建失败.	
		return FALSE;
	hWndMain=hWnd;									//给全局窗口句柄付值.
	ShowWindow(hWnd,nCmdShow);						//显示窗口.
	UpdateWindow(hWnd);								//刷新用户区.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;							//无窗口类扩展.
	WndClass.cbWndExtra=0;							//无窗口实例扩展.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标.
	WndClass.hInstance=hInstance;					//当前实例.
	WndClass.lpfnWndProc=WndProc;					//消息处理函数.
	WndClass.lpszClassName="6_4";					//窗口类名称.
	WndClass.lpszMenuName=NULL;						//无菜单.
	WndClass.style=0;								//缺省窗口风格.
	return RegisterClass(&WndClass);				//返回窗口注册值.
}
