#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Pi 3.1415926

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

double dfTheta=0,dfRange=100.0;						//�������ߵĽǶȱ���.
long i=0,j=0;
long lCentreX=0,lCentreY=0,lRadious=(long)(0.2*dfRange);
				//����Բ�������Բ����.
POINT lpSin[100];	//�����������ߵĵ�����.

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
	WndClass.lpszClassName="SIN";					//����������.
	WndClass.lpszMenuName=NULL;						//�޴��ڲ˵�.
	WndClass.style=0;								//��������Ϊȱʡ����.

	if(!RegisterClass(&WndClass))			//ע�ᴰ��.
	{
		MessageBeep(0);
		return FALSE;
	}
	
	hWnd=CreateWindow("SIN",				//��������.
					"4_6",					//������.
					WS_OVERLAPPEDWINDOW,	//��������,������С��ť�Ĵ���.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,						
					CW_USEDEFAULT,			//����ȱʡ�Ŀ�Ⱥ͸߶�.
					0,
					NULL,					//�޸�����.
					NULL,					//�����˵�.
					hInstance,				//��ǰʵ�����.
					NULL);					//��Ҫ�˲���.
	ShowWindow(hWnd,nCmdShow);			//��ʾ����.
	UpdateWindow(hWnd);					//���²������û���.

	for(int j=0;j<100;j++)		//�����������ߵĵ�����.
	{
		lpSin[j].x=(long)(j*2*Pi/100*60);
		lpSin[j].y=(long)(dfRange*sin(j*2*Pi/100));
	}
	
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
		SetWindowOrgEx(hDC,-200,-200,NULL);	//����ԭ������Ϊ(-200,-200).
		
		hPen=CreatePen(PS_DASH,1,RGB(255,0,0));	//���»���.
		SelectObject(hDC,hPen);					//ѡ�뻭��.
		Polyline(hDC,lpSin,100);				//������������.

		if(i<=25) //��һ��1/4����.
		{
			hPen=CreatePen(PS_DASH,1,RGB(255,0,0));//���º��.
			hBrush=CreateHatchBrush(HS_BDIAGONAL,RGB(255,0,0));//���º컭ˢ.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//����뾶.
		}
		else if(i<=50)//�ڶ���1/4����.
		{
			hPen=CreatePen(PS_DASH,1,RGB(0,255,0));//�����̱�.
			hBrush=CreateHatchBrush(HS_DIAGCROSS,RGB(0,255,0));//������ˢ.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//����뾶.
		}
		else if(i<=75)//����������.
		{
			hPen=CreatePen(PS_DASH,1,RGB(0,0,255));//��������
			hBrush=CreateHatchBrush(HS_CROSS,RGB(0,0,255));//������ˢ.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//����뾶.
		}
		else//���ĸ�����.
		{
			hPen=CreatePen(PS_DASH,1,RGB(255,255,0));//���»Ʊ�
			hBrush=CreateHatchBrush(HS_VERTICAL,RGB(255,255,0));//���»�ˢ.
			lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//����뾶.
		}
		SelectObject(hDC,hBrush);	//ѡ�뻭ˢ.
		SelectObject(hDC,hPen);		//ѡ�뻭��.
		lCentreX=lpSin[i].x;		//Բ��x����.
		lCentreY=lpSin[i].y;		//Բ��y����.
		Ellipse(hDC,lCentreX-lRadious,lCentreY-lRadious,
			lCentreX+lRadious,lCentreY+lRadious);	//��Բ.

		i++;
		DeleteObject(hPen);		//ɾ������.
		DeleteObject(hBrush);	//ɾ����ˢ.
		EndPaint(hWnd,&PtStr);	//ɾ���豸����ָ��.
		Sleep(100);				//ͣ0.1��.
		if(i<100) InvalidateRect(hWnd,NULL,1);	//ˢ���û���.
		return 0;
	case WM_DESTROY:	//�رմ���.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
}

