#include<windows.h>	//����Ӧ�ó�����������������ͺ����ݽṹ�Ķ���
#include<tchar.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM); //���ں���˵��

//--------------- ���³�ʼ�������� ----------------------
int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
	HWND hwnd ;
	MSG Msg ;
	WNDCLASSEX wndclass ;
	TCHAR lpszClassName[] = L"����";	//��������
	TCHAR lpszTitle[]= L"My_Windows";	//���ڱ�����
	//������Ķ���
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style=0;			//��������Ϊȱʡ����
	wndclass.lpfnWndProc=WndProc;	//���崰�ڴ�����
	wndclass.cbClsExtra=0;		//����������չ
	wndclass.cbWndExtra=0;		//����ʵ������չ
	wndclass.hInstance=hInstance;	//��ǰʵ�����
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	//���ڵ���С��ͼ��Ϊȱʡͼ��
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW) ;
	//���ڲ��ü�ͷ���
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ڱ���Ϊ��ɫ
	wndclass.lpszMenuName=NULL;	//�������޲˵�
	wndclass.lpszClassName=lpszClassName ;
	wndclass.hIconSm = LoadIcon(wndclass.hInstance,MAKEINTRESOURCE(IDI_APPLICATION));

	//��������Ϊ"����"
	//--------------- ���½��д������ע�� -------
	if(!RegisterClassEx( &wndclass))//���ע��ʧ���򷢳�����
	{ 
		MessageBeep(0) ;
		MessageBox(NULL,_T("����ע��ʧ�ܣ�"),_T("����ע��"),NULL);
		return FALSE ;	
	}

	hwnd=CreateWindow(
		lpszClassName,		//��������
		lpszTitle,			//����ʵ���ı�����
		WS_OVERLAPPEDWINDOW,	//���ڵķ��
		CW_USEDEFAULT,
		CW_USEDEFAULT,		//�������Ͻ�����Ϊȱʡֵ
		CW_USEDEFAULT,
		CW_USEDEFAULT,		//���ڵĸߺͿ�Ϊȱʡֵ
		NULL,				//�˴����޸�����
		NULL,				//�˴��������˵�
		hInstance,			//�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
		NULL 				//��ʹ�ø�ֵ
		);
	//--------------- ��ʾ���� ----------------------
	ShowWindow( hwnd, nCmdShow) ;
	//-------------- �����û��� ---------------------
	UpdateWindow(hwnd);
	//----------------- �� Ϣ ѭ �� ---------------------- 
	while( GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage( &Msg) ;
		DispatchMessage( &Msg) ;
	}
	return Msg.wParam;	//��Ϣѭ��������������ֹʱ����Ϣ����ϵͳ
}
LRESULT CALLBACK WndProc(	HWND hwnd,UINT message, WPARAM  wParam,LPARAM  lParam )
{  
	switch(message)
	{ 
	case WM_DESTROY:
		PostQuitMessage(0);
	default:	//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return(0);
}
