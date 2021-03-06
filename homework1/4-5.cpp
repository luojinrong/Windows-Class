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

void Draw_five_angle_star(HWND hwnd, HDC hDC, double Out_r, int c_x, int c_y, double xie);//绘制五角星
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

//------------窗口消息处理函数----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//定义设备环境句柄.
	HPEN hPen;				//定义画笔句柄
	HBRUSH hbr;             //定义画刷句柄
	PAINTSTRUCT PtStr;		//定义包含绘图信息的结构体变量
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &PtStr);//获取设备环境
		SetMapMode(hDC, MM_ANISOTROPIC);//设置映射模式
		SetWindowOrgEx(hDC, 0, 0, NULL);//设置坐标原点
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		SelectObject(hDC, hPen);
		hbr = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hDC, hbr);
		Rectangle(hDC, 0, 0, 600, 400);//画底
		DeleteObject(hPen);
		DeleteObject(hbr);

		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		SelectObject(hDC, hPen);
		hbr = CreateSolidBrush(RGB(255, 255, 0));
		SelectObject(hDC, hbr);
		Draw_five_angle_star(hwnd, hDC, 40, 70, 70, -18);//画星星
		Draw_five_angle_star(hwnd, hDC, 10, 150, 30, 0);
		Draw_five_angle_star(hwnd, hDC, 10, 170, 55, 18);
		Draw_five_angle_star(hwnd, hDC, 10, 170, 90, -18);
		Draw_five_angle_star(hwnd, hDC, 10, 150, 115, 0);
		DeleteObject(hPen);
		DeleteObject(hbr);
		EndPaint(hwnd, &PtStr);
		break;
	default:	//缺省时采用系统消息缺省处理函数
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

void Draw_five_angle_star(HWND hwnd, HDC hDC, double Out_r, int c_x, int c_y, double xie) {
	double In_r;//内部正五边形外接圆得半径
	POINT lpOuterPoints[5], lpInnerPoints[5];//定义外,内正五边形点结构数组.
	POINT lpTriangle[3];                    //定义三角形点结构数组.
	In_r = Out_r * sin(0.1*Pi) / sin(126.0 / 180 * Pi);//根据外圆半径计算内圆半径
													   //计算内外正五边形的点坐标.
	for (int i = 0; i < 5; i++)
	{
		lpOuterPoints[i].x = (long)((Out_r*cos(i*72.0 / 180 * Pi + xie / 180 * Pi)) + c_x);
		lpOuterPoints[i].y = (long)((Out_r*sin(i*72.0 / 180 * Pi + xie / 180 * Pi)) + c_y);
		lpInnerPoints[i].x = (long)((In_r*cos(i*72.0 / 180 * Pi + (xie + 36.0) / 180 * Pi)) + c_x);
		lpInnerPoints[i].y = (long)((In_r*sin(i*72.0 / 180 * Pi + (xie + 36.0) / 180 * Pi)) + c_y);
	}
	//Polygon(hDC, lpOuterPoints, 5);				//画正五边形.
												//填充正五边形的不同区域.
	for (int i = 0; i<5; i++)
	{
		lpTriangle[0] = lpOuterPoints[i % 5];	//生成图形中的三角形区域的坐标.
		lpTriangle[1] = lpInnerPoints[i % 5];
		lpTriangle[2] = lpOuterPoints[(i + 1) % 5];
		//Polygon(hDC, lpTriangle, 3);	//画三角形区域.
		lpTriangle[2] = lpInnerPoints[(i + 4) % 5];	//生成图形中的三角形区域的坐标.
		Polygon(hDC, lpTriangle, 3);		//画三角形区域.
	}
	Polygon(hDC, lpInnerPoints, 5);	//画中心的五边形.

									//用不同种颜色的画笔来绘制五角星.
	MoveToEx(hDC, lpOuterPoints[0].x, lpOuterPoints[0].y, NULL);
	for (int i = 1; i <= 5; i++)
	{
		//LineTo(hDC, lpOuterPoints[(i + 2) % 5].x, lpOuterPoints[(i + 2) % 5].y);
	}
}