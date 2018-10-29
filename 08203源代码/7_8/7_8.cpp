#include <windows.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明

HWND hWndMain;		//定义窗口句柄
HDC hDC;			//定义设备环境句柄
HDC hdcmem;			//定义内存句柄
HBITMAP hBm;		//定义位图句柄
BITMAP bm;			//定义位图结构变量
int iY=80;			//位图左上角初始y坐标
int iWindowWidth,iWindowHeight;		//窗口的宽度和高度
char cUpWarn[]="不能再向上移动了";		//向上警告字符串
char cDownWarn[]="不能再向下移动了";	//向下警告字符串


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)			//主函数
{
	MSG Message;		//定义消息变量

	hBm=LoadBitmap(hInstance,"forest");		//加载位图
	GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);	//获得位图信息
	iWindowWidth=2*bm.bmWidth;					//得到窗口的宽度
	iWindowHeight=2*bm.bmHeight;				//得到窗口的高度

	if(!InitWindowsClass(hInstance))		//初始化窗口类
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//初始化窗口
		return FALSE;
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);			//消息循环
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam)			//消息处理函数
{
	PAINTSTRUCT ps;				//定义包含绘图信息的结构变量

	switch(iMessage)
	{
	case WM_LBUTTONDOWN:			//点击鼠标左键
		iY=iY-10;					//位图高度-10
		InvalidateRect(hWnd,NULL,1);//刷新用户区
		break;
	case WM_RBUTTONDOWN:			//点击鼠标右键
		iY=iY+10;					//位图高度+10;
		InvalidateRect(hWnd,NULL,1);//刷新用户区
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_UP:					//按上箭头时,位置-10
			iY=iY-10;
			break;
		case VK_DOWN:				//按下箭头时,位置+10
			iY=iY+10;
			break;
		}
		InvalidateRect(hWnd,NULL,1);//刷新用户区
		break;
	case WM_CREATE:					//初始化窗口消息
		hDC=GetDC(hWnd);			//得到设备环境指针
		hdcmem=CreateCompatibleDC(hDC);	//得到内存指针
		ReleaseDC(hWnd,hDC);		//删除设备环境指针
	case WM_PAINT:					//处理绘图消息
		hDC=BeginPaint(hWnd,&ps);	//得到设备环境指针
		if(iY>0&&iY<iWindowHeight/2)		//当位图完整的在窗口中时
		{
			SelectObject(hdcmem,hBm);		//选入内存句柄
			BitBlt(hDC,60,iY,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
											//输出位图
		}
		else if(iY<=0)				//当位图的上边界超出了窗口时
		{
			TextOut(hDC,0,0,cUpWarn,sizeof(cUpWarn));//输出警告
		}
		else						//当位图的下边界超出了窗口时
		{
			TextOut(hDC,0,0,cDownWarn,sizeof(cDownWarn));//输出警告
		}
		EndPaint(hWnd,&ps);			//输出环境指针
		break;
	case WM_DESTROY:				//关闭窗口消息
		DeleteObject(hBm);			//删除内存句柄
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
	hWnd=CreateWindow("BitmapInstance",		//窗口类名称
					"位图显示实例程序",	 	 //标题栏名称
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮
					CW_USEDEFAULT,			//窗口左上角坐标
					0,
					iWindowWidth,			//采用自定义的高度和宽度
					iWindowHeight,
					NULL,					//无父窗口
					NULL,					//无菜单
					hInstance,				//当前应用实例句柄
					NULL);					//指向传递给窗口的参数的指针.不用
	if(!hWnd)		//创建失败
		return FALSE;
	hWndMain=hWnd;	//给全局窗口句柄付值
	ShowWindow(hWnd,nCmdShow);	//显示窗口
	UpdateWindow(hWnd);			//刷新用户区
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;					//无窗口类扩展
	WndClass.cbWndExtra=0;					//无窗口实例扩展
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标
	WndClass.hInstance=hInstance;			//当前实例
	WndClass.lpfnWndProc=WndProc;			//消息处理函数
	WndClass.lpszClassName="BitmapInstance";//窗口类名称
	WndClass.lpszMenuName="Menu";			//定义菜单为Menu
	WndClass.style=0;						//缺省窗口风格
	return RegisterClass(&WndClass);	//返回窗口注册值
}
