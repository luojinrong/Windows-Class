#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.
int nNum = 0,nMaxNum = 20;			//nMaxNum记录了叶片循环一周中绘图的次数.
									//nNum记录了当前的序数.

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)			//主函数
{
	MSG Message;			//定义消息变量.
	HWND hWnd;				//定义窗口句柄.

	WNDCLASS WndClass;		//定义窗口类.
	WndClass.cbClsExtra=0;		//无窗口类扩展.
	WndClass.cbWndExtra=0;		//无窗口实例扩展.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//窗口采用箭头光标.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//采用缺省图标.
	WndClass.hInstance=hInstance;					//当前应用程序句柄.
	WndClass.lpfnWndProc=WndProc;					//窗口处理函数.
	WndClass.lpszClassName="4_8";					//窗口类名称.
	WndClass.lpszMenuName=NULL;						//无窗口菜单.
	WndClass.style=0;								//窗口类型为缺省类型.

	if(!RegisterClass(&WndClass))			//注册窗口.
	{
		MessageBeep(0);
		return FALSE;
	}
	
	hWnd=CreateWindow("4_8",				//窗口类名.
					"4_8",					//标题名.
					WS_OVERLAPPEDWINDOW,	//带标题栏,最大和最小按钮的窗口.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,						
					600,				//采用宽度为450，高度为600.
					450,
					NULL,					//无父窗口.
					NULL,					//无主菜单.
					hInstance,				//当前实例句柄.
					NULL);					//不要此参数.
	ShowWindow(hWnd,nCmdShow);			//显示窗口.
	UpdateWindow(hWnd);					//更新并绘制用户区.

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
	HBRUSH hBrush;			//定义画刷句柄
	HPEN hPen;				//定义画笔句柄
	PAINTSTRUCT PtStr;		//定义包含绘图信息的结构体变量
	int nCentreX,nCentreY;	//定义3个叶片的圆心的坐标.
	double fAngle;

	switch(iMessage)
	{
	case WM_PAINT:							//处理绘图消息.
		hDC=BeginPaint(hWnd,&PtStr);		//获得设备环境指针.
		SetMapMode(hDC,MM_ANISOTROPIC);		//设置映射模式.
		SetWindowExtEx(hDC,400,300,NULL);	//设置窗口区域.逻辑单位.
		SetViewportExtEx(hDC,600,450,NULL);	//设置视口区域.物理单位.
		SetViewportOrgEx(hDC,300,200,NULL);	//设置视口原点坐标为(300,200).物理单位.
		//绘制外圆。
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		Ellipse(hDC,-100,-100,100,100);
		//绘制风车的叶片。
		hBrush = CreateSolidBrush(RGB(255,0,0));		//画红色的叶片.
		SelectObject(hDC,hBrush);
		fAngle = 2*Pi/nMaxNum*nNum;
		nCentreX = (int)(50*cos(fAngle));
		nCentreY = (int)(50*sin(fAngle));
		Pie(hDC,nCentreX-50,nCentreY-50,
			nCentreX+50,nCentreY+50,
			(int)(nCentreX+50*cos(fAngle)),(int)(nCentreY+50*sin(fAngle)),
			(int)(nCentreX+50*cos(fAngle+Pi)),(int)(nCentreY+50*sin(fAngle+Pi)));
		hBrush = CreateSolidBrush(RGB(255,255,0));		//画天蓝色的叶片.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(50*cos(fAngle+2*Pi/3));
		nCentreY = (int)(50*sin(fAngle+2*Pi/3));
		Pie(hDC,nCentreX-50,nCentreY-50,
			nCentreX+50,nCentreY+50,
			(int)(nCentreX+50*cos(fAngle+2*Pi/3)),(int)(nCentreY+50*sin(fAngle+2*Pi/3)),
			(int)(nCentreX+50*cos(fAngle+Pi+2*Pi/3)),(int)(nCentreY+50*sin(fAngle+Pi+2*Pi/3)));
		hBrush = CreateSolidBrush(RGB(0,255,255));		//画黄色的叶片.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(50*cos(fAngle+4*Pi/3));
		nCentreY = (int)(50*sin(fAngle+4*Pi/3));
		Pie(hDC,nCentreX-50,nCentreY-50,
			nCentreX+50,nCentreY+50,
			(int)(nCentreX+50*cos(fAngle+4*Pi/3)),(int)(nCentreY+50*sin(fAngle+4*Pi/3)),
			(int)(nCentreX+50*cos(fAngle+Pi+4*Pi/3)),(int)(nCentreY+50*sin(fAngle+Pi+4*Pi/3)));
		
		nNum++;				//当前序数加1.
		Sleep(100);			//等待0.1秒.
		InvalidateRect(hWnd,NULL,1);	//重绘窗口区域.

		EndPaint(hWnd,&PtStr);				//释放环境指针。
		return 0;
	case WM_DESTROY:	//关闭窗口.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

