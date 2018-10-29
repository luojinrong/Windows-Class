#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

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
	WndClass.lpszClassName="4_7";					//窗口类名称.
	WndClass.lpszMenuName=NULL;						//无窗口菜单.
	WndClass.style=0;								//窗口类型为缺省类型.

	if(!RegisterClass(&WndClass))			//注册窗口.
	{
		MessageBeep(0);
		return FALSE;
	}
	
	hWnd=CreateWindow("4_7",				//窗口类名.
					"4_7",					//标题名.
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

	switch(iMessage)
	{
	case WM_PAINT:							//处理绘图消息.
		hDC=BeginPaint(hWnd,&PtStr);		//获得设备环境指针.
		SetMapMode(hDC,MM_ANISOTROPIC);		//设置映射模式.
		SetWindowExtEx(hDC,300,300,NULL);	//设置窗口区域.逻辑单位.
		SetViewportExtEx(hDC,600,600,NULL);	//设置视口区域.物理单位.
		SetViewportOrgEx(hDC,0,0,NULL);	//设置视口原点坐标为(0,0).物理单位.
		//绘制四个圆形.(笔的样式不同)
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	//选择空画刷.
		SelectObject(hDC,hBrush);
		hPen = CreatePen(PS_DASH,0,RGB(255,0,0));//建立虚线样式的红色笔
		SelectObject(hDC,hPen);					//选入设备环境.
		Ellipse(hDC,0,0,70,70);					//画圆.
		hPen = CreatePen(PS_DASHDOT,0,RGB(0,255,0));//建立点划线样式的绿色笔
		SelectObject(hDC,hPen);
		Ellipse(hDC,25,0,95,70);				//画圆.
		hPen = CreatePen(PS_DASHDOTDOT,0,RGB(0,0,255));//建立双点划线样式的蓝色笔
		SelectObject(hDC,hPen);
		Ellipse(hDC,0,25,70,95);
		hPen = CreatePen(PS_DOT,0,RGB(0,255,255));//建立点线样式的天蓝色笔
		SelectObject(hDC,hPen);
		Ellipse(hDC,25,25,95,95);
		//画6个圆角矩形.(实画刷样式不同.)
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//选择黑画刷.
		SelectObject(hDC,hBrush);		//选入设备环境.
		RoundRect(hDC,120,0,165,45,10,10);	//画圆角矩形.
		hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	//选择深灰画刷.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,165,0,210,45,10,10);
		hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//选择灰画刷.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,210,0,255,45,10,10);
		hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);	//选择虚画刷.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,120,45,165,90,10,10);
		hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//选择亮灰画刷.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,165,45,210,90,10,10);
		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//选择白画刷.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,210,45,255,90,10,10);
		//画6个矩形.(画刷阴影样式不同.)
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(200,200,200));//创建45度左上右下阴影线
		SelectObject(hDC,hBrush);		//选入设备环境.
		Rectangle(hDC,120,90,165,135);	//画矩形.
		hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(200,200,200));//创建45度交叉线
		SelectObject(hDC,hBrush);
		Rectangle(hDC,165,90,210,135);
		hBrush = CreateHatchBrush(HS_FDIAGONAL,RGB(200,200,200));//创建45度左下右上阴影线.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,210,90,255,135);
		hBrush = CreateHatchBrush(HS_CROSS,RGB(200,200,200));//创建垂直相交阴影线.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,120,135,165,175);
		hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));//创建水平阴影线.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,165,135,210,175);
		hBrush = CreateHatchBrush(HS_VERTICAL,RGB(200,200,200));//创建垂直阴影线.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,210,135,255,175);
		//画饼图。
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		hBrush = CreateSolidBrush(RGB(255,0,0));//创建红色画刷。
		SelectObject(hDC,hBrush);					//选入设备环境。
		Pie(hDC,10,100,							//画饼图。
				100,190,
				(int)(55+45*cos(2*Pi/3)),(int)(145+45*sin(2*Pi/3)),
				(int)(55+45*cos(0)),(int)(145+45*sin(0)));
		hBrush = CreateSolidBrush(RGB(0,255,255));//创建天蓝色画刷。
		SelectObject(hDC,hBrush);					//选入设备环境。
		Pie(hDC,10,100,
				100,190,
				(int)(55+45*cos(4*Pi/3)),(int)(145+45*sin(4*Pi/3)),
				(int)(55+45*cos(2*Pi/3)),(int)(145+45*sin(2*Pi/3)));
		hBrush = CreateSolidBrush(RGB(255,255,0));//创建黄色画刷。
		SelectObject(hDC,hBrush);					//选入设备环境。
		Pie(hDC,10,100,
				100,190,
				(int)(55+45*cos(2*Pi)),(int)(145+45*sin(2*Pi)),
				(int)(55+45*cos(4*Pi/3)),(int)(145+45*sin(4*Pi/3)));

		EndPaint(hWnd,&PtStr);				//释放环境指针。
		return 0;
	case WM_DESTROY:	//关闭窗口.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

