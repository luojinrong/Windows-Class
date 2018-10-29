#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������.
HWND hWndMain;

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)			//������
{
	MSG Message;
	if(!InitWindowsClass(hInstance))		//��ʼ��������.
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//��ʼ������.
		return FALSE;
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);			//��Ϣѭ��.
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam)			//��Ϣ������.
{
	HDC hDC;				//�����豸�������.
	PAINTSTRUCT ps;			//���������ͼ��Ϣ�Ľṹ�����
	HPEN hPen;				//���廭�ʾ����
	HBRUSH hBrush;			//���廭ˢ���
	//����������ַ�����
	static char cUp[]="You had hitted the UP key";
	static char cCtrl[]="You had hitted the Ctrl key";
	static char cShift[]="You had hitted the SHIFT key";
	static char cCtrl_A[]="You had hitted the CTRL A key";
	static char cShift_B[]="You had hitted the SHIFT B key";
	//���岢��ʼ��������־������
	static BOOL nUpKeyDown=FALSE, nShiftKeyDown=FALSE,
		 nCtrlKeyDown=FALSE, nCtrlAKeyDown=FALSE, nShiftBKeyDown=FALSE;

	switch(iMessage)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:				//�����ϼ�ͷ��ʱ��������Ϊ�档
				nUpKeyDown = TRUE;
				break;
			case VK_SHIFT:			//����shift��ʱ��������Ϊ�档
				nShiftKeyDown = TRUE;
				break;
			case VK_CONTROL:		//����control��ʱ��������Ϊ�档
				nCtrlKeyDown = TRUE;
				break;
			default:
				break;
			}
		}
		break;
	case WM_KEYUP:
		InvalidateRect(hWnd,NULL,FALSE);	//ˢ���û�����
		break;
	case WM_CHAR:
		if(wParam==(65&VK_CONTROL))	
		{
			if(nCtrlKeyDown == TRUE)
			{
				nCtrlAKeyDown = TRUE;
				nCtrlKeyDown = FALSE;
			}
		}
		else if(wParam==98||wParam==66)	//������b��ʱ
		{
			if(nShiftKeyDown == TRUE)	//���shift���Ƿ��ڰ���״̬��
			{
				nShiftBKeyDown = TRUE;	//��SHIFT������ʱ��������Ϊ�档
				nShiftKeyDown = FALSE;	
			}
		}
		break;
	case WM_PAINT:							//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&ps);
		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���� �׻�ˢ��
		hPen = (HPEN)GetStockObject(WHITE_PEN);		//�����׻��ʡ�
		SelectObject(hDC,hPen);				//ѡ��׻�ˢ
		SelectObject(hDC,hBrush);			//ѡ��׻���
		SetTextColor(hDC,RGB(255,0,0));		//����������ɫΪ��ɫ��
		//�����Ϣ��
		if(nUpKeyDown == TRUE) 
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,0,cUp,strlen(cUp));
			nUpKeyDown = FALSE;
		}
		else if(nCtrlAKeyDown == TRUE) 
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,100,cCtrl_A,strlen(cCtrl_A));
			nCtrlAKeyDown = FALSE;
			nCtrlKeyDown = FALSE;
		}
		else if(nCtrlKeyDown == TRUE&&nCtrlAKeyDown == FALSE)
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,60,cCtrl,strlen(cCtrl));
			nCtrlKeyDown = FALSE;
		}
		else if(nShiftBKeyDown == TRUE) 
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,0,cShift_B,strlen(cShift_B));
			nShiftBKeyDown = FALSE;
			nShiftKeyDown = FALSE;
		}
		else if(nShiftBKeyDown == FALSE&&nShiftKeyDown == TRUE)
		{
			Rectangle(hDC,0,0,300,200);
			TextOut(hDC,0,0,cShift,strlen(cShift));
			nShiftKeyDown = FALSE;
		}
		else
		{

		}
		//ɾ�����ʺͻ�ˢ
		DeleteObject(hPen);
		DeleteObject(hBrush);
		EndPaint(hWnd,&ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("6_3",
					"����ʵ������",
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					0,
					CW_USEDEFAULT,
					0,
					NULL,
					NULL,
					hInstance,
					NULL);
	if(!hWnd)
		return FALSE;
	hWndMain=hWnd;
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,"END");
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName="6_3";
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	return RegisterClass(&WndClass);
	WndClass.style=0;
}