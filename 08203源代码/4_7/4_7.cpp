#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

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
	WndClass.lpszClassName="4_7";					//����������.
	WndClass.lpszMenuName=NULL;						//�޴��ڲ˵�.
	WndClass.style=0;								//��������Ϊȱʡ����.

	if(!RegisterClass(&WndClass))			//ע�ᴰ��.
	{
		MessageBeep(0);
		return FALSE;
	}
	
	hWnd=CreateWindow("4_7",				//��������.
					"4_7",					//������.
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

	switch(iMessage)
	{
	case WM_PAINT:							//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&PtStr);		//����豸����ָ��.
		SetMapMode(hDC,MM_ANISOTROPIC);		//����ӳ��ģʽ.
		SetWindowExtEx(hDC,300,300,NULL);	//���ô�������.�߼���λ.
		SetViewportExtEx(hDC,600,600,NULL);	//�����ӿ�����.����λ.
		SetViewportOrgEx(hDC,0,0,NULL);	//�����ӿ�ԭ������Ϊ(0,0).����λ.
		//�����ĸ�Բ��.(�ʵ���ʽ��ͬ)
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);	//ѡ��ջ�ˢ.
		SelectObject(hDC,hBrush);
		hPen = CreatePen(PS_DASH,0,RGB(255,0,0));//����������ʽ�ĺ�ɫ��
		SelectObject(hDC,hPen);					//ѡ���豸����.
		Ellipse(hDC,0,0,70,70);					//��Բ.
		hPen = CreatePen(PS_DASHDOT,0,RGB(0,255,0));//�����㻮����ʽ����ɫ��
		SelectObject(hDC,hPen);
		Ellipse(hDC,25,0,95,70);				//��Բ.
		hPen = CreatePen(PS_DASHDOTDOT,0,RGB(0,0,255));//����˫�㻮����ʽ����ɫ��
		SelectObject(hDC,hPen);
		Ellipse(hDC,0,25,70,95);
		hPen = CreatePen(PS_DOT,0,RGB(0,255,255));//����������ʽ������ɫ��
		SelectObject(hDC,hPen);
		Ellipse(hDC,25,25,95,95);
		//��6��Բ�Ǿ���.(ʵ��ˢ��ʽ��ͬ.)
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);	//ѡ��ڻ�ˢ.
		SelectObject(hDC,hBrush);		//ѡ���豸����.
		RoundRect(hDC,120,0,165,45,10,10);	//��Բ�Ǿ���.
		hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);	//ѡ����һ�ˢ.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,165,0,210,45,10,10);
		hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);	//ѡ��һ�ˢ.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,210,0,255,45,10,10);
		hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);	//ѡ���黭ˢ.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,120,45,165,90,10,10);
		hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//ѡ�����һ�ˢ.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,165,45,210,90,10,10);
		hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);	//ѡ��׻�ˢ.
		SelectObject(hDC,hBrush);
		RoundRect(hDC,210,45,255,90,10,10);
		//��6������.(��ˢ��Ӱ��ʽ��ͬ.)
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		hBrush = CreateHatchBrush(HS_BDIAGONAL,RGB(200,200,200));//����45������������Ӱ��
		SelectObject(hDC,hBrush);		//ѡ���豸����.
		Rectangle(hDC,120,90,165,135);	//������.
		hBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(200,200,200));//����45�Ƚ�����
		SelectObject(hDC,hBrush);
		Rectangle(hDC,165,90,210,135);
		hBrush = CreateHatchBrush(HS_FDIAGONAL,RGB(200,200,200));//����45������������Ӱ��.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,210,90,255,135);
		hBrush = CreateHatchBrush(HS_CROSS,RGB(200,200,200));//������ֱ�ཻ��Ӱ��.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,120,135,165,175);
		hBrush = CreateHatchBrush(HS_HORIZONTAL,RGB(200,200,200));//����ˮƽ��Ӱ��.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,165,135,210,175);
		hBrush = CreateHatchBrush(HS_VERTICAL,RGB(200,200,200));//������ֱ��Ӱ��.
		SelectObject(hDC,hBrush);
		Rectangle(hDC,210,135,255,175);
		//����ͼ��
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		hBrush = CreateSolidBrush(RGB(255,0,0));//������ɫ��ˢ��
		SelectObject(hDC,hBrush);					//ѡ���豸������
		Pie(hDC,10,100,							//����ͼ��
				100,190,
				(int)(55+45*cos(2*Pi/3)),(int)(145+45*sin(2*Pi/3)),
				(int)(55+45*cos(0)),(int)(145+45*sin(0)));
		hBrush = CreateSolidBrush(RGB(0,255,255));//��������ɫ��ˢ��
		SelectObject(hDC,hBrush);					//ѡ���豸������
		Pie(hDC,10,100,
				100,190,
				(int)(55+45*cos(4*Pi/3)),(int)(145+45*sin(4*Pi/3)),
				(int)(55+45*cos(2*Pi/3)),(int)(145+45*sin(2*Pi/3)));
		hBrush = CreateSolidBrush(RGB(255,255,0));//������ɫ��ˢ��
		SelectObject(hDC,hBrush);					//ѡ���豸������
		Pie(hDC,10,100,
				100,190,
				(int)(55+45*cos(2*Pi)),(int)(145+45*sin(2*Pi)),
				(int)(55+45*cos(4*Pi/3)),(int)(145+45*sin(4*Pi/3)));

		EndPaint(hWnd,&PtStr);				//�ͷŻ���ָ�롣
		return 0;
	case WM_DESTROY:	//�رմ���.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

