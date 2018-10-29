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
	HCURSOR hCursor;		//��������.
	HBRUSH hBrush;
	LPSIZE lpSize;		//���ڳߴ�ṹ.
	static char cLeftBtn[]="LEFT BUTTON";	//���嵥�����ʱ������ַ�.
	static char cRightBtn[]="RIGHT BUTTON";	//���嵥���Ҽ�ʱ������ַ�.
	RECT ClientRect;

	switch(iMessage)
	{
	case WM_MOUSEMOVE:			//��������ƶ���Ϣ.
		x=LOWORD(lParam);		//�������X����.
		y=HIWORD(lParam);		//�������Y����.
		GetClientRect(hWnd,&ClientRect);	//�õ����ڴ�С
		if(y>=0&&y<=ClientRect.bottom)
		{
			if(y>=0&&y<=ClientRect.bottom/5)		//�ڴ�����,�Ǽ�ͷ.
			{
				hCursor=LoadCursor(NULL,IDC_ARROW);
				SetCursor(hCursor);
			}
			else if(y>=ClientRect.bottom/5&&y<=ClientRect.bottom/5*2)	//�ڴ�����Ϊʮ��ͼ��.
			{
				hCursor=LoadCursor(NULL,IDC_CROSS);
				SetCursor(hCursor);
			}
			else if(y>=ClientRect.bottom/5*2&&y<=ClientRect.bottom/5*3)	//�ڴ�����Ϊ�������Ϸ���ļ�ͷ���.
			{
				hCursor=LoadCursor(NULL,IDC_SIZENESW);
				SetCursor(hCursor);
			}
			else if(y>=ClientRect.bottom/5*3&&y<=ClientRect.bottom/5*4)	//�ڴ�����Ϊ�������Ϸ���ļ�ͷ���.
			{
				hCursor=LoadCursor(NULL,IDC_SIZENS);
				SetCursor(hCursor);
			}
			else				//�ڴ�����Ϊ�ȴ����.
			{
				hCursor=LoadCursor(NULL,IDC_WAIT);
				SetCursor(hCursor);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:		//������.
		hDC=GetDC(hWnd);		//�õ��豸����ָ��.
		SetBkColor(hDC,RGB(255,255,0));		//���ñ���ɫ.
		TextOut(hDC,0,0,cLeftBtn,strlen(cLeftBtn));		//���.
		ReleaseDC(hWnd,hDC);	//�ͷ��豸����ָ��.
		break;
	case WM_RBUTTONDOWN:		//�����ҽ�.
		hDC=GetDC(hWnd);		//�õ��豸����ָ��.
		SetBkColor(hDC,RGB(255,255,0));	//���ñ���ɫ.
		TextOut(hDC,0,0,cRightBtn,strlen(cRightBtn));	//���.
		ReleaseDC(hWnd,hDC);	//�ͷ��豸����ָ��.
		break;
	case WM_SIZE:
		hDC=GetDC(hWnd);	//�õ��豸����ָ��.
		SetMapMode(hDC,MM_ANISOTROPIC);	//����ӳ��ģʽ.
		SetViewportExtEx(hDC,LOWORD(lParam),HIWORD(lParam),lpSize);	//�����Կ�����.
		SetWindowExtEx(hDC,100,50,lpSize);	//���ô�������.

		hBrush=CreateSolidBrush(RGB(255,255,255));	//����׻�ˢ.	
		SelectObject(hDC,hBrush);				//ѡ��׻�ˢ.
		Rectangle(hDC,0,0,100,10);				//������
		DeleteObject(hBrush);					//ɾ����ˢ.

		hBrush=CreateSolidBrush(RGB(0,255,0));	//�����̻�ˢ.
		SelectObject(hDC,hBrush);				//ѡ���̻�ˢ.
		Rectangle(hDC,0,10,100,20);				//������.
		DeleteObject(hBrush);					//ɾ����ˢ.

		hBrush=CreateSolidBrush(RGB(0,0,255));	//��������ˢ.
		SelectObject(hDC,hBrush);				//ѡ������ˢ.
		Rectangle(hDC,0,20,100,30);				//������.
		DeleteObject(hBrush);					//ɾ����ˢ.

		hBrush=CreateSolidBrush(RGB(255,255,0));	//����ƻ�ˢ.
		SelectObject(hDC,hBrush);					//ѡ��ƻ�ˢ.
		Rectangle(hDC,0,30,100,40);					//������.
		DeleteObject(hBrush);						//ɾ����ˢ.

		hBrush=CreateSolidBrush(RGB(255,0,0));		//����컭ˢ.
		SelectObject(hDC,hBrush);					//ѡ��컭ˢ.
		Rectangle(hDC,0,40,100,50);					//������.
		DeleteObject(hBrush);						//ɾ����ˢ.

		ReleaseDC(hWnd,hDC);						//ɾ���豸����ָ��.
		break;
	case WM_DESTROY:								//�����˳�������Ϣ.
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
	hWnd=CreateWindow("6_4",						//����������.
					"�����ʾʵ������",				//����������.
					WS_OVERLAPPEDWINDOW,			//������ʽ.�б������������С����ť.
					CW_USEDEFAULT,					//�������Ͻ�����.
					0,
					600,							//����ȱʡ�ĸ߶ȺͿ��.
					400,
					NULL,							//�޸�����.
					NULL,							//�޲˵�.
					hInstance,						//��ǰӦ��ʵ�����.
					NULL);							//ָ�򴫵ݸ����ڵĲ�����ָ��.����.
	if(!hWnd)										//����ʧ��.	
		return FALSE;
	hWndMain=hWnd;									//��ȫ�ִ��ھ����ֵ.
	ShowWindow(hWnd,nCmdShow);						//��ʾ����.
	UpdateWindow(hWnd);								//ˢ���û���.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;							//�޴�������չ.
	WndClass.cbWndExtra=0;							//�޴���ʵ����չ.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��.
	WndClass.hInstance=hInstance;					//��ǰʵ��.
	WndClass.lpfnWndProc=WndProc;					//��Ϣ������.
	WndClass.lpszClassName="6_4";					//����������.
	WndClass.lpszMenuName=NULL;						//�޲˵�.
	WndClass.style=0;								//ȱʡ���ڷ��.
	return RegisterClass(&WndClass);				//���ش���ע��ֵ.
}
