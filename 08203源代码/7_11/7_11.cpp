#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "7_11.h"

LRESULT CALLBACK WndProc(HWND hWnd,	UINT iMessage,
					UINT wParam,LONG lParam);	

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������
HWND hWndMain;										//����ȫ�ִ��ھ��
HINSTANCE hInst;									//����ʵ�����

OPENFILENAME ofn;
CHOOSECOLOR  chc;
CHOOSEFONT   chf;


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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	static char lpstrFileName[] = ""; 
	static COLORREF clref[16]={0x00ff0000};

	switch(iMessage)
	{
	case WM_CREATE:			
		//ע��:�˴�ֻ��ע��һЩ���õ�OPENFILENAME�ṹ�ĳ�Ա
		ofn.lStructSize = sizeof(OPENFILENAME);				//���ݽṹ����
		ofn.hwndOwner = hWnd;								//ӵ�иýṹ�Ĵ��ھ��
		ofn.hInstance = hInst;								//Ӧ�ó���ʵ�����
		ofn.lpstrFilter = "Text Files(*.TXT)\0*.txt\0"\
						"All Files (*.*)\0*.*\0";			//�ļ�������
		ofn.lpstrCustomFilter = NULL;						//�Զ�����ļ�������
		ofn.nMaxCustFilter = 0;
		ofn.nFilterIndex = 1;								//�ļ����������Ĵ�����ֵ
		ofn.lpstrFile = NULL;								//ָ���б���ļ���ָ��
		ofn.nMaxFile = 0;
		ofn.lpstrFileTitle = NULL;							//ָ��ѡ���ļ�����ָ��
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;
		ofn.Flags = 0;										//�Ի����־
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = NULL;
		ofn.lCustData = 0;
		ofn.lpfnHook = NULL;						//���Ӻ���ָ��.ͬ�Ի�����������һ��
		ofn.lpTemplateName = NULL;

		//ѡ����ɫͨ�öԻ���
		chc.lStructSize = sizeof(CHOOSECOLOR);		//�ṹ��С
		chc.hwndOwner = hWnd;						//�����ھ��
		chc.rgbResult = 0;							//�趨Ĭ����ɫ
		chc.lpCustColors = clref;					//ָ���û��Զ�����ɫ�����ָ��
		chc.Flags = 0;								//��־
		chc.lCustData = 0;							
		chc.lpfnHook = NULL;						//���Ӻ���ָ��.ͬ�Ի�����������һ��
		chc.lpTemplateName = NULL;

		//ѡ����ͨ����Ի���
		chf.lStructSize = sizeof(CHOOSEFONT);		//�ṹ��С
		chf.hwndOwner = hWnd;						//�����ھ��
		chf.Flags = CF_BOTH | CF_TTONLY | CF_EFFECTS;//ͨ�öԻ�������

		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_NEW:
			break;
		case IDM_OPEN:
			//����ͨ�öԻ�����ʽ
			ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
			ofn.lpstrTitle = "��";				//ͨ�öԻ������
			GetOpenFileName(&ofn);					//��ʾ�Ի���
			break;
		case IDM_SAVEAS:
			//����ͨ�öԻ�����ʽ.
			ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST
				|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
			ofn.lpstrTitle = "���Ϊ...";				//ͨ�öԻ������
			GetOpenFileName(&ofn);					//��ʾ�Ի���
			break;
		case IDM_FONT:
			ChooseFont(&chf);
			break;
		case IDM_COLOR:
			ChooseColor(&chc);
			break;
		case IDM_ABOUT:
			MessageBox(hWnd,"ͨ�öԻ������ʾ��","����",MB_OK);
			break;
		case IDM_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);
			break;
		}
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
	HMENU hMenu;

	hMenu = LoadMenu(hInstance,"Menu");
	hWnd=CreateWindow("7_11",				//����������.
					"ͨ�öԻ�����ʾʵ������",//����������.
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,
					CW_USEDEFAULT,			//����ȱʡ�ĸ߶ȺͿ��.
					0,
					NULL,					//�޸�����.
					hMenu,					//�˵�.
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

	WndClass.cbClsExtra=0;			//�޴�������չ
	WndClass.cbWndExtra=0;			//�޴���ʵ����չ
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//����ȱʡͼ��
	WndClass.hInstance=hInstance;			//��ǰʵ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="7_11";			//����������
	WndClass.lpszMenuName=NULL;				//�޲˵�
	WndClass.style=0;						//ȱʡ���ڷ��
	return RegisterClass(&WndClass);	//���ش���ע��ֵ
}

