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
HFONT CreateFont(HDC hDC,int nCharHeight,int nCharWidth);//创建字体函数声明.
HWND hWndMain;			//定义窗口句柄.

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
	HFONT hF;				//定义字体句柄.	
	PAINTSTRUCT ps;			//定义包含绘图信息的结构体变量
	char lpsz_1[]="欲穷千里目更上一层楼";	//定义输出的字符串.(白日依山尽黄河入海流)
	int nCharlen=strlen(lpsz_1)/2;	//定义字符串长度变量.
	int X=0,Y=0,i;
	int nCharHeight;

	switch(iMessage)
	{
	case WM_PAINT:					//处理绘图消息.
		hDC=BeginPaint(hWnd,&ps);	//获得设备环境指针.
		SetMapMode(hDC,MM_ANISOTROPIC);		//设置映射模式.
		SetWindowExtEx(hDC,640,480,NULL);	//设置窗口范围.
		SetViewportExtEx(hDC,640,480,NULL);	//设置视口范围.
		//输出字体大小线形变化的艺术字.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 40-(int)((40.0-15.0)/(nCharlen-1)*i);//计算字符的高度.
			X = i*30;							//字符输出位置的X坐标.
			Y = 50-nCharHeight/2;				//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(255-i*15,0,0));//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,15);			//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 15+(int)((40.0-15.0)/(nCharlen-1)*i);
			X = i*30;
			Y = 75-nCharHeight/2;
			SetTextColor(hDC,RGB(105+i*15,0,0));
			hF = CreateFont(hDC,nCharHeight,15);			//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//输出字体大小双线形变化的艺术字.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = (int)(-1.23*i*i+11.07*i+15.1);//计算字符的高度.
			X = i*30;
			Y = 120-nCharHeight/2;				//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(0,255-i*15,0));//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,15);	//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = (int)(0.9*i*i+15);//计算字符的高度.
			X = i*30;
			Y = 180-nCharHeight/2;				//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(0,0,255-i*20));//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,15);	//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//输出位置为正弦波的字符串.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30;							//字符的高度.
			X = i*30;									//字符输出位置的X坐标.
			Y = (int)(250-40*sin(2*Pi/(nCharlen-1)*i));	//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(0,255-i*15,255-i*20));	//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,15);			//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//输出位置为余弦波的字符串.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30;						//字符的高度.
			X = i*30;								//字符输出位置的X坐标
			Y = (int)(360-40*cos(2*Pi/(nCharlen-1)*i));//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(150,50,255-i*20));	//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,15);		//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//输出位置为圆形的字符串.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30;						//字符的高度.
			X = (int)(420+70*cos(2*Pi/(nCharlen)*i));//字符输出位置的X坐标.
			Y = (int)(300+70*sin(2*Pi/(nCharlen)*i));//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(255-i*15,100,0));	//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,15);		//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//输出位置为半圆形.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30-i*2;							//字符的高度.
			X = (int)(420-80*cos(-Pi/(nCharlen)*i));		//字符输出位置的X坐标.
			Y = (int)(120+80*sin(-Pi/(nCharlen)*i)-nCharHeight/2);	//字符输出位置的Y坐标.
			SetTextColor(hDC,RGB(255-i*15,100,255-i*15));	//设置字符的颜色.
			hF = CreateFont(hDC,nCharHeight,0);				//定义字体.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}

		DeleteObject(hF);				//删除字体句柄.
		EndPaint(hWnd,&ps);				//删除设备用户指针.
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("5_8",				//窗口类名称.
					"字体显示实例程序",		 //标题栏名称.
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,
					640,					//窗口高度和宽度.
					480,
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
	WndClass.lpszClassName="5_8";			//窗口类名称.
	WndClass.lpszMenuName=NULL;				//无菜单.
	WndClass.style=0;						//缺省窗口风格.
	return RegisterClass(&WndClass);		//返回窗口注册值.
}

//定义字体函数.
HFONT CreateFont(HDC hDC,int nCharHeight,int nCharWidth)
{
	HFONT hFont;
	hFont=CreateFont(				//定义字体句柄.
		nCharHeight,				//字体高度.
		nCharWidth,					//宽度.
		0,							//文本倾斜度为0,表示水平.
		0,							//字体倾斜度为0.
		400,						//字体粗度.400为正常.
		0,							//是斜体字?,
		0,							//无下划线.
		0,							//无删除线.
		ANSI_CHARSET,				//表示所用的字符集为ANSI_CHARSET.
		OUT_DEFAULT_PRECIS,			//删除精度为缺省值.
		CLIP_DEFAULT_PRECIS,		//裁剪精度为缺省值.
		DEFAULT_QUALITY,			//输出质量为缺省值.
		DEFAULT_PITCH|FF_DONTCARE,	//字间距和字体系列使用缺省值.
		"Arial");					//字体名称.
	if(hFont == NULL) return NULL;
	else return hFont;
}