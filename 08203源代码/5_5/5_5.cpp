#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������.
int CALLBACK pEnumFontFamProc(
  ENUMLOGFONT FAR *lpelf,  // pointer to logical-font data
  NEWTEXTMETRIC FAR *lpntm,  // pointer to physical-font data
  int FontType,            // type of font
  LPARAM lParam            // pointer to application-defined data
);
 
HWND hWndMain;			//���崰�ھ��.
int iFontSign=0;		//���������־,��ʾ���ú�������.

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

long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)			//��Ϣ������.
{
	HDC hDC;				//�����豸�������.
	HFONT hF;				//����������.	
	PAINTSTRUCT ps;			//���������ͼ��Ϣ�Ľṹ�����
	TEXTMETRIC tm;			//�������������Ϣ�Ľṹ�����.
	static char lpsz_1[]="ֻ�и��������ջ�  ";	//����������ַ���.
	char chFont[20];				//��������������ַ���.
	int X=0,Y=0,i;
	static int nCharlen=strlen(lpsz_1);	//�����ַ������ȱ���.

	switch(iMessage)
	{
	case WM_PAINT:							//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&ps);		//����豸����ָ��.
		for(i=0;i<nCharlen;i+=2)		//����ĳ���������ɫ����ַ���.
		{
			SetTextColor(hDC,RGB((long)(255.0/nCharlen*i),//����������ɫ.
								0,
								0));
			if(iFontSign%5==0) strcpy(chFont,"����_GB2312");	//���ð���������Ϣ���ַ���.
			else if(iFontSign%5==1) strcpy(chFont,"����");	//iFont%��ʾ��5Ϊ����ѭ���ı�����.
			else if(iFontSign%5==2) strcpy(chFont,"����");
			else if(iFontSign%5==3) strcpy(chFont,"����");
			else strcpy(chFont,"��Բ");
			hF=CreateFont(				//����������.
				(long)(8+32.0*i/nCharlen),	//����߶�.
				0,							//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ.
				0,							//�ı���б��Ϊ0,��ʾˮƽ.
				0,							//������б��Ϊ0.
				400,						//����ֶ�.400Ϊ����.
				0,							//��б����,
				0,							//���»���.
				0,							//��ɾ����.
				GB2312_CHARSET,				//��ʾ���õ��ַ���ΪGB2312_CHARSET
				OUT_DEFAULT_PRECIS,			//ɾ������Ϊȱʡֵ.
				CLIP_DEFAULT_PRECIS,		//�ü�����Ϊȱʡֵ.
				DEFAULT_QUALITY,			//�������Ϊȱʡֵ.
				DEFAULT_PITCH|FF_DONTCARE,	//�ּ�������ϵ��ʹ��ȱʡֵ.
				chFont);					//��������.
			SelectObject(hDC,hF);			//ѡ������.
			GetTextMetrics(hDC,&tm);		//�õ�����������Ϣ�Ľṹ��.
			X=X+tm.tmAveCharWidth*2;		//��������ַ���X����.
			Y=iFontSign%5*40+tm.tmExternalLeading;	//��������ַ���Y����.
			TextOut(hDC,X,Y,&lpsz_1[i],2);	//�����i���ַ�.����������Ч��.
			Sleep(400);						//��ͣ0.4��.
			DeleteObject(hF);		//ɾ��������.
		}
		iFontSign++;				//�����־����
		InvalidateRect(hWnd,NULL,1);//ˢ���û���.
		EndPaint(hWnd,&ps);			//ɾ���豸�û�ָ��.
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
	hWnd=CreateWindow("5_5",				//����������.
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
	WndClass.lpszClassName="5_5";			//����������.
	WndClass.lpszMenuName=NULL;				//�޲˵�.
	WndClass.style=0;						//ȱʡ���ڷ��.
	return RegisterClass(&WndClass);	//���ش���ע��ֵ.
}