#include <windows.h>

LRESULT CALLBACK  WndProc (HWND, UINT, WPARAM, LPARAM) ;//Wndproc是窗口过程函数名，LRESULT说明是32位数据类型 CALLBACK说明是反调函数

int WINAPI WinMain (
					HINSTANCE hInstance,//当前实例句柄
					HINSTANCE hPrevInstance,//前一个实例句柄
                    LPSTR lpszCmdParam, //指向字符串的指针，这里指向存放内存运行程序名的缓冲区
					int nCmdShow)//告诉应用程序如何显示初始化窗口，一般为SW—SHOW—NOMAL
     {
     static char szAppName[] = "4_11" ;//赋值字符串，在定义窗口特征中你会看到他
     HWND        hwnd ;//窗口句柄
     MSG         msg ;//消息结构类
     WNDCLASS    wndclass ;//窗口类

     if (!hPrevInstance)//定义窗口特征
          {
          wndclass.style         = CS_HREDRAW | CS_VREDRAW ;//定义窗口类型为整个窗口重画
          wndclass.lpfnWndProc   = WndProc ;//指向当前运行窗口，以处理不同窗口信息
          wndclass.cbClsExtra    = 0 ;//不留额外类结构空间
          wndclass.cbWndExtra    = 0 ;//不留额外窗口结构空间
          wndclass.hInstance     = hInstance ;//设置winmain的第一个参数
          wndclass.hIcon         = NULL;
          wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;//定义窗口光标为IDC_ARROW标记的光标，即箭头
          wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;//指定窗口客户区的背景为浅灰色
          wndclass.lpszMenuName  = szAppName ;//这个应用程序的菜单名
          wndclass.lpszClassName = szAppName ;//窗口类的名字，一般应和程序名字一样

          RegisterClass (&wndclass) ;//这个函数用来注册窗口类
	 }

     hwnd = CreateWindow (//该函数创建一个窗口实例
		 szAppName,         // window class name
		    "ROP2 demonstration program",     // window caption
                    WS_OVERLAPPEDWINDOW,     // window style
                    CW_USEDEFAULT,           // initial x position常量CW_USEDEFAULT可使Windows 为窗口选择适当的大小和位置
                    CW_USEDEFAULT,           // initial y position
                    CW_USEDEFAULT,           // initial x size
                    CW_USEDEFAULT,           // initial y size
                    NULL,                    // parent window handle
                    NULL,                    // window menu handle
                    hInstance,               // program instance handle
		    NULL) ;		     // creation parameters

     ShowWindow (hwnd, nCmdShow) ;//把窗口放到显示器上，hwnd标志要显示的窗口句柄, nCmdShow标志显示方式
     UpdateWindow (hwnd) ;//显示窗口，发送WM—PAINT消息

     while (GetMessage (&msg, NULL, 0, 0))//取得消息，除受到WM-QUIT外，任何消息都返回TRUE
          {
          TranslateMessage (&msg) ;//对一些键盘消息进行翻译
          DispatchMessage (&msg) ;//要求WINDOWS将消息传送给 在MSG结构中为窗口所指定的消息处理器
          }
     return msg.wParam ;//返回一个16位消息参数
     }

LRESULT CALLBACK  WndProc (//Wndproc是窗口过程函数名，LRESULT说明是32位数据类型 CALLBACK说明是反调函数
						   HWND hwnd, //窗口句柄
						   UINT message, //调用的消息
						   WPARAM wParam,//第一个消息，16位
						   LPARAM lParam)//第二个消息，32位
     {
	static LOGPEN lpBlack={PS_SOLID,1,1,RGB(0,0,0)},//定义逻辑笔类型
		lpWhite={PS_SOLID,1,1,RGB(255,255,255)};
	 static short nDrawingMode=R2_COPYPEN;
     HDC         hdc ;//设备句柄
	 HMENU       hMenu;//菜单句柄
	 HPEN        hPenBlack,hPenWhite,hDefPen;
     PAINTSTRUCT ps ;//画刷结构
     RECT	 rect ;//无效区
	 short     i;
	
     switch (message)//消息处理函数
          {   
	     case WM_COMMAND:
		 hMenu=GetMenu(hwnd);//从窗口取得菜单句柄
		 CheckMenuItem(hMenu,nDrawingMode,MF_UNCHECKED);//检查菜单项
		 nDrawingMode=LOWORD(wParam);
		 CheckMenuItem(hMenu,nDrawingMode,MF_CHECKED);
		 InvalidateRect(hwnd,NULL,FALSE);
		 return 0;
          case WM_PAINT://绘制消息
	        hdc = BeginPaint (hwnd, &ps) ; //得到设备上下文，这个函数仅用于WM-PAINT消息处理中
			hPenBlack=CreatePenIndirect(&lpBlack);//设置黑色笔
			hPenWhite=CreatePenIndirect(&lpWhite);//设置白色笔
			SetMapMode(hdc,MM_ANISOTROPIC);//设置图纸模式
            GetClientRect (hwnd, &rect) ;//得到需要绘制的客户区
			SetViewportExtEx(hdc,rect.right,rect.bottom,NULL);
			SetWindowExtEx(hdc,10,4,NULL);

			for(i=0;i<10;i+=2)
			{
			SetRect(&rect,i,0,i+2,4);
			FillRect(hdc,&rect,(HBRUSH)GetStockObject(i/2));
			}
			SetROP2(hdc,nDrawingMode);
			hDefPen=(HPEN)SelectObject(hdc,hPenWhite);
			MoveToEx(hdc,1,1,NULL);//在当前点和前一个点连一根线，返回前一个点的坐标
			LineTo(hdc,9,3);
			EndPaint(hwnd,&ps);
			SelectObject(hdc,hDefPen);
			DeleteObject(hPenBlack);
			DeleteObject(hPenWhite);
			return 0 ;

          case WM_DESTROY://用户电击了X按钮等消息
               PostQuitMessage (0) ;//告诉系统退出程序
               return 0 ;  
                 
          }

     return DefWindowProc (hwnd, message, wParam, lParam) ;//调用系统默认函数处理程序没有处理的消息
     }
	 

