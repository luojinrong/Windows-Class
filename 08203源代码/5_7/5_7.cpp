#include <windows.h>
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
					UINT iMessage,
					UINT wParam,
					LONG lParam);					//��Ϣ����������.

BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������.
HFONT CreateFont(HDC hDC,int nCharHeight,BOOL bItalic);
HWND hWndMain;			//���崰�ھ��.
int nChar=0;
BOOL bRight=TRUE,bLeft=FALSE,bItalic=FALSE;

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
	TEXTMETRIC tm;			//�������������Ϣ�Ľṹ�����.
	char lpsz_1[]="abcdefghijklmnopqrstuvwxyz";	//����������ַ���.
	int nCharlen=strlen(lpsz_1);	//�����ַ������ȱ���.
	int X=0,Y=0,i;

	switch(iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,300,NULL);	//������ʱ��,ÿ0.1�뷢��WM_TIMER��Ϣ.

		break;
	case WM_PAINT:					//�����ͼ��Ϣ.
		hDC=BeginPaint(hWnd,&ps);	//����豸����ָ��.
		
		//�����1������. 
		hF = CreateFont(hDC,40,0);			//��������.
		SelectObject(hDC,hF);			//ѡ������.
		GetTextMetrics(hDC,&tm);		//�õ�����������Ϣ�Ľṹ��.
		Y=tm.tmExternalLeading+10;			//��������ַ���Y����.
		for(i=0;i<nChar;i++)
		{
			SetTextColor(hDC,RGB(0,0,0));	//�����������ɫΪ��ɫ.
			X=X+tm.tmAveCharWidth*2;		//��������ַ���X����.
			TextOut(hDC,X,Y,&lpsz_1[i],1);	//����ӵ�1������nChar���ַ�.
		}
		
		SetTextColor(hDC,RGB(255,0,0));	//�����������ɫΪ��ɫ.
		X=X+tm.tmAveCharWidth*2;		//��������ַ���X,Y����.
		Y=tm.tmExternalLeading;			//���ֵ�λ�ø�10������λ.
		TextOut(hDC,X,Y,&lpsz_1[nChar],1);	//�����nChar���ַ�.

		Y=tm.tmExternalLeading+10;
		for(i=nChar+1;i<nCharlen;i++)
		{
			SetTextColor(hDC,RGB(0,0,0));	//�����������ɫΪ��ɫ.
			X=X+tm.tmAveCharWidth*2;		//��������ַ���X����.
			TextOut(hDC,X,Y,&lpsz_1[i],1);	//���������ַ�.
		}
		if(nChar == nCharlen)				//�����������һ���ַ�ʱ, 
		{
			bRight = FALSE;					//�ı��ɫ���ƶ��ķ���Ϊ����.
			bLeft = TRUE;
		}
		else if(nChar == 0)					//���������һ����ʱ,
		{
			bRight = TRUE;					//�ı��ɫ���ƶ��ķ���Ϊ����
			bLeft = FALSE;
		}
		if(bRight == TRUE) nChar++;
		else nChar--;
		DeleteObject(hF);				//ɾ��������.

		//�����2������.
		hF = CreateFont(hDC,40,bItalic);		//��������.��СΪ40.
		SelectObject(hDC,hF);			//ѡ������.
		X = tm.tmAveCharWidth*2;		//�������λ��.
		Y = tm.tmHeight*2;
		if(bItalic == TRUE) SetTextColor(hDC,RGB(0,0,0));
		else SetTextColor(hDC,RGB(0,255,255));
		TextOut(hDC,X,Y,lpsz_1,strlen(lpsz_1));	//���.
		if(bItalic == TRUE) bItalic=FALSE;
		else bItalic=TRUE;

		DeleteObject(hF);				//ɾ��������.
		EndPaint(hWnd,&ps);				//ɾ���豸�û�ָ��.
		return 0;
	case WM_TIMER:						//�����ɼ�ʱ����������Ϣ.
		InvalidateRect(hWnd,NULL,1);	//ˢ���û���.
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd,1);				//ɾ����ʱ��
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd=CreateWindow("5_7",				//����������.
					"������ʾʵ������",		 //����������.
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,
					850,					//���ڸ߶ȺͿ��.
					300,
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
	WndClass.lpszClassName="5_7";			//����������.
	WndClass.lpszMenuName=NULL;				//�޲˵�.
	WndClass.style=0;						//ȱʡ���ڷ��.
	return RegisterClass(&WndClass);		//���ش���ע��ֵ.
}

HFONT CreateFont(HDC hDC,int nCharHeight,BOOL bItalic)
{
	HFONT hFont;
	hFont=CreateFont(				//����������.
		nCharHeight,				//����߶�.
		0,							//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ.
		0,							//�ı���б��Ϊ0,��ʾˮƽ.
		0,							//������б��Ϊ0.
		400,						//����ֶ�.400Ϊ����.
		bItalic,					//��б����?,
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