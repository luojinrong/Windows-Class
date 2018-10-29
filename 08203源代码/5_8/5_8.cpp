#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������.
HFONT CreateFont(HDC hDC,int nCharHeight,int nCharWidth);//�������庯������.
HWND hWndMain;			//���崰�ھ��.

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
	PAINTSTRUCT ps;			//���������ͼ��Ϣ�Ľṹ�����
	char lpsz_1[]="����ǧ��Ŀ����һ��¥";	//����������ַ���.(������ɽ���ƺ��뺣��)
	int nCharlen=strlen(lpsz_1)/2;	//�����ַ������ȱ���.
	int X=0,Y=0,i;
	int nCharHeight;

	switch(iMessage)
	{
	case WM_PAINT:					//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&ps);	//����豸����ָ��.
		SetMapMode(hDC,MM_ANISOTROPIC);		//����ӳ��ģʽ.
		SetWindowExtEx(hDC,640,480,NULL);	//���ô��ڷ�Χ.
		SetViewportExtEx(hDC,640,480,NULL);	//�����ӿڷ�Χ.
		//��������С���α仯��������.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 40-(int)((40.0-15.0)/(nCharlen-1)*i);//�����ַ��ĸ߶�.
			X = i*30;							//�ַ����λ�õ�X����.
			Y = 50-nCharHeight/2;				//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(255-i*15,0,0));//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,15);			//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 15+(int)((40.0-15.0)/(nCharlen-1)*i);
			X = i*30;
			Y = 75-nCharHeight/2;
			SetTextColor(hDC,RGB(105+i*15,0,0));
			hF = CreateFont(hDC,nCharHeight,15);			//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//��������С˫���α仯��������.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = (int)(-1.23*i*i+11.07*i+15.1);//�����ַ��ĸ߶�.
			X = i*30;
			Y = 120-nCharHeight/2;				//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(0,255-i*15,0));//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,15);	//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = (int)(0.9*i*i+15);//�����ַ��ĸ߶�.
			X = i*30;
			Y = 180-nCharHeight/2;				//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(0,0,255-i*20));//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,15);	//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//���λ��Ϊ���Ҳ����ַ���.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30;							//�ַ��ĸ߶�.
			X = i*30;									//�ַ����λ�õ�X����.
			Y = (int)(250-40*sin(2*Pi/(nCharlen-1)*i));	//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(0,255-i*15,255-i*20));	//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,15);			//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//���λ��Ϊ���Ҳ����ַ���.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30;						//�ַ��ĸ߶�.
			X = i*30;								//�ַ����λ�õ�X����
			Y = (int)(360-40*cos(2*Pi/(nCharlen-1)*i));//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(150,50,255-i*20));	//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,15);		//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//���λ��ΪԲ�ε��ַ���.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30;						//�ַ��ĸ߶�.
			X = (int)(420+70*cos(2*Pi/(nCharlen)*i));//�ַ����λ�õ�X����.
			Y = (int)(300+70*sin(2*Pi/(nCharlen)*i));//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(255-i*15,100,0));	//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,15);		//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}
		//���λ��Ϊ��Բ��.
		for(i=0;i<nCharlen;i++)
		{
			nCharHeight = 30-i*2;							//�ַ��ĸ߶�.
			X = (int)(420-80*cos(-Pi/(nCharlen)*i));		//�ַ����λ�õ�X����.
			Y = (int)(120+80*sin(-Pi/(nCharlen)*i)-nCharHeight/2);	//�ַ����λ�õ�Y����.
			SetTextColor(hDC,RGB(255-i*15,100,255-i*15));	//�����ַ�����ɫ.
			hF = CreateFont(hDC,nCharHeight,0);				//��������.
			SelectObject(hDC,hF);
			TextOut(hDC,X,Y,&lpsz_1[2*i],2);		
		}

		DeleteObject(hF);				//ɾ��������.
		EndPaint(hWnd,&ps);				//ɾ���豸�û�ָ��.
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("5_8",				//����������.
					"������ʾʵ������",		 //����������.
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,
					640,					//���ڸ߶ȺͿ��.
					480,
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
	WndClass.lpszClassName="5_8";			//����������.
	WndClass.lpszMenuName=NULL;				//�޲˵�.
	WndClass.style=0;						//ȱʡ���ڷ��.
	return RegisterClass(&WndClass);		//���ش���ע��ֵ.
}

//�������庯��.
HFONT CreateFont(HDC hDC,int nCharHeight,int nCharWidth)
{
	HFONT hFont;
	hFont=CreateFont(				//����������.
		nCharHeight,				//����߶�.
		nCharWidth,					//���.
		0,							//�ı���б��Ϊ0,��ʾˮƽ.
		0,							//������б��Ϊ0.
		400,						//����ֶ�.400Ϊ����.
		0,							//��б����?,
		0,							//���»���.
		0,							//��ɾ����.
		ANSI_CHARSET,				//��ʾ���õ��ַ���ΪANSI_CHARSET.
		OUT_DEFAULT_PRECIS,			//ɾ������Ϊȱʡֵ.
		CLIP_DEFAULT_PRECIS,		//�ü�����Ϊȱʡֵ.
		DEFAULT_QUALITY,			//�������Ϊȱʡֵ.
		DEFAULT_PITCH|FF_DONTCARE,	//�ּ�������ϵ��ʹ��ȱʡֵ.
		"Arial");					//��������.
	if(hFont == NULL) return NULL;
	else return hFont;
}