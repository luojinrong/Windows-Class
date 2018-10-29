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
	HBRUSH hBrush;			//���廭ˢ���
	HPEN hPen;				//���廭�ʾ��
	PAINTSTRUCT PtStr;		//���������ͼ��Ϣ�Ľṹ�����
	double dfRadious0=100.0,dfRadious1;		//�����ⲿ���ڲ�����������Բ�뾶.
	POINT lpOuterPoints[5],lpInnerPoints[5];//������,��������ε�ṹ����.
	POINT lpTriangle[3];                    //���������ε�ṹ����.
	dfRadious1=dfRadious0*sin(0.1*Pi)/sin(126.0/180*Pi);//������Բ�뾶������԰�뾶.
	//��������������εĵ�����.
	for(int i=0;i<5;i++)
	{
		lpOuterPoints[i].x=(long)(dfRadious0*cos(i*72.0/180*Pi));
		lpOuterPoints[i].y=(long)(dfRadious0*sin(i*72.0/180*Pi));
		lpInnerPoints[i].x=(long)(dfRadious1*cos(i*72.0/180*Pi+36.0/180*Pi));
		lpInnerPoints[i].y=(long)(dfRadious1*sin(i*72.0/180*Pi+36.0/180*Pi));
	}

	switch(iMessage)
	{
	case WM_PAINT:							//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&PtStr);		//�õ��豸�������
		SetMapMode(hDC,MM_ANISOTROPIC);		//����ӳ��ģʽ.
		SetWindowOrgEx(hDC,-100,-100,NULL);	//��������ԭ��.

		hPen=CreatePen(PS_SOLID,1,RGB(255,0,0));	//���º�ɫ����.
		SelectObject(hDC,hPen);						//������ѡ��.
		Polygon(hDC,lpOuterPoints,5);				//���������.
			//���������εĲ�ͬ����.
		for(i=0;i<5;i++)
		{
			lpTriangle[0]=lpOuterPoints[i%5];	//����ͼ���е����������������.
			lpTriangle[1]=lpInnerPoints[i%5];
			lpTriangle[2]=lpOuterPoints[(i+1)%5];
					//�����»�ˢ.
			hBrush=CreateSolidBrush(RGB(i*10,i*20,i*30));
			SelectObject(hDC,hBrush);	//ѡ���»�ˢ.
			Polygon(hDC,lpTriangle,3);	//������������.
			lpTriangle[2]=lpInnerPoints[(i+4)%5];	//����ͼ���е����������������.
			hBrush=CreateSolidBrush(RGB(i*40,i*30,i*20));//���»�ˢ.
			SelectObject(hDC,hBrush);		//ѡ�뻭ˢ.
			Polygon(hDC,lpTriangle,3);		//������������.
		}
		hBrush=CreateSolidBrush(RGB(255,255,255));//���°׻�ˢ.
		SelectObject(hDC,hBrush);		//ѡ�뻭ˢ.
		Polygon(hDC,lpInnerPoints,5);	//�����ĵ������.
			
			//�ò�ͬ����ɫ�Ļ��������������.
		MoveToEx(hDC,lpOuterPoints[0].x,lpOuterPoints[0].y,NULL);
		for(i=1;i<=5;i++)
		{
			hPen=CreatePen(PS_SOLID,1,RGB(0,i*51,0));
			SelectObject(hDC,hPen);
			LineTo(hDC,lpOuterPoints[(i+2)%5].x,lpOuterPoints[(i+2)%5].y);
		}
		hPen=(HPEN)(GetStockObject(PS_NULL));

		DeleteObject(hPen);		//ɾ������.
		DeleteObject(hBrush);	//ɾ����ˢ.
		EndPaint(hWnd,&PtStr);	//������ͼ.
		return 0;
	case WM_DESTROY:		//����رմ�����Ϣ.
		PostQuitMessage(0);		//��Ӧ�ó�����WM_QUIT��Ϣ.
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)	//��ʼ��
{
	HWND hWnd;					//���崰�ھ��.
	hWnd=CreateWindow("Polygon",				//��������.
					"�����",					//����ʵ������.
					WS_OVERLAPPEDWINDOW,		//���ڷ��.���߿�,������,ϵͳ�˵���������С��ť.
					CW_USEDEFAULT,				//�������Ͻ�����.
					0,							//�������Ͻ�����.
					CW_USEDEFAULT,				//���ڿ��
					0,							//���ڸ߶�	
					NULL,						//�޸�����.
					NULL,						//�����˵�.
					hInstance,					//�����˴��ڵ�Ӧ�ó���ĵ�ǰ���.
					NULL);						//ָ��һ�����ݸ����ڵĲ���ֵ��ָ��.
												//��ʹ�ø�ֵ.
	if(!hWnd)			//������ڴ���ʧ��,����false.
		return FALSE;
	hWndMain=hWnd;		//�����ھ�����ݸ�ȫ�ֱ���.
	ShowWindow(hWnd,nCmdShow);		//��ʾ����.
	UpdateWindow(hWnd);				//���²������û���.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)	//��ʼ��������.
{
	WNDCLASS WndClass;					//���崰����.
	WndClass.cbClsExtra=0;				//����������չ.
	WndClass.cbWndExtra=0;				//����ʵ������չ.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//���ڱ���Ϊ��ɫ.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ڲ��ü�ͷ���.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//���ڵ���С��ͼ��Ϊȱʡͼ��.
	WndClass.hInstance=hInstance;					//��ǰʵ�����.
	WndClass.lpfnWndProc=WndProc;					//���ڴ�����.
	WndClass.lpszClassName="Polygon";				//��������.
	WndClass.lpszMenuName=NULL;						//�޲˵�
	WndClass.style=0;								//��������Ϊȱʡ����.
	return RegisterClass(&WndClass);				//����ע�ᴰ�ڵ�ֵ.
}