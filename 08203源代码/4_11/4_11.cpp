#include <windows.h>

LRESULT CALLBACK  WndProc (HWND, UINT, WPARAM, LPARAM) ;//Wndproc�Ǵ��ڹ��̺�������LRESULT˵����32λ�������� CALLBACK˵���Ƿ�������

int WINAPI WinMain (
					HINSTANCE hInstance,//��ǰʵ�����
					HINSTANCE hPrevInstance,//ǰһ��ʵ�����
                    LPSTR lpszCmdParam, //ָ���ַ�����ָ�룬����ָ�����ڴ����г������Ļ�����
					int nCmdShow)//����Ӧ�ó��������ʾ��ʼ�����ڣ�һ��ΪSW��SHOW��NOMAL
     {
     static char szAppName[] = "4_11" ;//��ֵ�ַ������ڶ��崰����������ῴ����
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
          wndclass.hIcon         = NULL;
          wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;//���崰�ڹ��ΪIDC_ARROW��ǵĹ�꣬����ͷ
          wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;//ָ�����ڿͻ����ı���Ϊǳ��ɫ
          wndclass.lpszMenuName  = szAppName ;//���Ӧ�ó���Ĳ˵���
          wndclass.lpszClassName = szAppName ;//����������֣�һ��Ӧ�ͳ�������һ��

          RegisterClass (&wndclass) ;//�����������ע�ᴰ����
	 }

     hwnd = CreateWindow (//�ú�������һ������ʵ��
		 szAppName,         // window class name
		    "ROP2 demonstration program",     // window caption
                    WS_OVERLAPPEDWINDOW,     // window style
                    CW_USEDEFAULT,           // initial x position����CW_USEDEFAULT��ʹWindows Ϊ����ѡ���ʵ��Ĵ�С��λ��
                    CW_USEDEFAULT,           // initial y position
                    CW_USEDEFAULT,           // initial x size
                    CW_USEDEFAULT,           // initial y size
                    NULL,                    // parent window handle
                    NULL,                    // window menu handle
                    hInstance,               // program instance handle
		    NULL) ;		     // creation parameters

     ShowWindow (hwnd, nCmdShow) ;//�Ѵ��ڷŵ���ʾ���ϣ�hwnd��־Ҫ��ʾ�Ĵ��ھ��, nCmdShow��־��ʾ��ʽ
     UpdateWindow (hwnd) ;//��ʾ���ڣ�����WM��PAINT��Ϣ

     while (GetMessage (&msg, NULL, 0, 0))//ȡ����Ϣ�����ܵ�WM-QUIT�⣬�κ���Ϣ������TRUE
          {
          TranslateMessage (&msg) ;//��һЩ������Ϣ���з���
          DispatchMessage (&msg) ;//Ҫ��WINDOWS����Ϣ���͸� ��MSG�ṹ��Ϊ������ָ������Ϣ������
          }
     return msg.wParam ;//����һ��16λ��Ϣ����
     }

LRESULT CALLBACK  WndProc (//Wndproc�Ǵ��ڹ��̺�������LRESULT˵����32λ�������� CALLBACK˵���Ƿ�������
						   HWND hwnd, //���ھ��
						   UINT message, //���õ���Ϣ
						   WPARAM wParam,//��һ����Ϣ��16λ
						   LPARAM lParam)//�ڶ�����Ϣ��32λ
     {
	static LOGPEN lpBlack={PS_SOLID,1,1,RGB(0,0,0)},//�����߼�������
		lpWhite={PS_SOLID,1,1,RGB(255,255,255)};
	 static short nDrawingMode=R2_COPYPEN;
     HDC         hdc ;//�豸���
	 HMENU       hMenu;//�˵����
	 HPEN        hPenBlack,hPenWhite,hDefPen;
     PAINTSTRUCT ps ;//��ˢ�ṹ
     RECT	 rect ;//��Ч��
	 short     i;
	
     switch (message)//��Ϣ������
          {   
	     case WM_COMMAND:
		 hMenu=GetMenu(hwnd);//�Ӵ���ȡ�ò˵����
		 CheckMenuItem(hMenu,nDrawingMode,MF_UNCHECKED);//���˵���
		 nDrawingMode=LOWORD(wParam);
		 CheckMenuItem(hMenu,nDrawingMode,MF_CHECKED);
		 InvalidateRect(hwnd,NULL,FALSE);
		 return 0;
          case WM_PAINT://������Ϣ
	        hdc = BeginPaint (hwnd, &ps) ; //�õ��豸�����ģ��������������WM-PAINT��Ϣ������
			hPenBlack=CreatePenIndirect(&lpBlack);//���ú�ɫ��
			hPenWhite=CreatePenIndirect(&lpWhite);//���ð�ɫ��
			SetMapMode(hdc,MM_ANISOTROPIC);//����ͼֽģʽ
            GetClientRect (hwnd, &rect) ;//�õ���Ҫ���ƵĿͻ���
			SetViewportExtEx(hdc,rect.right,rect.bottom,NULL);
			SetWindowExtEx(hdc,10,4,NULL);

			for(i=0;i<10;i+=2)
			{
			SetRect(&rect,i,0,i+2,4);
			FillRect(hdc,&rect,(HBRUSH)GetStockObject(i/2));
			}
			SetROP2(hdc,nDrawingMode);
			hDefPen=(HPEN)SelectObject(hdc,hPenWhite);
			MoveToEx(hdc,1,1,NULL);//�ڵ�ǰ���ǰһ������һ���ߣ�����ǰһ���������
			LineTo(hdc,9,3);
			EndPaint(hwnd,&ps);
			SelectObject(hdc,hDefPen);
			DeleteObject(hPenBlack);
			DeleteObject(hPenWhite);
			return 0 ;

          case WM_DESTROY://�û������X��ť����Ϣ
               PostQuitMessage (0) ;//����ϵͳ�˳�����
               return 0 ;  
                 
          }

     return DefWindowProc (hwnd, message, wParam, lParam) ;//����ϵͳĬ�Ϻ����������û�д������Ϣ
     }
	 

