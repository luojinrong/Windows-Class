/*-------------------------------------------------------------
   MAPMODE.C -- What's the Size of Window in differend mapmode?
  ------------------------------------------------------------*/

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK  WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
	{
     static char szAppName[] = "MapMode" ;
     HWND        hwnd ;
     MSG         msg ;
     WNDCLASS    wndclass ;

     if (!hPrevInstance) 
          {
          wndclass.style         = CS_HREDRAW | CS_VREDRAW;
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

     hwnd = CreateWindow (szAppName, "What Size is the Window?",
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

void Show (HWND hwnd, HDC hdc, short xText, short yText, short nMapMode,
           char *szMapMode)
     {
     char szBuffer [60] ;
     RECT rect ;
     SaveDC (hdc) ;//保存保存设备上下文
     SetMapMode (hdc, nMapMode) ;//为设备上下文设置新的图纸单位，并且设置好X-，Y-轴方向
     GetClientRect (hwnd, &rect) ;
     DPtoLP (hdc, (LPPOINT) &rect, 2) ;
     RestoreDC (hdc, -1) ;//重新保存设备上下文
     TextOut (hdc, xText, yText, szBuffer,
     sprintf (szBuffer, "%-20s %7d %7d %7d %7d", szMapMode,
               rect.left, rect.right, rect.top, rect.bottom)) ;
     }  

LRESULT CALLBACK  WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
     {
     static char  szHeading [] =
                    "Mapping Mode            Left   Right     Top  Bottom" ;
     static char  szUndLine [] = 
                    "------------            ----   -----     ---  ------" ;
     static long cxChar, cyChar ; 
     HDC          hdc ;
     PAINTSTRUCT  ps ;
     TEXTMETRIC   tm ;

     switch (message)
          {
          case WM_CREATE:
               hdc = GetDC (hwnd) ;
               SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;

               GetTextMetrics (hdc, &tm) ;
               cxChar = tm.tmAveCharWidth ;
               cyChar = tm.tmHeight + tm.tmExternalLeading ;

               ReleaseDC (hwnd, hdc) ;
               return 0 ;

          case WM_PAINT:
               hdc = BeginPaint (hwnd, &ps) ;
               SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;

               SetMapMode (hdc, MM_ANISOTROPIC) ;
               SetWindowExtEx (hdc, 1, 1,NULL) ;//用指定设置窗口的水平和竖直长度
               SetViewportExtEx (hdc, cxChar, cyChar,NULL) ;
			   TextOut (hdc, 1, 1, szHeading, sizeof szHeading - 1) ;
               TextOut (hdc, 1, 2, szUndLine, sizeof szUndLine - 1) ;
               Show (hwnd, hdc, 1, 3, MM_TEXT,      "TEXT (pixels)") ;
               Show (hwnd, hdc, 1, 4, MM_LOMETRIC,  "LOMETRIC (.1 mm)") ;
               Show (hwnd, hdc, 1, 5, MM_HIMETRIC,  "HIMETRIC (.01 mm)") ;
               Show (hwnd, hdc, 1, 6, MM_LOENGLISH, "LOENGLISH (.01 in)") ;
               Show (hwnd, hdc, 1, 7, MM_HIENGLISH, "HIENGLISH (.001 in)") ;
               Show (hwnd, hdc, 1, 8, MM_TWIPS,     "TWIPS (1/1440 in)") ;
               EndPaint (hwnd, &ps) ;
               return 0 ;

          case WM_DESTROY:
               PostQuitMessage (0) ;
               return 0 ;
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
