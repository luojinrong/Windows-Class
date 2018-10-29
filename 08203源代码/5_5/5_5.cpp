#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.
int CALLBACK pEnumFontFamProc(
  ENUMLOGFONT FAR *lpelf,  // pointer to logical-font data
  NEWTEXTMETRIC FAR *lpntm,  // pointer to physical-font data
  int FontType,            // type of font
  LPARAM lParam            // pointer to application-defined data
);
 
HWND hWndMain;			//定义窗口句柄.
int iFontSign=0;		//定义字体标志,表示采用何种字体.

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

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)			//消息处理函数.
{
	HDC hDC;				//定义设备环境句柄.
	HFONT hF;				//定义字体句柄.	
	PAINTSTRUCT ps;			//定义包含绘图信息的结构体变量
	TEXTMETRIC tm;			//定义包含字体信息的结构体变量.
	static char lpsz_1[]="只有付出才有收获  ";	//定义输出的字符串.
	char chFont[20];				//定义字体种类的字符串.
	int X=0,Y=0,i;
	static int nCharlen=strlen(lpsz_1);	//定义字符串长度变量.

	switch(iMessage)
	{
	case WM_PAINT:							//处理绘图消息.
		hDC=BeginPaint(hWnd,&ps);		//获得设备环境指针.
		for(i=0;i<nCharlen;i+=2)		//采用某种字体和颜色输出字符串.
		{
			SetTextColor(hDC,RGB((long)(255.0/nCharlen*i),//设置字体颜色.
								0,
								0));
			if(iFontSign%5==0) strcpy(chFont,"楷体_GB2312");	//设置包含字体信息的字符串.
			else if(iFontSign%5==1) strcpy(chFont,"宋体");	//iFont%表示以5为周期循环改变字体.
			else if(iFontSign%5==2) strcpy(chFont,"隶书");
			else if(iFontSign%5==3) strcpy(chFont,"黑体");
			else strcpy(chFont,"幼圆");
			hF=CreateFont(				//定义字体句柄.
				(long)(8+32.0*i/nCharlen),	//字体高度.
				0,							//由系统根据高宽比选取字体最佳宽度值.
				0,							//文本倾斜度为0,表示水平.
				0,							//字体倾斜度为0.
				400,						//字体粗度.400为正常.
				0,							//非斜体字,
				0,							//无下划线.
				0,							//无删除线.
				GB2312_CHARSET,				//表示所用的字符集为GB2312_CHARSET
				OUT_DEFAULT_PRECIS,			//删除精度为缺省值.
				CLIP_DEFAULT_PRECIS,		//裁剪精度为缺省值.
				DEFAULT_QUALITY,			//输出质量为缺省值.
				DEFAULT_PITCH|FF_DONTCARE,	//字间距和字体系列使用缺省值.
				chFont);					//字体名称.
			SelectObject(hDC,hF);			//选入字体.
			GetTextMetrics(hDC,&tm);		//得到包含字体信息的结构体.
			X=X+tm.tmAveCharWidth*2;		//设置输出字符的X坐标.
			Y=iFontSign%5*40+tm.tmExternalLeading;	//设置输出字符的Y坐标.
			TextOut(hDC,X,Y,&lpsz_1[i],2);	//输出第i个字符.产生滚动的效果.
			Sleep(400);						//暂停0.4秒.
			DeleteObject(hF);		//删除字体句柄.
		}
		iFontSign++;				//字体标志增加
		InvalidateRect(hWnd,NULL,1);//刷新用户区.
		EndPaint(hWnd,&ps);			//删除设备用户指针.
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
	hWnd=CreateWindow("5_5",				//窗口类名称.
					"字体显示实例程序",		 //标题栏名称.
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
	WndClass.lpszClassName="5_5";			//窗口类名称.
	WndClass.lpszMenuName=NULL;				//无菜单.
	WndClass.style=0;						//缺省窗口风格.
	return RegisterClass(&WndClass);	//返回窗口注册值.
}