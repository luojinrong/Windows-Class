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
     ClientToScreen (hwnd, &ptBeg) ;//ת��ָ�����ڵĿͻ����ڵĵ㣨PIONT�ṹ��������
     ClientToScreen (hwnd, &ptEnd) ;
     PatBlt (hdc, ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x, ptEnd.y - ptBeg.y,
             DSTINVERT) ;
//��������ھ��������õ�ǰ�Ļ����ػ�������ǰ��*/
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
                    fCapturing = TRUE ;//����������
                    SetCapture (hwnd) ;//�����е������Ϣ���뵽���������Ĵ��ڣ���������Ƿ��ڴ����ڻ��
					//ֱ����걻�ٴε���Ϊֹ
                    SetCursor (LoadCursor (NULL, IDC_CROSS)) ;//������
                    }
               if (!fBlocking)
                    {
                    fBlocking = TRUE ;//����������
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
                                SRCCOPY) ;//��λͼ����ָ���ľ��οͻ��������������ѹ��λͼ
					//ǡ���ʺϾ�����

                    ReleaseDC (hwnd, hdc) ;
                    SetCursor (LoadCursor (NULL, IDC_ARROW)) ;
                    ReleaseCapture () ;//�����ӵ�ǰ�������ͷų�������Ӧ�ò����ҳ�ǰ����֮���׵ĺ���
                    }
               return 0 ;

          case WM_DESTROY:
               PostQuitMessage (0) ;
               return 0 ; 
          }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
     }
