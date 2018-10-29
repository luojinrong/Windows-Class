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
	static BOOL bCircle=FALSE,bRect=FALSE;	//���û���Բ�;��εı�־����.
	PAINTSTRUCT ps;			//�����ͼ�ṹ�����.

	switch(iMessage)
	{
	case WM_KEYDOWN:	
		if(wParam == VK_CONTROL)		//����Ctrl��ʱ.
		{
			bCircle = TRUE;				//��Բ.
			bRect = FALSE;
			rect1.left = 0;				//��ʼ�����νṹ��.
			rect1.right = 0;
			rect1.top = 0;
			rect1.bottom = 0;
		}
		else if(wParam == VK_SHIFT)		//����shift��ʱ.
		{
			bRect = TRUE;				//������.
			bCircle = FALSE;
			rect1.left = 0;				//��ʼ�����νṹ��.
			rect1.right = 0;
			rect1.top = 0;
			rect1.bottom = 0;
		}
		else if(wParam == VK_RIGHT)
		{
			rect1.right +=10;			//�����Ҽ�ͷʱ���ο򳤶ȼ�10.
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
			}
		}
		else if(wParam == VK_DOWN)
		{
			rect1.bottom +=10;			//�����¼�ͷ���ο�߶ȼ�10.
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
			}
		}
		else if(wParam == VK_PRIOR)
		{								//��pageup��ʱ,�����ƶ�.
			rect1.top -=10;
			rect1.bottom -=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
			}
		}
		else if(wParam == VK_NEXT)
		{								//��pagedown��,�����ƶ�.
			rect1.top +=10;
			rect1.bottom +=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
			}
		}
		else if(wParam == VK_HOME)
		{								//��home��,�����ƶ�.
			rect1.left -=10;
			rect1.right -=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
			}
		}
		else if(wParam == VK_END)
		{								//��end��,�����ƶ�.
			rect1.left +=10;
			rect1.right +=10;
			if(bRect == TRUE || bCircle == TRUE)
			{
				InvalidateRect(hWnd,NULL,TRUE);	//�����ػ���Ϣ.
			}
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

