#include<windows.h>	//包含应用程序中所需的数据类型和数据结构的定义
#include<tchar.h>
HWND hwnd;
MSG Msg;
WNDCLASSEX wndclass;
TCHAR lpszClassName[] = "窗口";	//窗口类名
TCHAR lpszTitle[] = "My_Windows";	//窗口标题名

ATOM MyRegisterClass(HINSTANCE hInstance);//注册窗口函数

BOOL Create(HINSTANCE hInstance, int nCmdShow);//创建窗口实例函数

int Run(); //窗口消息循环函数

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //窗口函数说明

HFONT mycreate(const TCHAR *fontname);//创建字体

void OnLbuttonDown(HWND hwnd);

char s1[] = "School of Computer & Information Engineering(SCIE)";
char s2[] = "SCIE was originally the Information Management Department established in 1985.";
char s3[] = "It was renamed as Computer and Information Engineering Department in 1996";

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
int x = 0, y = 0;
//------------窗口消息处理函数----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//定义设备环境句柄.
	HPEN hPen;				//定义画笔句柄
	PAINTSTRUCT PtStr;		//定义包含绘图信息的结构体变量
	TEXTMETRIC tm;
	SIZE size;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		
		hDC = BeginPaint(hwnd, &PtStr);
		HFONT hf;
		hf = mycreate("宋体");
		SelectObject(hDC, hf);
		GetTextMetrics(hDC, &tm);
		TextOut(hDC, x, y, s1, sizeof(s1));
		Sleep(1000);

		GetTextMetrics(hDC, &tm);
		hf = mycreate("Trebuchet MS");
		SelectObject(hDC, hf);
		y = y + tm.tmHeight + tm.tmExternalLeading;
		x = x + 2 * tm.tmAveCharWidth;
		TextOut(hDC, x, y, s2, sizeof(s2));
		GetTextExtentPoint32(hDC, s2, sizeof(s2), &size);
		x = x + size.cx;
		Sleep(1000);

		TextOut(hDC, x, y, s3, sizeof(s3));
		DeleteObject(hf);

		x = y = 0;
		EndPaint(hwnd, &PtStr);
		break;
	case WM_LBUTTONDOWN:
		//OnLbuttonDown(hwnd);
		break;
	default:	//缺省时采用系统消息缺省处理函数
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

HFONT mycreate(const TCHAR *fontname) {
	return CreateFont(
		0,
		0,
		0,
		0,
		400,
		0,
		0,
		0,
		GB2312_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontname
	);
}
int flag = 0, x0 = 0, y0 = 0;
void OnLbuttonDown(HWND hwnd) {
	HDC hDC;
	HFONT hf;
	TEXTMETRIC tm;
	SIZE size;
	int x, y;
	hDC = GetDC(hwnd);
	if (flag == 0) {
		flag++;
		GetTextMetrics(hDC, &tm);
		hf = mycreate("Trebuchet MS");
		SelectObject(hDC, hf);
		y = y0 + tm.tmHeight + tm.tmExternalLeading;
		x = x0 + 2 * tm.tmAveCharWidth;
		TextOut(hDC, x, y, s2, sizeof(s2));
		GetTextExtentPoint32(hDC, s2, sizeof(s2), &size);
		x0 = x + size.cx;
		y0 = y;
		DeleteObject(hf);
	}
	else if (flag == 1) {
		flag++;
		hf = mycreate("Trebuchet MS");
		SelectObject(hDC, hf);
		TextOut(hDC, x0, y0, s3, sizeof(s3));
		DeleteObject(hf);
	}
	ReleaseDC(hwnd, hDC);
}