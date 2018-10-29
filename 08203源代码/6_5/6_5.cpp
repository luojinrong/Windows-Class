#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������.
HWND hWndMain;							//����ȫ�ִ��ھ��.
RECT rect1;				//������νṹ��.��¼��ͼ�ε���Ϣ.

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
	WORD x,y;				//��������λ������.
	static BOOL bCircle=FALSE,bRect=FALSE;	//���û���Բ�;��εı�־����.
	PAINTSTRUCT ps;			//�����ͼ�ṹ�����.

	x = LOWORD(lParam);		//�õ�����λ��.
	y = HIWORD(lParam);

	switch(iMessage)
	{
	case WM_LBUTTONDOWN:	//��������������Ϣ.
		if(wParam&MK_CONTROL)	//ͬʱ����Ctrl��ʱ.
		{
			bCircle = TRUE;			//��Բ.
			bRect = FALSE;
			rect1.left = x;			//Բ�����Ͻ�����Ϊ��ǰ���λ��.
			rect1.top = y;
		}
		else if(wParam&MK_SHIFT)	//ͬʱ����shift��ʱ.
		{
			bRect = TRUE;				//������.
			bCircle = FALSE;
			rect1.left = x;			//���ε����Ͻ�����Ϊ��ǰ���λ��.
			rect1.top = y;
		}
		else
		{
			bRect = FALSE;
			bCircle = FALSE;
		}
		break;
	case WM_LBUTTONUP:			//���ɿ����ʱ.��ͼ��־Ϊfalse.			
		bRect = FALSE;
		bCircle = FALSE;
		break;
	case WM_MOUSEMOVE:			//��������ƶ���Ϣ.
		rect1.right = x;		//ͼ�ε����½�����Ϊ��ǰ���λ��.
		rect1.bottom = y;
		if(bRect == TRUE || bCircle == TRUE)
		{
			InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);
		if(bCircle == TRUE)
		{						//����Բ��.
			Ellipse(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		if(bRect == TRUE)
		{						//���ƾ���.
			Rectangle(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		EndPaint(hWnd,&ps);
		break;
	case WM_DESTROY:		//�����˳�������Ϣ.
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
	hWnd=CreateWindow("6_4",				//����������.
					"�����ʾʵ������",		 //����������.
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,
					CW_USEDEFAULT,			//����ȱʡ�ĸ߶ȺͿ��.
					0,
					NULL,					//�޸�����.
					NULL,					//�޲˵�.
					hInstance,				//��ǰӦ��ʵ�����.
					NULL);					//ָ�򴫵ݸ����ڵĲ�����ָ��.����.
	if(!hWnd)		//����ʧ��.
		return FALSE;
	hWndMain=hWnd;	//��ȫ�ִ��ھ����ֵ.
	ShowWindow(hWnd,nCmdShow);	//��ʾ����.
	UpdateWindow(hWnd);			//ˢ���û���.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;			//�޴�������չ.
	WndClass.cbWndExtra=0;			//�޴���ʵ����չ.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��.
	WndClass.hInstance=hInstance;			//��ǰʵ��.
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������.
	WndClass.lpszClassName="6_4";			//����������.
	WndClass.lpszMenuName=NULL;				//�޲˵�.
	WndClass.style=0;						//ȱʡ���ڷ��.
	return RegisterClass(&WndClass);	//���ش���ע��ֵ.
}

