#include<windows.h>	//包含应用程序中所需的数据类型和数据结构的定义
#include<tchar.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
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

HFONT mycreate(const TCHAR *fontname);//创建字体

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
int pos = 0, scret_pos = 0, size = 10, x = 0, y = 0, flag = 0, r_flag = 0, g_flag = 0, b_flag = 0, max_raw, can_c=0;
//pos 为输出的字符长度，scret_pos是光标位置（字符串第几个字符处），size为字符串最大长度，x,y为当前打印坐标，flag标记是否有输入，rgb_flag表示当前字体颜色，max_raw为当前窗口一行最大存储字符数，can_c标记当前是否为全选状态（复制时用）
bool Ctrl_Down = false, Ctrl_A_Down = false, Ctrl_C_DOWN = false, Ctrl_V_DOWN = false, Ctrl_S_DOWN = false;
char *s=(char*)malloc(sizeof(char)*size), *cv=(char*)malloc(sizeof(char)*size);

//------------窗口消息处理函数----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//定义设备环境句柄.
	HFONT hF;				//定义字体句柄.	
	HPEN hP;
	HBRUSH hB;
	PAINTSTRUCT PtStr;			//定义包含绘图信息的结构体变量
	TEXTMETRIC tm;
	RECT rc;
	SIZE sz;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		if (flag) {
			x = y = 0;
			hDC = BeginPaint(hwnd, &PtStr);
			char c[2];
			hF = mycreate("宋体");
			SelectObject(hDC, hF);
			if (r_flag) {
				SetTextColor(hDC, RGB(255, 0, 0));
			}
			else if (g_flag) {
				SetTextColor(hDC, RGB(0, 255, 0));
			}
			else if (b_flag) {
				SetTextColor(hDC, RGB(0, 0, 255));
			}
			else {
				SetTextColor(hDC, RGB(0, 0, 0));
			}
			if (Ctrl_A_Down) {
				Ctrl_A_Down = false;
				SetBkColor(hDC, RGB(0, 0, 255));
			}
			for (int i = 0; s[i]; i++) {
				c[0] = s[i];
				c[1] = 0;
				TextOut(hDC, x, y, c, sizeof(c));
				GetTextMetrics(hDC, &tm);
				CreateCaret(hwnd, NULL, 1, tm.tmHeight);
				//ShowCaret(hwnd);
				GetTextExtentPoint32(hDC, c, sizeof(c), &sz);
				x = x + sz.cx - tm.tmPitchAndFamily;
				GetClientRect(hwnd, &rc);
				max_raw = (rc.right / (sz.cx - tm.tmPitchAndFamily))-1;
				if (x + sz.cx > rc.right) {
					x = 0;
					y = y + tm.tmHeight + tm.tmExternalLeading;
				}
				if (i == scret_pos-1) {
					SetCaretPos(x, y);
				}
			}
			if (scret_pos == 0) {
				SetCaretPos(0, 0);
			}
			if (GetBkColor(hDC) == RGB(0, 0, 255)) {
				can_c = 1;
			}
			else {
				can_c = 0;
			}
			EndPaint(hwnd, &PtStr);
		}
		break;
	case WM_CHAR:
		if ((wParam >= 'a'&&wParam <= 'z') || (wParam >= 'A'&&wParam <= 'Z')) {
			cv[0] = 0;
			flag = 1;
			if (pos + 5 > size) {
				size *= 2;
				s = (char*)realloc(s, sizeof(char)*size);
				cv = (char*)realloc(cv, sizeof(char)*size);
			}
			if (pos == scret_pos) {
				s[pos] = wParam;
				s[++pos] = 0;
				scret_pos++;
			}
			else {
				char a = wParam;
				for (int i = scret_pos; i < pos+1; i++) {
					s[i] ^= a;
					a ^= s[i];
					s[i] ^= a;
				}
				s[++pos] = a;
				scret_pos++;
			}
			InvalidateRect(hwnd, NULL, false);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_CONTROL) {
			Ctrl_Down = true;
			//MessageBox(NULL, _T("Ctrl"), _T("按键消息"), NULL);
		}
		else if (wParam == 'A'&&Ctrl_Down) {
			Ctrl_A_Down = true;
			Ctrl_Down = false;
			//MessageBox(NULL, _T("Ctrl-A"), _T("按键消息"), NULL);
			InvalidateRect(hwnd, NULL, false);
			
		}
		else if (wParam == 'C'&&Ctrl_Down&& can_c) {
			Ctrl_C_DOWN = true;
			Ctrl_Down = false;
			strcpy(cv, s);
		}
		else if (wParam == 'V'&&Ctrl_Down) {
			Ctrl_V_DOWN = true;
			Ctrl_Down = false;
			if (strlen(s) * 2 > size) {
				size *= 2;
				s = (char*)realloc(s, sizeof(char)*size);
				cv = (char*)realloc(cv, sizeof(char)*size);
			}
			if (scret_pos == pos) {
				strcat(s, cv);
				scret_pos += strlen(cv) ;
			}
			else {
				char *tmp = (char*)malloc(sizeof(char)*size);
				for (int i = scret_pos;; i++) {
					if (s[i] == 0) {
						tmp[i - scret_pos] = 0;
						break;
					}
					else {
						tmp[i - scret_pos] = s[i];
					}
				}
				s[scret_pos] = 0;
				strcat(s, cv);
				strcat(s, tmp);
				scret_pos += strlen(cv);
			}
			pos = strlen(s);
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'S'&&Ctrl_Down) {
			Ctrl_S_DOWN = true;
			Ctrl_Down = false;
			FILE *fp;
			fp = fopen("./save.txt", "w");
			fprintf(fp, s);
			fclose(fp);
			MessageBox(NULL, "已保存", "这是一个消息", NULL);
		}
		else if (wParam == 'R') {
			//MessageBox(NULL, _T("Red"), _T("测试消息"), NULL);
			r_flag ^= 1;
			g_flag = 0;
			b_flag = 0;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'G') {
			//MessageBox(NULL, _T("Green"), _T("测试消息"), NULL);
			g_flag ^= 1;
			r_flag = 0;
			b_flag = 0;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'B') {
			//MessageBox(NULL, _T("Blue"), _T("测试消息"), NULL);
			b_flag ^= 1;
			r_flag = 0;
			g_flag = 0;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_LEFT && scret_pos) {
			scret_pos--;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_RIGHT && scret_pos < pos) {
			scret_pos++;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_UP && scret_pos > max_raw) {
			scret_pos -= max_raw;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_DOWN && pos - scret_pos > max_raw) {
			scret_pos += max_raw;
			InvalidateRect(hwnd, NULL, false);
		}
		else {

		}
		break;
	case WM_KEYUP:
		if (wParam == VK_CONTROL) {
			Ctrl_Down = false;
		}
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