#include <windows.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������

HWND hWndMain;		//���崰�ھ��
HDC hDC;			//�����豸�������
HDC hdcmem;			//�����ڴ���
HBITMAP hBm;		//����λͼ���
BITMAP bm;			//����λͼ�ṹ����
int iY=80;			//λͼ���Ͻǳ�ʼy����
int iWindowWidth,iWindowHeight;		//���ڵĿ�Ⱥ͸߶�
char cUpWarn[]="�����������ƶ���";		//���Ͼ����ַ���
char cDownWarn[]="�����������ƶ���";	//���¾����ַ���


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)			//������
{
	MSG Message;		//������Ϣ����

	hBm=LoadBitmap(hInstance,"forest");		//����λͼ
	GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);	//���λͼ��Ϣ
	iWindowWidth=2*bm.bmWidth;					//�õ����ڵĿ��
	iWindowHeight=2*bm.bmHeight;				//�õ����ڵĸ߶�

	if(!InitWindowsClass(hInstance))		//��ʼ��������
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//��ʼ������
		return FALSE;
	while(GetMessage(&Message,0,0,0))
	{
		TranslateMessage(&Message);			//��Ϣѭ��
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam)			//��Ϣ������
{
	PAINTSTRUCT ps;				//���������ͼ��Ϣ�Ľṹ����

	switch(iMessage)
	{
	case WM_LBUTTONDOWN:			//���������
		iY=iY-10;					//λͼ�߶�-10
		InvalidateRect(hWnd,NULL,1);//ˢ���û���
		break;
	case WM_RBUTTONDOWN:			//�������Ҽ�
		iY=iY+10;					//λͼ�߶�+10;
		InvalidateRect(hWnd,NULL,1);//ˢ���û���
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_UP:					//���ϼ�ͷʱ,λ��-10
			iY=iY-10;
			break;
		case VK_DOWN:				//���¼�ͷʱ,λ��+10
			iY=iY+10;
			break;
		}
		InvalidateRect(hWnd,NULL,1);//ˢ���û���
		break;
	case WM_CREATE:					//��ʼ��������Ϣ
		hDC=GetDC(hWnd);			//�õ��豸����ָ��
		hdcmem=CreateCompatibleDC(hDC);	//�õ��ڴ�ָ��
		ReleaseDC(hWnd,hDC);		//ɾ���豸����ָ��
	case WM_PAINT:					//�����ͼ��Ϣ
		hDC=BeginPaint(hWnd,&ps);	//�õ��豸����ָ��
		if(iY>0&&iY<iWindowHeight/2)		//��λͼ�������ڴ�����ʱ
		{
			SelectObject(hdcmem,hBm);		//ѡ���ڴ���
			BitBlt(hDC,60,iY,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
											//���λͼ
		}
		else if(iY<=0)				//��λͼ���ϱ߽糬���˴���ʱ
		{
			TextOut(hDC,0,0,cUpWarn,sizeof(cUpWarn));//�������
		}
		else						//��λͼ���±߽糬���˴���ʱ
		{
			TextOut(hDC,0,0,cDownWarn,sizeof(cDownWarn));//�������
		}
		EndPaint(hWnd,&ps);			//�������ָ��
		break;
	case WM_DESTROY:				//�رմ�����Ϣ
		DeleteObject(hBm);			//ɾ���ڴ���
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
	hWnd=CreateWindow("BitmapInstance",		//����������
					"λͼ��ʾʵ������",	 	 //����������
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť
					CW_USEDEFAULT,			//�������Ͻ�����
					0,
					iWindowWidth,			//�����Զ���ĸ߶ȺͿ��
					iWindowHeight,
					NULL,					//�޸�����
					NULL,					//�޲˵�
					hInstance,				//��ǰӦ��ʵ�����
					NULL);					//ָ�򴫵ݸ����ڵĲ�����ָ��.����
	if(!hWnd)		//����ʧ��
		return FALSE;
	hWndMain=hWnd;	//��ȫ�ִ��ھ����ֵ
	ShowWindow(hWnd,nCmdShow);	//��ʾ����
	UpdateWindow(hWnd);			//ˢ���û���
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;					//�޴�������չ
	WndClass.cbWndExtra=0;					//�޴���ʵ����չ
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��
	WndClass.hInstance=hInstance;			//��ǰʵ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="BitmapInstance";//����������
	WndClass.lpszMenuName="Menu";			//����˵�ΪMenu
	WndClass.style=0;						//ȱʡ���ڷ��
	return RegisterClass(&WndClass);	//���ش���ע��ֵ
}
