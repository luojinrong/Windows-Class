#include<windows.h>	//包含应用程序中所需的数据类型和数据结构的定义
#include<tchar.h>
#include<math.h>
const double Pi = 3.1415926535;
HWND hwnd;
MSG Msg;
WNDCLASSEX wndclass;
TCHAR lpszClassName[] = "窗口";	//窗口类名
TCHAR lpszTitle[] = "My_Windows";	//窗口标题名

ATOM MyRegisterClass(HINSTANCE hInstance);//注册窗口函数

BOOL Create(HINSTANCE hInstance, int nCmdShow);//创建窗口实例函数

int Run(); //窗口消息循环函数

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //窗口函数说明

HFONT CreateFont(HDC hDC, int nCharHeight, int nCharWidth);

													  //--------------- 以下初始化窗口类 ----------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	//MyRegisterClass(hInstance);
	Create(hInstance, nCmdShow);

	Run();
}



//------------注册窗口函数--------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance) {

	//窗口类的定义
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = 0;			//窗口类型为缺省类型
	wndclass.lpfnWndProc = WndProc;	//定义窗口处理函数
	wndclass.cbClsExtra = 0;		//窗口类无扩展
	wndclass.cbWndExtra = 0;		//窗口实例无扩展
	wndclass.hInstance = hInstance;	//当前实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//窗口的最小化图标为缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//窗口采用箭头光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//窗口背景为白色
	wndclass.lpszMenuName = NULL;	//窗口中无菜单
	wndclass.lpszClassName = lpszClassName;
	wndclass.hIconSm = LoadIcon(wndclass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//窗口类名为"窗口"
	//--------------- 以下进行窗口类的注册 -------
	if (!RegisterClassEx(&wndclass))//如果注册失败则发出警告
	{
		MessageBeep(0);
		MessageBox(NULL, _T("窗口注册失败！"), _T("窗口注册"), NULL);
		return FALSE;
	}
	return TRUE;

}

//------------创建窗口实例函数----------------------------------
BOOL Create(HINSTANCE hInstance, int nCmdShow) {
	//-------------- 窗口注册 -----------------------
	if (!MyRegisterClass(hInstance)) {
		return FALSE;
	}
	hwnd = CreateWindow(
		lpszClassName,		//窗口类名
		lpszTitle,			//窗口实例的标题名
		WS_OVERLAPPEDWINDOW,	//窗口的风格
		CW_USEDEFAULT,
		CW_USEDEFAULT,		//窗口左上角坐标为缺省值
		CW_USEDEFAULT,
		CW_USEDEFAULT,		//窗口的高和宽为缺省值
		NULL,				//此窗口无父窗口
		NULL,				//此窗口无主菜单
		hInstance,			//创建此窗口的应用程序的当前句柄
		NULL 				//不使用该值
	);
	//--------------- 显示窗口 ----------------------
	ShowWindow(hwnd, nCmdShow);
	//-------------- 绘制用户区 ---------------------
	UpdateWindow(hwnd);
}

//------------窗口消息循环函数----------------------------------
int Run() {
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
int x = 325, y = 25, v = 0, flag = 0;
//------------窗口消息处理函数----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//定义设备环境句柄.
	HFONT hF;				//定义字体句柄.	
	PAINTSTRUCT PtStr;			//定义包含绘图信息的结构体变量
	char lpsz_1[] = "浙江工商大学欢迎您！";	//定义输出的字符串
	int nCharlen = strlen(lpsz_1) / 2;	//定义字符串长度变量.
	int X = 0, Y = 0, i;
	int nCharHeight;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &PtStr);
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 40 - (int)((40.0 - 15.0) / (nCharlen - 1)*i);//计算字符的高度.
			X = i * 30;							//字符输出位置的X坐标.
			Y = 50 - nCharHeight / 2;				//字符输出位置的Y坐标.
			SetTextColor(hDC, RGB(255 - i * 15, 0, 0));//设置字符的颜色.
			hF = CreateFont(hDC, nCharHeight, 15);			//定义字体.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 15 + (int)((40.0 - 15.0) / (nCharlen - 1)*i);
			X = i * 30;
			Y = 75 - nCharHeight / 2;
			SetTextColor(hDC, RGB(105 + i * 15, 0, 0));
			hF = CreateFont(hDC, nCharHeight, 15);			//定义字体.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		//输出字体大小双线形变化的艺术字.
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = (int)(-1.23*i*i + 11.07*i + 15.1);//计算字符的高度.
			X = i * 30;
			Y = 120 - nCharHeight / 2;				//字符输出位置的Y坐标.
			SetTextColor(hDC, RGB(0, 255 - i * 15, 0));//设置字符的颜色.
			hF = CreateFont(hDC, nCharHeight, 15);	//定义字体.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = (int)(0.9*i*i + 15);//计算字符的高度.
			X = i * 30;
			Y = 180 - nCharHeight / 2;				//字符输出位置的Y坐标.
			SetTextColor(hDC, RGB(0, 0, 255 - i * 20));//设置字符的颜色.
			hF = CreateFont(hDC, nCharHeight, 15);	//定义字体.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		//输出位置为圆形的字符串.
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 30;						//字符的高度.
			X = (int)(420 + 70 * cos(2 * Pi / (nCharlen)*i));//字符输出位置的X坐标.
			Y = (int)(300 + 70 * sin(2 * Pi / (nCharlen)*i));//字符输出位置的Y坐标.
			SetTextColor(hDC, RGB(255 - i * 15, 100, 0));	//设置字符的颜色.
			hF = CreateFont(hDC, nCharHeight, 15);		//定义字体.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		//输出位置为半圆形.
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 30 - i * 2;							//字符的高度.
			X = (int)(420 - 80 * cos(-Pi / (nCharlen)*i));		//字符输出位置的X坐标.
			Y = (int)(120 + 80 * sin(-Pi / (nCharlen)*i) - nCharHeight / 2);	//字符输出位置的Y坐标.
			SetTextColor(hDC, RGB(255 - i * 15, 100, 255 - i * 15));	//设置字符的颜色.
			hF = CreateFont(hDC, nCharHeight, 0);				//定义字体.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}

		DeleteObject(hF);				//删除字体句柄.
		EndPaint(hwnd, &PtStr);
		break;
	default:	//缺省时采用系统消息缺省处理函数
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

HFONT CreateFont(HDC hDC, int nCharHeight, int nCharWidth){
	HFONT hFont;
	hFont = CreateFont(				//定义字体句柄.
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
		DEFAULT_PITCH | FF_DONTCARE,	//字间距和字体系列使用缺省值.
		"Arial");					//字体名称.
	if (hFont == NULL) return NULL;
	else return hFont;
}