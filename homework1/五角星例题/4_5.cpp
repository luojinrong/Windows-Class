#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.
HWND hWndMain;

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
	HBRUSH hBrush;			//定义画刷句柄
	HPEN hPen;				//定义画笔句柄
	PAINTSTRUCT PtStr;		//定义包含绘图信息的结构体变量
	double dfRadious0=100.0,dfRadious1;		//定义外部和内部正五边形外接圆半径.
	POINT lpOuterPoints[5],lpInnerPoints[5];//定义外,内正五边形点结构数组.
	POINT lpTriangle[3];                    //定义三角形点结构数组.
	dfRadious1=dfRadious0*sin(0.1*Pi)/sin(126.0/180*Pi);//根据外圆半径计算内园半径.
	//计算内外正五边形的点坐标.
	for(int i=0;i<5;i++)
	{
		lpOuterPoints[i].x=(long)(dfRadious0*cos(i*72.0/180*Pi));
		lpOuterPoints[i].y=(long)(dfRadious0*sin(i*72.0/180*Pi));
		lpInnerPoints[i].x=(long)(dfRadious1*cos(i*72.0/180*Pi+36.0/180*Pi));
		lpInnerPoints[i].y=(long)(dfRadious1*sin(i*72.0/180*Pi+36.0/180*Pi));
	}

	switch(iMessage)
	{
	case WM_PAINT:							//处理绘图消息.
		hDC=BeginPaint(hWnd,&PtStr);		//得到设备环境句柄
		SetMapMode(hDC,MM_ANISOTROPIC);		//设置映射模式.
		SetWindowOrgEx(hDC,-100,-100,NULL);	//设置坐标原点.

		hPen=CreatePen(PS_SOLID,1,RGB(255,0,0));	//创新红色画笔.
		SelectObject(hDC,hPen);						//将画笔选入.
		Polygon(hDC,lpOuterPoints,5);				//画正五边形.
			//填充正五边形的不同区域.
		for(i=0;i<5;i++)
		{
			lpTriangle[0]=lpOuterPoints[i%5];	//生成图形中的三角形区域的坐标.
			lpTriangle[1]=lpInnerPoints[i%5];
			lpTriangle[2]=lpOuterPoints[(i+1)%5];
					//创新新画刷.
			hBrush=CreateSolidBrush(RGB(i*10,i*20,i*30));
			SelectObject(hDC,hBrush);	//选入新画刷.
			Polygon(hDC,lpTriangle,3);	//画三角形区域.
			lpTriangle[2]=lpInnerPoints[(i+4)%5];	//生成图形中的三角形区域的坐标.
			hBrush=CreateSolidBrush(RGB(i*40,i*30,i*20));//创新画刷.
			SelectObject(hDC,hBrush);		//选入画刷.
			Polygon(hDC,lpTriangle,3);		//画三角形区域.
		}
		hBrush=CreateSolidBrush(RGB(255,255,255));//创新白画刷.
		SelectObject(hDC,hBrush);		//选入画刷.
		Polygon(hDC,lpInnerPoints,5);	//画中心的五边形.
			
			//用不同种颜色的画笔来绘制五角星.
		MoveToEx(hDC,lpOuterPoints[0].x,lpOuterPoints[0].y,NULL);
		for(i=1;i<=5;i++)
		{
			hPen=CreatePen(PS_SOLID,1,RGB(0,i*51,0));
			SelectObject(hDC,hPen);
			LineTo(hDC,lpOuterPoints[(i+2)%5].x,lpOuterPoints[(i+2)%5].y);
		}
		hPen=(HPEN)(GetStockObject(PS_NULL));

		DeleteObject(hPen);		//删除画笔.
		DeleteObject(hBrush);	//删除画刷.
		EndPaint(hWnd,&PtStr);	//结束绘图.
		return 0;
	case WM_DESTROY:		//处理关闭窗口信息.
		PostQuitMessage(0);		//向应用程序发送WM_QUIT消息.
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)	//初始化
{
	HWND hWnd;					//定义窗口句柄.
	hWnd=CreateWindow("Polygon",				//窗口类名.
					"五边形",					//窗口实例标题.
					WS_OVERLAPPEDWINDOW,		//窗口风格.带边框,标题栏,系统菜单和最大和最小按钮.
					CW_USEDEFAULT,				//窗口左上角坐标.
					0,							//窗口左上角坐标.
					CW_USEDEFAULT,				//窗口宽度
					0,							//窗口高度	
					NULL,						//无父窗口.
					NULL,						//无主菜单.
					hInstance,					//创建此窗口的应用程序的当前句柄.
					NULL);						//指向一个传递给窗口的参数值从指针.
												//不使用该值.
	if(!hWnd)			//如果窗口创建失败,返回false.
		return FALSE;
	hWndMain=hWnd;		//将窗口句柄传递给全局变量.
	ShowWindow(hWnd,nCmdShow);		//显示窗口.
	UpdateWindow(hWnd);				//更新并绘制用户区.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)	//初始化窗口类.
{
	WNDCLASS WndClass;					//定义窗口类.
	WndClass.cbClsExtra=0;				//窗口类无扩展.
	WndClass.cbWndExtra=0;				//窗口实例无扩展.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//窗口背景为白色.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//窗口采用箭头光标.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//窗口的最小化图标为缺省图标.
	WndClass.hInstance=hInstance;					//当前实例句柄.
	WndClass.lpfnWndProc=WndProc;					//窗口处理函数.
	WndClass.lpszClassName="Polygon";				//窗口类名.
	WndClass.lpszMenuName=NULL;						//无菜单
	WndClass.style=0;								//窗口类型为缺省类型.
	return RegisterClass(&WndClass);				//返回注册窗口的值.
}