#include <windows.h>
#include "7_9.h"

long WINAPI WndProc(HWND hWnd,UINT iMessage,
					WPARAM wParam,LPARAM lParam);
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);		//�Ի�������

HWND hDlg;				//����Ի�����
HINSTANCE hInst;		//����Ӧ�ó���ʵ�����

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)	
{
	MSG Message;					//������Ϣ����
	HWND hWnd;						//���崰�ھ��
	WNDCLASS WndClass;				//���崰����
	WndClass.cbClsExtra=0;			//�޴�������չ
	WndClass.cbWndExtra=0;			//�޴���ʵ����չ
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��
	WndClass.hInstance=hInstance;			//��ǰʵ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="DlgInstance";//����������
	WndClass.lpszMenuName="Menu";			//����˵�ΪMenu
	WndClass.style=0;						//ȱʡ���ڷ��

	if(!RegisterClass(&WndClass))			//ע�ᴰ��.
	{
		MessageBeep(0);			//ע��ʧ�ܷ���������.
		return FALSE;
	}

	hWnd=CreateWindow("DlgInstance",		//����������
					"��ģʽ�Ի���",		 	 //����������
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť
					CW_USEDEFAULT,			//�������Ͻ�����
					0,
					CW_USEDEFAULT,			//�����Զ���ĸ߶ȺͿ��
					0,
					NULL,					//�޸�����
					NULL,					//�޲˵�
					hInstance,				//��ǰӦ��ʵ�����
					NULL);					//ָ�򴫵ݸ����ڵĲ�����ָ��

	ShowWindow(hWnd,nCmdShow);				//��ʾ����
	UpdateWindow(hWnd);						//ˢ���û���
	hInst=hInstance;						//��Ӧ�ó��������ݸ�ȫ�ֱ���

	while(GetMessage(&Message,0,0,0))
	{
		if(!IsDialogMessage(hDlg,&Message))		//���ǶԻ�����Ϣ,�����Ի�������
		{
			TranslateMessage(&Message);			//��Ϣѭ��
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}

long WINAPI WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_SHOW:						//���Show�˵�
			hDlg=CreateDialog(hInst,"Show",hWnd,(DLGPROC)DlgProc);	//��ʾ�Ի���
			break;
		case IDM_HIDE:						//���Hide�˵�
			DestroyWindow(hDlg);			//ɾ���Ի���
			break;
		case IDM_EXIT:						//���Exit�˵�
			SendMessage(hWnd,WM_DESTROY,0,0);	//�����˳���Ϣ
			break;
		}
		break;
	case WM_DESTROY:						//�˳�
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}


//�Ի�������
BOOL CALLBACK DlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:			//��ʼ���Ի���
		return 1;
	}
	return 0;
}