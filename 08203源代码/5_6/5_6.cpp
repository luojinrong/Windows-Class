#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������.
HWND hWndMain;		//���崰�ھ��.
int iFontFlag=0;	//���������־.

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
	HFONT hF;				//����������.
	PAINTSTRUCT ps;		//���������ͼ��Ϣ�Ľṹ�����
	TEXTMETRIC tm;		//�������������Ϣ�Ľṹ�����.
	char lpsz_1[]="����ǧ��Ŀ  ����һ��¥";		//��������ַ���.
	char chFont[7];		//�������������ַ���.
	int X=0,Y=0,nCharlen=strlen(lpsz_1);

	switch(iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,200,NULL);		//�趨��ʱ��.ÿ0.2�뷢��WM_TIMER��Ϣ.
		break;
	case WM_PAINT:							//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&ps);			//��ȡ�豸����ָ��.
		if(iFontFlag/nCharlen==0)	//����������ɫ.
		{
			SetTextColor(hDC,RGB(255,0,0));
			strcpy(chFont,"����");
		}
		else if(iFontFlag/nCharlen==1)
		{
			SetTextColor(hDC,RGB(0,255,0));
			strcpy(chFont,"����");
		}
		else if(iFontFlag/nCharlen==2)
		{
			SetTextColor(hDC,RGB(255,255,0));
			strcpy(chFont,"������");
		}
		else if(iFontFlag/nCharlen==3)
		{
			SetTextColor(hDC,RGB(0,0,255));
			strcpy(chFont,"����");
		}
		else
		{
			iFontFlag=0;
			SetTextColor(hDC,RGB(255,0,0));
		}
		//��������.
		hF=CreateFont(			//���������.
			40,					//����߶�
			0,					//ϵͳ�Զ��������.
			0,					//�ı�ˮƽ
			0,					//������б��Ϊ0
			400,				//����ֶ�.400Ϊ����.
			0,					//���岻��б.
			0,					//���»���.
			0,					//���л���.
			GB2312_CHARSET,		//�ַ���
			OUT_DEFAULT_PRECIS,	//Ĭ���������.
			CLIP_DEFAULT_PRECIS,//Ĭ�ϲü�����
			DEFAULT_QUALITY,	//Ĭ���������.
			DEFAULT_PITCH|FF_DONTCARE,//Ĭ�ϼ��
			chFont);		//��������.
		SelectObject(hDC,hF);	//ѡ������.
		GetTextMetrics(hDC,&tm);	//�õ��������Ϣ.
		TextOut(hDC,X,Y,&lpsz_1[iFontFlag%nCharlen],nCharlen-iFontFlag%nCharlen);
					//���.
		iFontFlag+=2;	//�����־����.

		DeleteObject(hF);	//ɾ������.
		EndPaint(hWnd,&ps);	//ɾ���豸����ָ��.
		return 0;
	case WM_DESTROY:		//����.
		PostQuitMessage(0);
		KillTimer(hWnd,1);			//ɾ����ʱ��.
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,1);	//ˢ���û���.
		break;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}


BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("5_6",				//����������.
					"������ʾʵ������",		 //����������.
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
	WndClass.lpszClassName="5_6";			//����������.
	WndClass.lpszMenuName=NULL;				//�޲˵�.
	WndClass.style=0;						//ȱʡ���ڷ��.
	return RegisterClass(&WndClass);	//���ش���ע��ֵ.
}

