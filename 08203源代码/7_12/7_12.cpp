/*----------------------------------------------------
    BALL.C--Bouncing Ball Program
  ----------------------------------------------------*/
#include <windows.h>//包括了windows函数和数据类型，结构，常量，宏
#define min(a,b) (((a) < (b)) ? (a) : (b))//宏定义函数，
#define max(a,b) (((a) > (b)) ? (a) : (b))
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
      //Wndproc是窗口过程函数名，LRESULT说明是32位数据类型 CALLBACK说明是反调函数
int WINAPI WinMain (//WinMain在vc中相当于tc 的main函数，
	              //WINAPI声明表示windows希望winmain使用通用的API函数调用约定
	HINSTANCE hInstance,//当前实例句柄
	HINSTANCE hPrevInstance,//前一个实例句柄
        LPSTR lpszCmdParam, //指向字符串的指针，这里指向存放内存运行程序名的缓冲区
	int nCmdShow)	//告诉应用程序如何显示初始化窗口，一般为SW—SHOW—NOMAL
     {
      static char szAppName[] = "Ball" ;//赋值字符串，在定义窗口特征中你会看到他
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
   wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
				//定义窗口图标为IDI_APPLICATION标记的图标
   wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
				//定义窗口光标为IDC_ARROW标记的光标，即箭头
   wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;//指定窗口客户区的背景为白色
   wndclass.lpszMenuName  = NULL ;//这个应用程序没有菜单，所以菜单名为NULL
   wndclass.lpszClassName = szAppName ;//窗口类的名字，一般应和程序名字一样
   RegisterClass (&wndclass) ;//这个函数用来注册窗口类
 }

hwnd = CreateWindow (//该函数创建一个窗口实例
	 szAppName,         // window class nameszAppName, 
	 "Bouncing ball", // window caption
       WS_OVERLAPPEDWINDOW|WS_VSCROLL,  // window style
       CW_USEDEFAULT, //初始化 x位置,用确省值
       CW_USEDEFAULT,    // initial y position
       CW_USEDEFAULT,    // initial x size
       CW_USEDEFAULT,    // initial y size
       NULL,             // parent window handle
       NULL,             // window menu handle
       hInstance,        // program instance handle
	 NULL) ;	   // creation parameters
                       
  if(!SetTimer(hwnd,1,50,NULL))
  {
   MessageBox(hwnd,"Too many clocks or timers!", szAppName,MB_ICONEXCLAMATION|MB_OK);
   return FALSE;
 }

  ShowWindow (hwnd, nCmdShow) ;//显示hwnd标志的窗口, nCmdShow标志显示方式
  UpdateWindow (hwnd) ;//显示窗口，发送WM—PAINT消息

  while (GetMessage (&msg, NULL, 0, 0))//取得消息，除WM-QUIT外都返回TRUE
    {
      TranslateMessage (&msg) ;//对一些键盘消息进行翻译
      DispatchMessage (&msg) ;//要求将消息传送给 在MSG结构中为窗口所指定的消息处理器
   }
     return msg.wParam ;//返回一个16位消息参数
}

LRESULT CALLBACK WndProc ( HWND hwnd, //窗口句柄
			   UINT message, //调用的消息
			   WPARAM wParam,//第一个消息，16位
			   LPARAM lParam)//第二个消息，32位
						   
  {
   static HANDLE hBitmap;
   static short cxClient ,cyClient,xCenter,yCenter,cxTotal,cyTotal,
	           cxRadius,cyRadius,cxMove,cyMove,xPixel,yPixel;
   HBRUSH			hBrush;
   HDC          hdc ,hdcMem;////设备句柄
   short        nScale ;
     
  switch (message)//消息处理函数
   {
    case WM_CREATE:
        hdc = GetDC (hwnd) ;//得到设备上下文，与下面的 ReleaseDC （）配套
	xPixel=GetDeviceCaps(hdc,ASPECTX);/*此函数返回设备信息
					//这里取回划一条线设备用的X—向象素单位
	int GetDeviceCaps(  HDC hdc,     // handle to the device context
  	int nIndex   // index of capability to query);

					*/
	yPixel=GetDeviceCaps(hdc,ASPECTY);
        ReleaseDC (hwnd, hdc) ;//释放由hdc = GetDC (hwnd)得到的设备上下文
        return 0 ;

   case WM_SIZE://受到改变窗口尺寸的命令时，
   	xCenter=(cxClient = LOWORD (lParam))/2 ;
        yCenter=(cyClient = HIWORD (lParam))/2 ;//指定客户区的高度，HIWORD是一个宏，
			   //检查lparam的高字节，返回32位系统中的客户区高度

   	nScale=min(cxClient*xPixel,cyClient*yPixel)/16;
   	cxRadius=nScale/xPixel;
	cyRadius=nScale/yPixel;
   	cxMove=max(1,cxRadius/4);
	cyMove=max(1,cyRadius/4);
	cxTotal=2*(cxRadius+cxMove);
	cyTotal=2*(cyRadius+cyMove);
   	if(hBitmap)
		   DeleteObject(hBitmap);
   	hdc=GetDC(hwnd);
	hdcMem=CreateCompatibleDC(hdc);
	hBitmap=CreateCompatibleBitmap(hdc,cxTotal,cyTotal);
			   /*根据设备上下文设置象素单位；原形：
   	HBITMAP CreateCompatibleBitmap(  HDC hdc,        // handle to device context
  	int nWidth,     // width of bitmap, in pixels
  	int nHeight     // height of bitmap, in pixels);

  			*/
	ReleaseDC(hwnd,hdc);
   	SelectObject(hdcMem,hBitmap);
	Rectangle(hdcMem,-1,-1,cxTotal+1,cyTotal+1);
	hBrush=CreateHatchBrush(HS_DIAGCROSS,0L);
	SelectObject(hdcMem,hBrush);
	SetBkColor(hdcMem,RGB(255,0,0));
	Ellipse(hdcMem,cxMove,cyMove,cxTotal-cxMove,
	cyTotal-cyMove);
	DeleteDC(hdcMem);
	DeleteObject(hBrush);
        return 0 ;

    case WM_TIMER:
	if(!hBitmap)
	  break;

	hdc=GetDC(hwnd);
	hdcMem=CreateCompatibleDC(hdc);//设置设备句柄
	SelectObject(hdcMem,hBitmap);
	BitBlt(hdc,xCenter-cxTotal/2,
		yCenter-cyTotal/2,cxTotal,cyTotal,
		hdcMem,0,0,SRCCOPY); 	  //从源设备句柄向目标设备句柄转化矩形象素块

  	ReleaseDC(hwnd,hdc);
	DeleteDC(hdcMem);
	xCenter+=cxMove;
	yCenter+=cyMove;
	if((xCenter+cxRadius>=cxClient)||(xCenter-cxRadius<=0))
		  cxMove=-cxMove;
	if((yCenter+cyRadius>=cyClient)||(yCenter-cyRadius<=0))
		  cyMove=-cyMove;
	  return 0 ;

  case WM_DESTROY://用户点击了X按钮等消息
	  if(hBitmap)
		  DeleteObject(hBitmap);
		  KillTimer(hwnd,1);
          PostQuitMessage (0) ;//告诉系统退出程序
          return 0 ;                  
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
