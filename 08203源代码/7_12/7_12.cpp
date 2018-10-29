/*----------------------------------------------------
    BALL.C--Bouncing Ball Program
  ----------------------------------------------------*/
#include <windows.h>//������windows�������������ͣ��ṹ����������
#define min(a,b) (((a) < (b)) ? (a) : (b))//�궨�庯����
#define max(a,b) (((a) > (b)) ? (a) : (b))
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
      //Wndproc�Ǵ��ڹ��̺�������LRESULT˵����32λ�������� CALLBACK˵���Ƿ�������
int WINAPI WinMain (//WinMain��vc���൱��tc ��main������
	              //WINAPI������ʾwindowsϣ��winmainʹ��ͨ�õ�API��������Լ��
	HINSTANCE hInstance,//��ǰʵ�����
	HINSTANCE hPrevInstance,//ǰһ��ʵ�����
        LPSTR lpszCmdParam, //ָ���ַ�����ָ�룬����ָ�����ڴ����г������Ļ�����
	int nCmdShow)	//����Ӧ�ó��������ʾ��ʼ�����ڣ�һ��ΪSW��SHOW��NOMAL
     {
      static char szAppName[] = "Ball" ;//��ֵ�ַ������ڶ��崰����������ῴ����
     HWND        hwnd ;//���ھ��
     MSG         msg ;//��Ϣ�ṹ��
     WNDCLASS    wndclass ;//������

 if (!hPrevInstance)//���崰������
  {
   wndclass.style         = CS_HREDRAW | CS_VREDRAW ;//���崰������Ϊ���������ػ�
   wndclass.lpfnWndProc   = WndProc ;//ָ��ǰ���д��ڣ��Դ���ͬ������Ϣ
   wndclass.cbClsExtra    = 0 ;//����������ṹ�ռ�
   wndclass.cbWndExtra    = 0 ;//�������ⴰ�ڽṹ�ռ�
   wndclass.hInstance     = hInstance ;//����winmain�ĵ�һ������
   wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
				//���崰��ͼ��ΪIDI_APPLICATION��ǵ�ͼ��
   wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
				//���崰�ڹ��ΪIDC_ARROW��ǵĹ�꣬����ͷ
   wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;//ָ�����ڿͻ����ı���Ϊ��ɫ
   wndclass.lpszMenuName  = NULL ;//���Ӧ�ó���û�в˵������Բ˵���ΪNULL
   wndclass.lpszClassName = szAppName ;//����������֣�һ��Ӧ�ͳ�������һ��
   RegisterClass (&wndclass) ;//�����������ע�ᴰ����
 }

hwnd = CreateWindow (//�ú�������һ������ʵ��
	 szAppName,         // window class nameszAppName, 
	 "Bouncing ball", // window caption
       WS_OVERLAPPEDWINDOW|WS_VSCROLL,  // window style
       CW_USEDEFAULT, //��ʼ�� xλ��,��ȷʡֵ
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

  ShowWindow (hwnd, nCmdShow) ;//��ʾhwnd��־�Ĵ���, nCmdShow��־��ʾ��ʽ
  UpdateWindow (hwnd) ;//��ʾ���ڣ�����WM��PAINT��Ϣ

  while (GetMessage (&msg, NULL, 0, 0))//ȡ����Ϣ����WM-QUIT�ⶼ����TRUE
    {
      TranslateMessage (&msg) ;//��һЩ������Ϣ���з���
      DispatchMessage (&msg) ;//Ҫ����Ϣ���͸� ��MSG�ṹ��Ϊ������ָ������Ϣ������
   }
     return msg.wParam ;//����һ��16λ��Ϣ����
}

LRESULT CALLBACK WndProc ( HWND hwnd, //���ھ��
			   UINT message, //���õ���Ϣ
			   WPARAM wParam,//��һ����Ϣ��16λ
			   LPARAM lParam)//�ڶ�����Ϣ��32λ
						   
  {
   static HANDLE hBitmap;
   static short cxClient ,cyClient,xCenter,yCenter,cxTotal,cyTotal,
	           cxRadius,cyRadius,cxMove,cyMove,xPixel,yPixel;
   HBRUSH			hBrush;
   HDC          hdc ,hdcMem;////�豸���
   short        nScale ;
     
  switch (message)//��Ϣ������
   {
    case WM_CREATE:
        hdc = GetDC (hwnd) ;//�õ��豸�����ģ�������� ReleaseDC ��������
	xPixel=GetDeviceCaps(hdc,ASPECTX);/*�˺��������豸��Ϣ
					//����ȡ�ػ�һ�����豸�õ�X�������ص�λ
	int GetDeviceCaps(  HDC hdc,     // handle to the device context
  	int nIndex   // index of capability to query);

					*/
	yPixel=GetDeviceCaps(hdc,ASPECTY);
        ReleaseDC (hwnd, hdc) ;//�ͷ���hdc = GetDC (hwnd)�õ����豸������
        return 0 ;

   case WM_SIZE://�ܵ��ı䴰�ڳߴ������ʱ��
   	xCenter=(cxClient = LOWORD (lParam))/2 ;
        yCenter=(cyClient = HIWORD (lParam))/2 ;//ָ���ͻ����ĸ߶ȣ�HIWORD��һ���꣬
			   //���lparam�ĸ��ֽڣ�����32λϵͳ�еĿͻ����߶�

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
			   /*�����豸�������������ص�λ��ԭ�Σ�
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
	hdcMem=CreateCompatibleDC(hdc);//�����豸���
	SelectObject(hdcMem,hBitmap);
	BitBlt(hdc,xCenter-cxTotal/2,
		yCenter-cyTotal/2,cxTotal,cyTotal,
		hdcMem,0,0,SRCCOPY); 	  //��Դ�豸�����Ŀ���豸���ת���������ؿ�

  	ReleaseDC(hwnd,hdc);
	DeleteDC(hdcMem);
	xCenter+=cxMove;
	yCenter+=cyMove;
	if((xCenter+cxRadius>=cxClient)||(xCenter-cxRadius<=0))
		  cxMove=-cxMove;
	if((yCenter+cyRadius>=cyClient)||(yCenter-cyRadius<=0))
		  cyMove=-cyMove;
	  return 0 ;

  case WM_DESTROY://�û������X��ť����Ϣ
	  if(hBitmap)
		  DeleteObject(hBitmap);
		  KillTimer(hwnd,1);
          PostQuitMessage (0) ;//����ϵͳ�˳�����
          return 0 ;                  
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
