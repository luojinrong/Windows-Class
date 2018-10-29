#include <windows.h>
#define MAXPOINTS 1000

LRESULT CALLBACK  WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
     {
     static char szAppName[] = "MMsg1" ;
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

     hwnd = CreateWindow (szAppName, "Connect-the-Points Mouse Demo",
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         NULL, NULL, hInstance, NULL) ;

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
     static POINTS points[MAXPOINTS] ;
     static short nCount ;
     HDC          hdc ;
     PAINTSTRUCT  ps ;
     short        i, j ;

     switch (message)
          {
          case WM_LBUTTONDOWN://单击鼠标左键
               nCount = 0 ;
               InvalidateRect (hwnd, NULL, TRUE) ;//整个客户区重画，产生wparam消息
               return 0 ;

          case WM_MOUSEMOVE://鼠标移动
               if (wParam & MK_LBUTTON && nCount < 1000)
                    {
                    points [nCount++] = MAKEPOINTS (lParam) ;//此宏返回POINTS类，这里包含有鼠标的X-，Y-坐标信息
                    hdc = GetDC (hwnd) ;
                    SetPixel (hdc, LOWORD (lParam), HIWORD (lParam), 0L) ;
                    ReleaseDC (hwnd, hdc) ;
                    }
               return 0 ;

          case WM_LBUTTONUP:
               InvalidateRect (hwnd, NULL, FALSE) ;
               return 0 ;

          case WM_PAINT:
               hdc = BeginPaint (hwnd, &ps) ;

               for (i = 0 ; i < nCount - 1 ; i++)
                    for (j = i ; j < nCount ; j++)
                         {
                         MoveToEx (hdc, points[i].x, points[i].y,NULL) ;//移动当前的位置，并且返回前一个位置的值
                         LineTo (hdc, points[j].x, points[j].y) ;//在两点之间画线
                         }

               EndPaint (hwnd, &ps) ;
               return 0 ;

          case WM_DESTROY:
               PostQuitMessage (0) ;
               return 0 ;
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
