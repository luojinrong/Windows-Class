  
//   HELLO60.C -- Displays "Hello,VC++ 6.0!" in client area

#include <windows.h>//包括了windows函数和数据类型，结构，常量，宏

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM) ;//Wndproc是窗口过程函数名

int WINAPI WinMain(		//windows希望winmain使用通用的API函数调用约定
	HINSTANCE hInstance,	//当前实例句柄
	HINSTANCE hPrevInstance,//前一个实例句柄
        LPSTR lpszCmdParam,	//指向字符串的指针，这里指向存放内存运行程序名的缓冲区
	int nCmdShow)		//应用程序开始执行时窗口的显示方式，常用SW_SHOWNORMAL
{
 static char szAppName[] = "Hello60" ;	//窗口类的名字，经常为程序名
 HWND        hwnd ;			//窗口句柄
 MSG         msg ;			//消息结构类
 WNDCLASS    wndclass ;			//窗口类

 if(!hPrevInstance)				
    {
     wndclass.style = CS_HREDRAW | CS_VREDRAW ;//定义窗口类型为整个窗口重画
     wndclass.lpfnWndProc= WndProc ;		//窗口处理函数
     wndclass.cbClsExtra = 0 ;			//不留额外类结构空间(窗口类无扩展)
     wndclass.cbWndExtra = 0 ;			//不留额外窗口结构空间(窗口实例无扩展)
     wndclass.hInstance = hInstance ;		//设置winmain的第一个参数
     wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);//IDI_APPLICATION为窗口最小化确省图标
     wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;//定义窗口采用IDC_ARROW(箭头)光标
     wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;//窗口客户区的背景为浅灰色
     wndclass.lpszMenuName  = NULL ;	//应用程序窗口中没有菜单，所以菜单名为NULL
     wndclass.lpszClassName = szAppName ;//窗口类的名字，一般应和程序名字一样
     RegisterClass (&wndclass) ;//这个函数用来注册窗口类
    }

     hwnd = CreateWindow (				//该函数创建一个窗口实例
			szAppName,			// window class name
			"The Hello Program",		// 窗口实例标题名
                    	WS_OVERLAPPEDWINDOW,		// window style
                    	CW_USEDEFAULT,CW_USEDEFAULT,	// 窗口左上角坐标 
                    	CW_USEDEFAULT,CW_USEDEFAULT,	// 窗口的高和宽
                    	NULL,				// parent window handle
                    	NULL,				// window menu handle
                    	hInstance,			// program instance handle of current window
			NULL);				// creation parameters

     ShowWindow (hwnd, nCmdShow) ;			//nCmdShow标志显示方式
     UpdateWindow (hwnd) ;				//绘制用户区，发送WM_PAINT消息

     while (GetMessage (&msg, NULL, 0, 0))//取得消息，除受到WM_QUIT外，任何消息都返回TRUE
          {
          TranslateMessage (&msg) ;		//对一些键盘消息进行翻译
          DispatchMessage (&msg) ;		//将消息传送给在MSG结构中为窗口所指定的消息处理器
          }
     return msg.wParam ;				//程序终止时告知系统
 }

LRESULT CALLBACK WndProc( HWND hwnd,	//接收消息的窗口句柄
			  UINT message, //调用的消息号
			  WPARAM wParam,//消息参数
			  LPARAM lParam)//消息参数
{
     HDC         hdc ;		//设备句柄
     PAINTSTRUCT ps ;		//画刷结构
     RECT	 rect ;		//无效矩形区
     static LOGFONT lf;			
     HFONT holdFont,hnewFont;	

     switch (message)		//消息处理函数
      {   
       case WM_CREATE:		//窗口创建，返回0
        return 0;

		case WM_PAINT:										//绘制消息
			lf.lfHeight=-64;	
			lf.lfWeight=500;	
			lf.lfPitchAndFamily=DEFAULT_PITCH & FF_DONTCARE;
			lf.lfCharSet=GB2312_CHARSET;						//选择字符集				
			strcpy(lf.lfFaceName,"黑体");					//字符串赋值，设置字体
			hnewFont=CreateFontIndirect(&lf);					//创建一种新的逻辑字体
			hdc = BeginPaint (hwnd, &ps);					//得到设备环境句柄        	GetClientRect (hwnd, &rect);						//得到需要绘制的客户区
			GetClientRect (hwnd, &rect) ;			//得到需要绘制的客户区
			holdFont=(HFONT)SelectObject(hdc,hnewFont);		//选择新的字体格式，并且保存老的画笔
			SetTextColor(hdc,RGB(255,0,0));					//设置文本颜色
			SetBkColor(hdc,RGB(255,255,0));					//设置背景颜色

			DrawText(hdc,									//输出文本
				 "VC中显示字体与背景",						//输出的字符串
	 			 -1,										//自动计算输出字符的个数
				&rect,									//输出文本区区域
				DT_SINGLELINE|DT_CENTER|DT_VCENTER);			//字体输出在矩形客户区的中央
	 		SelectObject(hdc,holdFont);						//保存原来的字体格式

			DeleteObject(hnewFont);							//删除新的字体格式
			EndPaint (hwnd, &ps) ;						//结束绘制，与BeiginPaint函数配套
        	return 0 ;

       case WM_DESTROY:		//退出消息
        PostQuitMessage (0) ;	//告诉系统退出程序
        return 0 ;  
}
  return DefWindowProc(hwnd,message,wParam,lParam) ;//调用默认函数处理没有处理的消息
}