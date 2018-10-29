#include <windows.h>

LRESULT CALLBACK  WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszCmdParam, int nCmdShow)
     {
     static char szAppName[] = "6_9" ;
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

     hwnd = CreateWindow (szAppName, "Blow-Up Mouse Demo",
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

void InvertBlock (HWND hwnd, POINT ptBeg, POINT ptEnd)
     {
     HDC hdc ;

     hdc = CreateDC ("DISPLAY", NULL, NULL, NULL) ;
     ClientToScreen (hwnd, &ptBeg) ;//转换指定窗口的客户区内的点（PIONT结构）的坐标
     ClientToScreen (hwnd, &ptEnd) ;
     PatBlt (hdc, ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y,
             DSTINVERT) ;
//这个函数在矩形区内用当前的画笔重画背景和前景*/
     DeleteDC (hdc) ;
     }

LRESULT CALLBACK  WndProc(HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
     {
     static BOOL  fCapturing=FALSE, fBlocking=FALSE;
     static POINT ptBeg, ptEnd ;
     HDC          hdc ;
     RECT         rect ;

     switch (message)
          {
          case WM_LBUTTONDOWN:
               if (!fCapturing)
                    {
                    fCapturing = TRUE ;//左键击活俘获
                    SetCapture (hwnd) ;//把所有的鼠标信息输入到被左键击活的窗口，无论鼠标是否在窗口内活动，
					//直到鼠标被再次点下为止
                    SetCursor (LoadCursor (NULL, IDC_CROSS)) ;//载入光标
                    }
               if (!fBlocking)
                    {
                    fBlocking = TRUE ;//左键击活俘获
                    ptBeg.x=LOWORD(lParam);
					ptBeg.y=HIWORD(lParam);
                    }
               return 0 ;

          case WM_MOUSEMOVE:
               if (fBlocking)
                    {
                    ptEnd.x=LOWORD(lParam);
					ptEnd.y=HIWORD(lParam);
                    InvertBlock (hwnd, ptBeg, ptEnd) ;
//                    InvertBlock (hwnd, ptBeg, ptEnd) ;
                    }
               return 0 ;

          case WM_LBUTTONUP:
               if (fBlocking)
                    {
                    fCapturing = fBlocking = FALSE ;
                    ptEnd.x=LOWORD(lParam);
					ptEnd.y=HIWORD(lParam);
                    SetCursor (LoadCursor (NULL, IDC_WAIT)) ;

                    hdc = GetDC (hwnd) ; 
                    GetClientRect (hwnd, &rect) ;
                    StretchBlt (hdc, 0, 0, rect.right, rect.bottom,
                                hdc, ptBeg.x, ptBeg.y,
                                ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y,
                                SRCCOPY) ;//把位图载入指定的矩形客户区，并且拉伸或压缩位图
					//恰好适合矩形区

                    ReleaseDC (hwnd, hdc) ;
                    SetCursor (LoadCursor (NULL, IDC_ARROW)) ;
                    ReleaseCapture () ;//把鼠标从当前窗口中释放出来，您应该不难找出前面与之配套的函数
                    }
               return 0 ;

          case WM_DESTROY:
               PostQuitMessage (0) ;
               return 0 ; 
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
