#include<windows.h>	//����Ӧ�ó�����������������ͺ����ݽṹ�Ķ���
#include<tchar.h>
#include<math.h>
const double Pi = 3.1415926535;
HWND hwnd;
MSG Msg;
WNDCLASSEX wndclass;
TCHAR lpszClassName[] = "����";	//��������
TCHAR lpszTitle[] = "My_Windows";	//���ڱ�����

ATOM MyRegisterClass(HINSTANCE hInstance);//ע�ᴰ�ں���

BOOL Create(HINSTANCE hInstance, int nCmdShow);//��������ʵ������

int Run(); //������Ϣѭ������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //���ں���˵��

HFONT CreateFont(HDC hDC, int nCharHeight, int nCharWidth);

													  //--------------- ���³�ʼ�������� ----------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	//MyRegisterClass(hInstance);
	Create(hInstance, nCmdShow);

	Run();
}



//------------ע�ᴰ�ں���--------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance) {

	//������Ķ���
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = 0;			//��������Ϊȱʡ����
	wndclass.lpfnWndProc = WndProc;	//���崰�ڴ�����
	wndclass.cbClsExtra = 0;		//����������չ
	wndclass.cbWndExtra = 0;		//����ʵ������չ
	wndclass.hInstance = hInstance;	//��ǰʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//���ڵ���С��ͼ��Ϊȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//���ڲ��ü�ͷ���
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ڱ���Ϊ��ɫ
	wndclass.lpszMenuName = NULL;	//�������޲˵�
	wndclass.lpszClassName = lpszClassName;
	wndclass.hIconSm = LoadIcon(wndclass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//��������Ϊ"����"
	//--------------- ���½��д������ע�� -------
	if (!RegisterClassEx(&wndclass))//���ע��ʧ���򷢳�����
	{
		MessageBeep(0);
		MessageBox(NULL, _T("����ע��ʧ�ܣ�"), _T("����ע��"), NULL);
		return FALSE;
	}
	return TRUE;

}

//------------��������ʵ������----------------------------------
BOOL Create(HINSTANCE hInstance, int nCmdShow) {
	//-------------- ����ע�� -----------------------
	if (!MyRegisterClass(hInstance)) {
		return FALSE;
	}
	hwnd = CreateWindow(
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
	ShowWindow(hwnd, nCmdShow);
	//-------------- �����û��� ---------------------
	UpdateWindow(hwnd);
}

//------------������Ϣѭ������----------------------------------
int Run() {
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
int x = 325, y = 25, v = 0, flag = 0;
//------------������Ϣ������----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//�����豸�������.
	HFONT hF;				//����������.	
	PAINTSTRUCT PtStr;			//���������ͼ��Ϣ�Ľṹ�����
	char lpsz_1[] = "�㽭���̴�ѧ��ӭ����";	//����������ַ���
	int nCharlen = strlen(lpsz_1) / 2;	//�����ַ������ȱ���.
	int X = 0, Y = 0, i;
	int nCharHeight;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &PtStr);
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 40 - (int)((40.0 - 15.0) / (nCharlen - 1)*i);//�����ַ��ĸ߶�.
			X = i * 30;							//�ַ����λ�õ�X����.
			Y = 50 - nCharHeight / 2;				//�ַ����λ�õ�Y����.
			SetTextColor(hDC, RGB(255 - i * 15, 0, 0));//�����ַ�����ɫ.
			hF = CreateFont(hDC, nCharHeight, 15);			//��������.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 15 + (int)((40.0 - 15.0) / (nCharlen - 1)*i);
			X = i * 30;
			Y = 75 - nCharHeight / 2;
			SetTextColor(hDC, RGB(105 + i * 15, 0, 0));
			hF = CreateFont(hDC, nCharHeight, 15);			//��������.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		//��������С˫���α仯��������.
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = (int)(-1.23*i*i + 11.07*i + 15.1);//�����ַ��ĸ߶�.
			X = i * 30;
			Y = 120 - nCharHeight / 2;				//�ַ����λ�õ�Y����.
			SetTextColor(hDC, RGB(0, 255 - i * 15, 0));//�����ַ�����ɫ.
			hF = CreateFont(hDC, nCharHeight, 15);	//��������.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = (int)(0.9*i*i + 15);//�����ַ��ĸ߶�.
			X = i * 30;
			Y = 180 - nCharHeight / 2;				//�ַ����λ�õ�Y����.
			SetTextColor(hDC, RGB(0, 0, 255 - i * 20));//�����ַ�����ɫ.
			hF = CreateFont(hDC, nCharHeight, 15);	//��������.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		//���λ��ΪԲ�ε��ַ���.
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 30;						//�ַ��ĸ߶�.
			X = (int)(420 + 70 * cos(2 * Pi / (nCharlen)*i));//�ַ����λ�õ�X����.
			Y = (int)(300 + 70 * sin(2 * Pi / (nCharlen)*i));//�ַ����λ�õ�Y����.
			SetTextColor(hDC, RGB(255 - i * 15, 100, 0));	//�����ַ�����ɫ.
			hF = CreateFont(hDC, nCharHeight, 15);		//��������.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}
		//���λ��Ϊ��Բ��.
		for (i = 0; i<nCharlen; i++)
		{
			nCharHeight = 30 - i * 2;							//�ַ��ĸ߶�.
			X = (int)(420 - 80 * cos(-Pi / (nCharlen)*i));		//�ַ����λ�õ�X����.
			Y = (int)(120 + 80 * sin(-Pi / (nCharlen)*i) - nCharHeight / 2);	//�ַ����λ�õ�Y����.
			SetTextColor(hDC, RGB(255 - i * 15, 100, 255 - i * 15));	//�����ַ�����ɫ.
			hF = CreateFont(hDC, nCharHeight, 0);				//��������.
			SelectObject(hDC, hF);
			TextOut(hDC, X, Y, &lpsz_1[2 * i], 2);
		}

		DeleteObject(hF);				//ɾ��������.
		EndPaint(hwnd, &PtStr);
		break;
	default:	//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

HFONT CreateFont(HDC hDC, int nCharHeight, int nCharWidth){
	HFONT hFont;
	hFont = CreateFont(				//����������.
		nCharHeight,				//����߶�.
		nCharWidth,					//���.
		0,							//�ı���б��Ϊ0,��ʾˮƽ.
		0,							//������б��Ϊ0.
		400,						//����ֶ�.400Ϊ����.
		0,							//��б����?,
		0,							//���»���.
		0,							//��ɾ����.
		ANSI_CHARSET,				//��ʾ���õ��ַ���ΪANSI_CHARSET.
		OUT_DEFAULT_PRECIS,			//ɾ������Ϊȱʡֵ.
		CLIP_DEFAULT_PRECIS,		//�ü�����Ϊȱʡֵ.
		DEFAULT_QUALITY,			//�������Ϊȱʡֵ.
		DEFAULT_PITCH | FF_DONTCARE,	//�ּ�������ϵ��ʹ��ȱʡֵ.
		"Arial");					//��������.
	if (hFont == NULL) return NULL;
	else return hFont;
}