#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.
HWND hWndMain;		//定义窗口句柄.
int iFontFlag=0;	//定义字体标志.

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
	PAINTSTRUCT ps;		//定义包含绘图信息的结构体变量
	TEXTMETRIC tm;		//定义包含字体信息的结构体变量.
	char lpsz_1[]="欲穷千里目  更上一层楼";		//定义输出字符串.
	char chFont[7];		//定义包含字体的字符串.
	int X=0,Y=0,nCharlen=strlen(lpsz_1);

	switch(iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,200,NULL);		//设定定时器.每0.2秒发出WM_TIMER消息.
		break;
	case WM_PAINT:							//处理绘图消息.
		hDC=BeginPaint(hWnd,&ps);			//获取设备环境指针.
		if(iFontFlag/nCharlen==0)	//设置字体颜色.
		{
			SetTextColor(hDC,RGB(255,0,0));
			strcpy(chFont,"楷体");
		}
		else if(iFontFlag/nCharlen==1)
		{
			SetTextColor(hDC,RGB(0,255,0));
			strcpy(chFont,"宋体");
		}
		else if(iFontFlag/nCharlen==2)
		{
			SetTextColor(hDC,RGB(255,255,0));
			strcpy(chFont,"仿宋体");
		}
		else if(iFontFlag/nCharlen==3)
		{
			SetTextColor(hDC,RGB(0,0,255));
			strcpy(chFont,"黑体");
		}
		else
		{
			iFontFlag=0;
			SetTextColor(hDC,RGB(255,0,0));
		}
		//设置字体.
		hF=CreateFont(			//获得字体句柄.
			40,					//字体高度
			0,					//系统自动调整宽度.
			0,					//文本水平
			0,					//字体倾斜度为0
			400,				//字体粗度.400为正常.
			0,					//字体不倾斜.
			0,					//无下划线.
			0,					//无中划线.
			GB2312_CHARSET,		//字符集
			OUT_DEFAULT_PRECIS,	//默认输出精度.
			CLIP_DEFAULT_PRECIS,//默认裁剪精度
			DEFAULT_QUALITY,	//默认输出质量.
			DEFAULT_PITCH|FF_DONTCARE,//默认间距
			chFont);		//字体名称.
		SelectObject(hDC,hF);	//选入字体.
		GetTextMetrics(hDC,&tm);	//得到字体的信息.
		TextOut(hDC,X,Y,&lpsz_1[iFontFlag%nCharlen],nCharlen-iFontFlag%nCharlen);
					//输出.
		iFontFlag+=2;	//字体标志自增.

		DeleteObject(hF);	//删除字体.
		EndPaint(hWnd,&ps);	//删除设备环境指针.
		return 0;
	case WM_DESTROY:		//结束.
		PostQuitMessage(0);
		KillTimer(hWnd,1);			//删除定时器.
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,1);	//刷新用户区.
		break;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}


BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("5_6",				//窗口类名称.
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
	WndClass.lpszClassName="5_6";			//窗口类名称.
	WndClass.lpszMenuName=NULL;				//无菜单.
	WndClass.style=0;						//缺省窗口风格.
	return RegisterClass(&WndClass);	//返回窗口注册值.
}

