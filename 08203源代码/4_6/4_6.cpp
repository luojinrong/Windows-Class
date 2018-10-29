#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

double dfTheta=0,dfRange=100.0;						//正弦曲线的角度变量.
long i=0,j=0;
long lCentreX=0,lCentreY=0,lRadious=(long)(0.2*dfRange);
				//定义圆心坐标和圆坐标.
POINT lpSin[100];	//定义正弦曲线的点坐标.

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
	WndClass.lpszClassName="SIN";					//窗口类名称.
	WndClass.lpszMenuName=NULL;						//无窗口菜单.
	WndClass.style=0;								//窗口类型为缺省类型.

	if(!RegisterClass(&WndClass))			//注册窗口.
	{
		MessageBeep(0);
		return FALSE;
	}
	
	hWnd=CreateWindow("SIN",				//窗口类名.
					"4_6",					//标题名.
					WS_OVERLAPPEDWINDOW,	//带标题栏,最大和最小按钮的窗口.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,						
					CW_USEDEFAULT,			//采用缺省的宽度和高度.
					0,
					NULL,					//无父窗口.
					NULL,					//无主菜单.
					hInstance,				//当前实例句柄.
					NULL);					//不要此参数.
	ShowWindow(hWnd,nCmdShow);			//显示窗口.
	UpdateWindow(hWnd);					//更新并绘制用户区.

	for(int j=0;j<100;j++)		//生成正弦曲线的点坐标.
	{
		lpSin[j].x=(long)(j*2*Pi/100*60);
		lpSin[j].y=(long)(dfRange*sin(j*2*Pi/100));
	}
	
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
		SetWindowOrgEx(hDC,-200,-200,NULL);	//设置原点坐标为(-200,-200).
		
		hPen=CreatePen(PS_DASH,1,RGB(255,0,0));	//创新画笔.
		SelectObject(hDC,hPen);					//选入画笔.
		Polyline(hDC,lpSin,100);				//绘制正弦曲线.

		if(i<=25) //第一个1/4周期.
		{
			hPen=CreatePen(PS_DASH,1,RGB(255,0,0));//创新红笔.
			hBrush=CreateHatchBrush(HS_BDIAGONAL,RGB(255,0,0));//创新红画刷.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
		}
		else if(i<=50)//第二个1/4周期.
		{
			hPen=CreatePen(PS_DASH,1,RGB(0,255,0));//创新绿笔.
			hBrush=CreateHatchBrush(HS_DIAGCROSS,RGB(0,255,0));//创新绿刷.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
		}
		else if(i<=75)//第三个周期.
		{
			hPen=CreatePen(PS_DASH,1,RGB(0,0,255));//创新蓝笔
			hBrush=CreateHatchBrush(HS_CROSS,RGB(0,0,255));//创新蓝刷.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
		}
		else//第四个周期.
		{
			hPen=CreatePen(PS_DASH,1,RGB(255,255,0));//创新黄笔
			hBrush=CreateHatchBrush(HS_VERTICAL,RGB(255,255,0));//创新黄刷.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
		}
		SelectObject(hDC,hBrush);	//选入画刷.
		SelectObject(hDC,hPen);		//选入画笔.
		lCentreX=lpSin[i].x;		//圆心x坐标.
		lCentreY=lpSin[i].y;		//圆心y坐标.
		Ellipse(hDC,lCentreX-lRadious,lCentreY-lRadious,
			lCentreX+lRadious,lCentreY+lRadious);	//画圆.

		i++;
		DeleteObject(hPen);		//删除画笔.
		DeleteObject(hBrush);	//删除画刷.
		EndPaint(hWnd,&PtStr);	//删除设备环境指针.
		Sleep(100);				//停0.1秒.
		if(i<100) InvalidateRect(hWnd,NULL,1);	//刷新用户区.
		return 0;
	case WM_DESTROY:	//关闭窗口.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

