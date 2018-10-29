#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.
int nNum = 0,nMaxNum = 20;			//nMaxNum��¼��ҶƬѭ��һ���л�ͼ�Ĵ���.
									//nNum��¼�˵�ǰ������.

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)			//������
{
	MSG Message;			//������Ϣ����.
	HWND hWnd;				//���崰�ھ��.

	WNDCLASS WndClass;		//���崰����.
	WndClass.cbClsExtra=0;		//�޴�������չ.
	WndClass.cbWndExtra=0;		//�޴���ʵ����չ.
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ.
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ڲ��ü�ͷ���.
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��.
	WndClass.hInstance=hInstance;					//��ǰӦ�ó�����.
	WndClass.lpfnWndProc=WndProc;					//���ڴ�����.
	WndClass.lpszClassName="4_8";					//����������.
	WndClass.lpszMenuName=NULL;						//�޴��ڲ˵�.
	WndClass.style=0;								//��������Ϊȱʡ����.

	if(!RegisterClass(&WndClass))			//ע�ᴰ��.
	{
		MessageBeep(0);
		return FALSE;
	}
	
	hWnd=CreateWindow("4_8",				//��������.
					"4_8",					//������.
					WS_OVERLAPPEDWINDOW,	//��������,������С��ť�Ĵ���.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,						
					600,				//���ÿ��Ϊ450���߶�Ϊ600.
					450,
					NULL,					//�޸�����.
					NULL,					//�����˵�.
					hInstance,				//��ǰʵ�����.
					NULL);					//��Ҫ�˲���.
	ShowWindow(hWnd,nCmdShow);			//��ʾ����.
	UpdateWindow(hWnd);					//���²������û���.

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
	int nCentreX,nCentreY;	//����3��ҶƬ��Բ�ĵ�����.
	double fAngle;

	switch(iMessage)
	{
	case WM_PAINT:							//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&PtStr);		//����豸����ָ��.
		SetMapMode(hDC,MM_ANISOTROPIC);		//����ӳ��ģʽ.
		SetWindowExtEx(hDC,400,300,NULL);	//���ô�������.�߼���λ.
		SetViewportExtEx(hDC,600,450,NULL);	//�����ӿ�����.����λ.
		SetViewportOrgEx(hDC,300,200,NULL);	//�����ӿ�ԭ������Ϊ(300,200).����λ.
		//������Բ��
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		Ellipse(hDC,-100,-100,100,100);
		//���Ʒ糵��ҶƬ��
		hBrush = CreateSolidBrush(RGB(255,0,0));		//����ɫ��ҶƬ.
		SelectObject(hDC,hBrush);
		fAngle = 2*Pi/nMaxNum*nNum;
		nCentreX = (int)(50*cos(fAngle));
		nCentreY = (int)(50*sin(fAngle));
		Pie(hDC,nCentreX-50,nCentreY-50,
			nCentreX+50,nCentreY+50,
			(int)(nCentreX+50*cos(fAngle)),(int)(nCentreY+50*sin(fAngle)),
			(int)(nCentreX+50*cos(fAngle+Pi)),(int)(nCentreY+50*sin(fAngle+Pi)));
		hBrush = CreateSolidBrush(RGB(255,255,0));		//������ɫ��ҶƬ.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(50*cos(fAngle+2*Pi/3));
		nCentreY = (int)(50*sin(fAngle+2*Pi/3));
		Pie(hDC,nCentreX-50,nCentreY-50,
			nCentreX+50,nCentreY+50,
			(int)(nCentreX+50*cos(fAngle+2*Pi/3)),(int)(nCentreY+50*sin(fAngle+2*Pi/3)),
			(int)(nCentreX+50*cos(fAngle+Pi+2*Pi/3)),(int)(nCentreY+50*sin(fAngle+Pi+2*Pi/3)));
		hBrush = CreateSolidBrush(RGB(0,255,255));		//����ɫ��ҶƬ.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(50*cos(fAngle+4*Pi/3));
		nCentreY = (int)(50*sin(fAngle+4*Pi/3));
		Pie(hDC,nCentreX-50,nCentreY-50,
			nCentreX+50,nCentreY+50,
			(int)(nCentreX+50*cos(fAngle+4*Pi/3)),(int)(nCentreY+50*sin(fAngle+4*Pi/3)),
			(int)(nCentreX+50*cos(fAngle+Pi+4*Pi/3)),(int)(nCentreY+50*sin(fAngle+Pi+4*Pi/3)));
		
		nNum++;				//��ǰ������1.
		Sleep(100);			//�ȴ�0.1��.
		InvalidateRect(hWnd,NULL,1);	//�ػ洰������.

		EndPaint(hWnd,&PtStr);				//�ͷŻ���ָ�롣
		return 0;
	case WM_DESTROY:	//�رմ���.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

