#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "7_10.h"
#include <math.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������
HWND hWndMain;							//����ȫ�ִ��ھ��
HINSTANCE hInst;		//����ʵ�����
RECT rect1={100,100,100,100};			//������νṹ��.��¼��ͼ�ε���Ϣ

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	HACCEL hAccel;
	hInst = hInstance;

	if(!InitWindowsClass(hInstance))		//��ʼ��������
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//��ʼ������
		return FALSE;
	hAccel = LoadAccelerators(hInstance,"Menu");	//���ؼ��ټ���Դ

	while(GetMessage(&Message,0,0,0))
	{
		if(!TranslateAccelerator(hWndMain,hAccel,&Message))//�ػ���ټ���Ϣ
		{
			TranslateMessage(&Message);			//��Ϣѭ��
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,
					UINT wParam,LONG lParam)
{
	HMENU hMenu1,hMenu2;				//����˵����
	HDC hDC;							//�����豸�������
	static BOOL bCircle = FALSE,bRect = FALSE;	//���û���Բ�;��εı�־����
	static BOOL bMove = FALSE;			//�����ƶ���־
	PAINTSTRUCT ps;						//�����ͼ�ṹ�����

	switch(iMessage)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_CIRCLE:				//����Բ�β˵�
			hMenu1 = GetMenu(hWnd);		//�õ��˵����
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_CHECKED);	//����ѡ�б�־
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_UNCHECKED);//ɾ����־
			DeleteMenu(hMenu1,1,MF_BYPOSITION);				//ɾ�������Ρ������˵�
			hMenu2 = CreateMenu();							//��̬�����˵�
			//��Ӳ˵���
			AppendMenu(hMenu2,MF_ENABLED,IDM_DRAWCIRCLE,"����Բ��(&d)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_MOVECIRCLE,"�ƶ�Բ��(&m)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMIN,"�Ŵ�(&i)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_ZOOMOUT,"��С(&o)");
			AppendMenu(hMenu2,MF_ENABLED,IDM_REDRAW,"�ػ�(&r)");
			//����˵���
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,"Բ��(&c)");
			DrawMenuBar(hWndMain);							//ˢ�²˵�
			bCircle = FALSE;								//��Բ��־Ϊ��
			bRect = FALSE;									//����α�־Ϊ��
			bMove = FALSE;									//�ƶ���־Ϊ��
			rect1.left = 100;								//�ָ����εĳ�ʼ״̬
			rect1.right = 100;
			rect1.bottom = 100;
			rect1.top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			break;
		case IDM_RECTANGLE:			//�������β˵�
			hMenu1 = GetMenu(hWnd);		//�õ��˵����
			CheckMenuItem(hMenu1,IDM_CIRCLE,MF_UNCHECKED);	//ɾ��ѡ�б�־
			CheckMenuItem(hMenu1,IDM_RECTANGLE,MF_CHECKED);	//����ѡ�б�־
			DeleteMenu(hMenu1,1,MF_BYPOSITION);				//ɾ����Բ�Ρ������˵�
			hMenu2 = LoadMenu(hInst,"menuRect");			//�õ��˵����
			//����˵�
			InsertMenu(hMenu1,1,MF_POPUP|MF_BYPOSITION,(UINT)hMenu2,"����(&r)");
			DrawMenuBar(hWndMain);							//ˢ�²˵�
			bCircle = FALSE;								//��Բ��־Ϊ��
			bRect = FALSE;									//����α�־Ϊ��
			bMove = FALSE;									//�ƶ���־Ϊ��
			rect1.left = 100;								//�ָ����εĳ�ʼ״̬
			rect1.right = 100;
			rect1.bottom = 100;
			rect1.top = 100;
			InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			break;
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);	//�����رմ�����Ϣ
			break;
		case IDM_DRAWCIRCLE:			//����Բ��
			bCircle = TRUE;									//��Բ��־Ϊ��
			bRect = FALSE;									//����α�־Ϊ��
			bMove = FALSE;									//�ƶ���־Ϊ��
			break;
		case IDM_DRAWRECT:			//���ƾ���
			bCircle = FALSE;								//��Բ��־Ϊ��
			bRect = TRUE;									//����α�־Ϊ��
			bMove = FALSE;									//�ƶ���־Ϊ��
			break;
		case IDM_MOVECIRCLE:			//�ƶ�Բ��
			bMove = TRUE;									//�ƶ���־Ϊ��
			break;
		case IDM_MOVERECT:			//�ƶ�����
			bMove = TRUE;									//�ƶ���־Ϊ��
			break;
		case IDM_ZOOMIN:			//�Ŵ�
			if(bCircle ==TRUE || bRect ==TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1.right-rect1.left);		//���㳤��
				nWidth = abs(rect1.top-rect1.bottom);		//������
				rect1.right = (int)(rect1.left+nLength*1.2);	//�Ŵ�
				rect1.bottom = (int)(rect1.top+nWidth*1.2);
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			break;
		case IDM_ZOOMOUT:			//��С
			if(bCircle ==TRUE || bRect ==TRUE)
			{
				int nLength,nWidth;
				nLength = abs(rect1.right-rect1.left);		//���㳤��
				nWidth = abs(rect1.top-rect1.bottom);		//������
				rect1.right = (int)(rect1.left+nLength/1.2);	//��С
				rect1.bottom = (int)(rect1.top+nWidth/1.2);
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			break;
		case IDM_REDRAW:							//���»�ͼ
			bMove = FALSE;									//�ƶ���־Ϊ��
			rect1.left = 100;								//�ָ����εĳ�ʼ״̬
			rect1.right = 100;
			rect1.top = 100;
			rect1.bottom = 100;
			InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			break;
		}
		break;
	case WM_KEYDOWN:	
		if(bMove ==TRUE)
		{
			if(wParam == VK_LEFT)
			{										//��left��,�����ƶ�
				rect1.left -=10;
				rect1.right -=10;
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			else if(wParam == VK_RIGHT)
			{										//��right��,�����ƶ�
				rect1.left +=10;
				rect1.right +=10;
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			else if(wParam == VK_UP)
			{										//��up��ʱ,�����ƶ�
				rect1.top -=10;
				rect1.bottom -=10;
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			else if(wParam == VK_DOWN)
			{										//��down��,�����ƶ�
				rect1.top +=10;
				rect1.bottom +=10;
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
		}
		else if(bCircle == TRUE || bRect ==TRUE)
		{
			if(wParam == VK_RIGHT)
			{
				rect1.right +=10;					//�����Ҽ�ͷʱ���ο򳤶ȼ�10
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			else if(wParam == VK_DOWN)
			{
				rect1.bottom +=10;					//�����¼�ͷ���ο�߶ȼ�10
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			else if(wParam == VK_UP)
			{
				rect1.bottom -=10;					//�����ϼ�ͷ���ο�߶�-10
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
			else if(wParam == VK_LEFT)
			{
				rect1.right -=10;					//�������ͷ���ο�߶�-10
				InvalidateRect(hWnd,NULL,TRUE);	//����ˢ����Ϣ
			}
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);
		if(bCircle == TRUE)
		{						//����Բ��
			Ellipse(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		if(bRect == TRUE)
		{						//���ƾ���
			Rectangle(hDC,rect1.left,rect1.top,rect1.right,rect1.bottom);
		}
		EndPaint(hWnd,&ps);
		break;
	case WM_DESTROY:		//�����˳�������Ϣ
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
	HMENU hMenu;

	hMenu = LoadMenu(hInstance,"Menu");
	hWnd=CreateWindow("7_10",				//����������
					"�˵���ʾʵ������",		 //����������
					WS_OVERLAPPEDWINDOW,	//������ʽ
					CW_USEDEFAULT,			//�������Ͻ�����
					0,
					CW_USEDEFAULT,			//����ȱʡ�ĸ߶ȺͿ��
					0,
					NULL,					//�޸�����
					hMenu,					//�˵�
					hInstance,				//��ǰӦ��ʵ�����
					NULL);					//ָ�򴫵ݸ����ڵĲ�����ָ��
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
	WndClass.cbClsExtra=0;			//�޴�������չ
	WndClass.cbWndExtra=0;			//�޴���ʵ����չ
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��
	WndClass.hInstance=hInstance;			//��ǰʵ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="7_10";			//����������
	WndClass.lpszMenuName=NULL;				//�޲˵�
	WndClass.style=0;						//ȱʡ���ڷ��
	return RegisterClass(&WndClass);	//���ش���ע��ֵ
}
