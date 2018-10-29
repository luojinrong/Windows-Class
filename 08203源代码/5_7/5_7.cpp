#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.
HFONT CreateFont(HDC hDC,int nCharHeight,BOOL bItalic);
HWND hWndMain;			//定义窗口句柄.
int nChar=0;
BOOL bRight=TRUE,bLeft=FALSE,bItalic=FALSE;

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
	TEXTMETRIC tm;			//定义包含字体信息的结构体变量.
	char lpsz_1[]="abcdefghijklmnopqrstuvwxyz";	//定义输出的字符串.
	int nCharlen=strlen(lpsz_1);	//定义字符串长度变量.
	int X=0,Y=0,i;

	switch(iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,300,NULL);	//建立计时器,每0.1秒发出WM_TIMER消息.

		break;
	case WM_PAINT:					//处理绘图消息.
		hDC=BeginPaint(hWnd,&ps);	//获得设备环境指针.
		
		//输出第1行字体. 
		hF = CreateFont(hDC,40,0);			//创建字体.
		SelectObject(hDC,hF);			//选入字体.
		GetTextMetrics(hDC,&tm);		//得到包含字体信息的结构体.
		Y=tm.tmExternalLeading+10;			//设置输出字符的Y坐标.
		for(i=0;i<nChar;i++)
		{
			SetTextColor(hDC,RGB(0,0,0));	//设置字体的颜色为黑色.
			X=X+tm.tmAveCharWidth*2;		//设置输出字符的X坐标.
			TextOut(hDC,X,Y,&lpsz_1[i],1);	//输出从第1个到第nChar个字符.
		}
		
		SetTextColor(hDC,RGB(255,0,0));	//设置字体的颜色为红色.
		X=X+tm.tmAveCharWidth*2;		//设置输出字符的X,Y坐标.
		Y=tm.tmExternalLeading;			//此字的位置高10个物理单位.
		TextOut(hDC,X,Y,&lpsz_1[nChar],1);	//输出第nChar个字符.

		Y=tm.tmExternalLeading+10;
		for(i=nChar+1;i<nCharlen;i++)
		{
			SetTextColor(hDC,RGB(0,0,0));	//设置字体的颜色为黑色.
			X=X+tm.tmAveCharWidth*2;		//设置输出字符的X坐标.
			TextOut(hDC,X,Y,&lpsz_1[i],1);	//输出后面的字符.
		}
		if(nChar == nCharlen)				//当输出到最后的一个字符时, 
		{
			bRight = FALSE;					//改变红色字移动的方向为向左.
			bLeft = TRUE;
		}
		else if(nChar == 0)					//当输出到第一个字时,
		{
			bRight = TRUE;					//改变红色字移动的方向为向右
			bLeft = FALSE;
		}
		if(bRight == TRUE) nChar++;
		else nChar--;
		DeleteObject(hF);				//删除字体句柄.

		//输出第2行字体.
		hF = CreateFont(hDC,40,bItalic);		//创建字体.大小为40.
		SelectObject(hDC,hF);			//选入字体.
		X = tm.tmAveCharWidth*2;		//设置输出位置.
		Y = tm.tmHeight*2;
		if(bItalic == TRUE) SetTextColor(hDC,RGB(0,0,0));
		else SetTextColor(hDC,RGB(0,255,255));
		TextOut(hDC,X,Y,lpsz_1,strlen(lpsz_1));	//输出.
		if(bItalic == TRUE) bItalic=FALSE;
		else bItalic=TRUE;

		DeleteObject(hF);				//删除字体句柄.
		EndPaint(hWnd,&ps);				//删除设备用户指针.
		return 0;
	case WM_TIMER:						//处理由计时器发出的消息.
		InvalidateRect(hWnd,NULL,1);	//刷新用户区.
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd,1);				//删除计时器
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("5_7",				//窗口类名称.
					"字体显示实例程序",		 //标题栏名称.
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,
					850,					//窗口高度和宽度.
					300,
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
	WndClass.lpszClassName="5_7";			//窗口类名称.
	WndClass.lpszMenuName=NULL;				//无菜单.
	WndClass.style=0;						//缺省窗口风格.
	return RegisterClass(&WndClass);		//返回窗口注册值.
}

HFONT CreateFont(HDC hDC,int nCharHeight,BOOL bItalic)
{
	HFONT hFont;
	hFont=CreateFont(				//定义字体句柄.
		nCharHeight,				//字体高度.
		0,							//由系统根据高宽比选取字体最佳宽度值.
		0,							//文本倾斜度为0,表示水平.
		0,							//字体倾斜度为0.
		400,						//字体粗度.400为正常.
		bItalic,					//是斜体字?,
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