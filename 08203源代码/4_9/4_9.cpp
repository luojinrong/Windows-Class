       
#include <windows.h>
#define ID_TIMER 1

LRESULT CALLBACK  WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
 
     {
     static char szAppName[] = "Timer1" ;
     HWND        hwnd ;
     MSG         msg ;
     WNDCLASS    wndclass ;

     if (!hPrevInstance) 
          {
          wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
          wndclass.lpfnWndProc   = WndProc ;
          wndclass.cbClsExtra    = 0 ;
          wndclass.cbWndExtra    = 0 ;
          wndclass.hInstance     = hInstance ;
          wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
          wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
          wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
          wndclass.lpszMenuName  = NULL ;
          wndclass.lpszClassName = szAppName ;

          RegisterClass (&wndclass) ;
          }

     hwnd = CreateWindow (szAppName, "Timer1 Demo Program",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

     while (!SetTimer (hwnd, ID_TIMER, 1000, NULL))	 //����һ�������ʱ��ֵ/
          if (IDCANCEL == MessageBox (hwnd,
                          "Too many clocks or timers!", szAppName,
                          MB_ICONEXCLAMATION | MB_RETRYCANCEL)) 
 
//�����У� MB_ICONEXCLAMATION��ʾ�Ի���ͼ��Ϊ��̾�ţ�
//MB_RETRYCANCEL��ʾ�Ի������RETRY��CANCEL������ť

               return FALSE ; 

     ShowWindow (hwnd, nCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
          {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
          }
     return msg.wParam ;
     }

LRESULT CALLBACK  WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
     {
     static int colors = 0 ;
     HBRUSH      hBrush ;
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rc ;

     switch (message)
          {
          case WM_TIMER:
               MessageBeep (-1) ;			//����һ������
               InvalidateRect (hwnd, NULL, FALSE) ;
               return 0 ;

          case WM_PAINT:
               hdc = BeginPaint (hwnd, &ps) ;
               GetClientRect (hwnd, &rc) ;
			   
			   switch (colors)
			   {
			   case 0:
					hBrush = CreateSolidBrush (RGB(255,0,0)) ;//�õ�ĳ����ɫ���߼�ˢ
					colors +=1;
					break;
			   case 1:
					hBrush = CreateSolidBrush (RGB(0,255,0)) ;
					colors +=1;
					break;
			   case 2:
					hBrush = CreateSolidBrush (RGB(0,0,255)) ;
					colors =0;
			   }

               FillRect (hdc, &rc, hBrush) ;//��ָ���ĸ�ʽˢ��������
			   //��������������ߺͶ��������������ұߺ͵ײ�
               EndPaint (hwnd, &ps) ;
               DeleteObject (hBrush) ;
               return 0 ;

          case WM_DESTROY:
               KillTimer (hwnd, ID_TIMER) ;//�ͷ�ID_TIMERָ���ļ�ʱ��
			   PostQuitMessage (0) ;
			   return 0 ;
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
