#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "7_10.h"
#include <math.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明
HWND hWndMain;							//定义全局窗口句柄
HINSTANCE hInst;		//定义实例句柄
RECT rect1={100,100,100,100};			//定义矩形结构体.记录了图形的信息

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,
					UINT wParam,LONG lParam)
{
	HMENU hMenu1,hMenu2;				//定义菜单句柄
	HDC hDC;							//定义设备环境句柄
	static BOOL bCircle = FALSE,bRect = FALSE;	//设置绘制圆和矩形的标志变量
	static BOOL bMove = FALSE;			//设置移动标志
	PAINTSTRUCT ps;						//定义绘图结构体变量

	switch(iMessage)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_CIRCLE:				//单击圆形菜单
			hMenu1 = GetMenu(hWnd);		//得到菜单句柄
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_CHECKED);	//设置选中标志
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_UNCHECKED);//删除标志
			DeleteMenu(hMenu1,1,MF_BYPOSITION);				//删除“矩形”弹出菜单
			hMenu2 = CreateMenu();							//动态创建菜单
			//添加菜单项
			AppendMenu(hMenu2,MF_ENABLED,IDM_DRAWCIRCLE,"绘制圆形(&d)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_MOVECIRCLE,"移动圆形(&m)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMIN,"放大(&i)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMOUT,"缩小(&o)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_REDRAW,"重绘(&r)");
			//插入菜单。
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,"圆形(&c)");
			DrawMenuBar(hWndMain);							//刷新菜单
			bCircle = FALSE;								//绘圆标志为假
			bRect = FALSE;									//绘矩形标志为假
			bMove = FALSE;									//移动标志为假
			rect1.left = 100;								//恢复矩形的初始状态
			rect1.right = 100;
			rect1.bottom = 100;
			rect1.top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			break;
		case IDM_RECTANGLE:			//单击矩形菜单
			hMenu1 = GetMenu(hWnd);		//得到菜单句柄
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_UNCHECKED);	//删除选中标志
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_CHECKED);	//设置选中标志
			DeleteMenu(hMenu1,1,MF_BYPOSITION);				//删除“圆形”弹出菜单
			hMenu2 = LoadMenu(hInst,"menuRect");			//得到菜单句柄
			//插入菜单
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,"矩形(&r)");
			DrawMenuBar(hWndMain);							//刷新菜单
			bCircle = FALSE;								//绘圆标志为假
			bRect = FALSE;									//绘矩形标志为假
			bMove = FALSE;									//移动标志为假
			rect1.left = 100;								//恢复矩形的初始状态
			rect1.right = 100;
			rect1.bottom = 100;
			rect1.top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			break;
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);	//发出关闭窗口信息
			break;
		case IDM_DRAWCIRCLE:			//绘制圆形
			bCircle = TRUE;									//绘圆标志为真
			bRect = FALSE;									//绘矩形标志为假
			bMove = FALSE;									//移动标志为假
			break;
		case IDM_DRAWRECT:			//绘制矩形
			bCircle = FALSE;								//绘圆标志为假
			bRect = TRUE;									//绘矩形标志为真
			bMove = FALSE;									//移动标志为假
			break;
		case IDM_MOVECIRCLE:			//移动圆形
			bMove = TRUE;									//移动标志为真
			break;
		case IDM_MOVERECT:			//移动矩形
			bMove = TRUE;									//移动标志为真
			break;
		case IDM_ZOOMIN:			//放大
			if(bCircle ==TRUE || bRect ==TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1.right-rect1.left);		//计算长度
				nWidth = abs(rect1.top-rect1.bottom);		//计算宽度
				rect1.right = (int)(rect1.left+nLength*1.2);	//放大
				rect1.bottom = (int)(rect1.top+nWidth*1.2);
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			break;
		case IDM_ZOOMOUT:			//缩小
			if(bCircle ==TRUE || bRect ==TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1.right-rect1.left);		//计算长度
				nWidth = abs(rect1.top-rect1.bottom);		//计算宽度
				rect1.right = (int)(rect1.left+nLength/1.2);	//缩小
				rect1.bottom = (int)(rect1.top+nWidth/1.2);
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			break;
		case IDM_REDRAW:							//重新绘图
			bMove = FALSE;									//移动标志为假
			rect1.left = 100;								//恢复矩形的初始状态
			rect1.right = 100;
			rect1.top = 100;
			rect1.bottom = 100;
			InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			break;
		}
		break;
	case WM_KEYDOWN:	
		if(bMove ==TRUE)
		{
			if(wParam == VK_LEFT)
			{										//按left键,向左移动
				rect1.left -=10;
				rect1.right -=10;
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			else if(wParam == VK_RIGHT)
			{										//按right键,向右移动
				rect1.left +=10;
				rect1.right +=10;
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			else if(wParam == VK_UP)
			{										//按up键时,向上移动
				rect1.top -=10;
				rect1.bottom -=10;
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			else if(wParam == VK_DOWN)
			{										//按down键,向下移动
				rect1.top +=10;
				rect1.bottom +=10;
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
		}
		else if(bCircle == TRUE || bRect ==TRUE)
		{
			if(wParam == VK_RIGHT)
			{
				rect1.right +=10;					//按下右箭头时矩形框长度加10
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			else if(wParam == VK_DOWN)
			{
				rect1.bottom +=10;					//按下下箭头矩形框高度加10
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			else if(wParam == VK_UP)
			{
				rect1.bottom -=10;					//按下上箭头矩形框高度-10
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
			else if(wParam == VK_LEFT)
			{
				rect1.right -=10;					//按下左箭头矩形框高度-10
				InvalidateRect(hWnd,NULL,TRUE);	//发出刷新信息
			}
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);
		if(bCircle == TRUE)
		{						//绘制圆形
			Ellipse(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		if(bRect == TRUE)
		{						//绘制矩形
			Rectangle(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		EndPaint(hWnd,&ps);
		break;
	case WM_DESTROY:		//处理退出窗口信息
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
	hWnd=CreateWindow("7_10",				//窗口类名称
					"菜单显示实例程序",		 //标题栏名称
					WS_OVERLAPPEDWINDOW,	//窗口样式
					CW_USEDEFAULT,			//窗口左上角坐标
					0,
					CW_USEDEFAULT,			//采用缺省的高度和宽度
					0,
					NULL,					//无父窗口
					hMenu,					//菜单
					hInstance,				//当前应用实例句柄
					NULL);					//指向传递给窗口的参数的指针
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
	WndClass.cbClsExtra=0;			//无窗口类扩展
	WndClass.cbWndExtra=0;			//无窗口实例扩展
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标
	WndClass.hInstance=hInstance;			//当前实例
	WndClass.lpfnWndProc=WndProc;			//消息处理函数
	WndClass.lpszClassName="7_10";			//窗口类名称
	WndClass.lpszMenuName=NULL;				//无菜单
	WndClass.style=0;						//缺省窗口风格
	return RegisterClass(&WndClass);	//返回窗口注册值
}
