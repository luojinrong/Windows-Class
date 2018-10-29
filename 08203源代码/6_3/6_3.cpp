#include <windows.h>
#include <stdlib.h>
#include <string.h>

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
	PAINTSTRUCT ps;			//定义包含绘图信息的结构体变量
	HPEN hPen;				//定义画笔句柄。
	HBRUSH hBrush;			//定义画刷句柄
	//定义输出的字符串。
	static char cUp[]="You had hitted the UP key";
	static char cCtrl[]="You had hitted the Ctrl key";
	static char cShift[]="You had hitted the SHIFT key";
	static char cCtrl_A[]="You had hitted the CTRL A key";
	static char cShift_B[]="You had hitted the SHIFT B key";
	//定义并初始化按键标志变量。
	static BOOL nUpKeyDown=FALSE, nShiftKeyDown=FALSE,
		 nCtrlKeyDown=FALSE, nCtrlAKeyDown=FALSE, nShiftBKeyDown=FALSE;

	switch(iMessage)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:				//当按上箭头键时，变量置为真。
				nUpKeyDown = TRUE;
				break;
			case VK_SHIFT:			//当按shift键时，变量置为真。
				nShiftKeyDown = TRUE;
				break;
			case VK_CONTROL:		//当按control键时，变量置为真。
				nCtrlKeyDown = TRUE;
				break;
			default:
				break;
			}
		}
		break;
	case WM_KEYUP:
		InvalidateRect(hWnd,NULL,FALSE);	//刷新用户区。
		break;
	case WM_CHAR:
		if(wParam==(65&VK_CONTROL))	
		{
			if(nCtrlKeyDown == TRUE)
			{
				nCtrlAKeyDown = TRUE;
				nCtrlKeyDown = FALSE;
			}
		}
		else if(wParam==98||wParam==66)	//当按下b键时
		{
			if(nShiftKeyDown == TRUE)	//检查shift键是否处于按下状态。
			{
				nShiftBKeyDown = TRUE;	//当SHIFT键按下时，变量置为真。
				nShiftKeyDown = FALSE;	
			}
		}
		break;
	case WM_PAINT:							//处理绘图消息.
		hDC=BeginPaint(hWnd,&ps);
		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//创建 白画刷。
		hPen = (HPEN)GetStockObject(WHITE_PEN);		//创建白画笔。
		SelectObject(hDC,hPen);				//选入白画刷
		SelectObject(hDC,hBrush);			//选入白画笔
		SetTextColor(hDC,RGB(255,0,0));		//设置字体颜色为红色。
		//输出信息。
		if(nUpKeyDown == TRUE) 
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,0,cUp,strlen(cUp));
			nUpKeyDown = FALSE;
		}
		else if(nCtrlAKeyDown == TRUE) 
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,100,cCtrl_A,strlen(cCtrl_A));
			nCtrlAKeyDown = FALSE;
			nCtrlKeyDown = FALSE;
		}
		else if(nCtrlKeyDown == TRUE&&nCtrlAKeyDown == FALSE)
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,60,cCtrl,strlen(cCtrl));
			nCtrlKeyDown = FALSE;
		}
		else if(nShiftBKeyDown == TRUE) 
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,0,cShift_B,strlen(cShift_B));
			nShiftBKeyDown = FALSE;
			nShiftKeyDown = FALSE;
		}
		else if(nShiftBKeyDown == FALSE&&nShiftKeyDown == TRUE)
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,0,cShift,strlen(cShift));
			nShiftKeyDown = FALSE;
		}
		else
		{

		}
		//删除画笔和画刷
		DeleteObject(hPen);
		DeleteObject(hBrush);
		EndPaint(hWnd,&ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("6_3",
					"键盘实例程序",
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					0,
					CW_USEDEFAULT,
					0,
					NULL,
					NULL,
					hInstance,
					NULL);
	if(!hWnd)
		return FALSE;
	hWndMain=hWnd;
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,"END");
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName="6_3";
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	return RegisterClass(&WndClass);
	WndClass.style=0;
}