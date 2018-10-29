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

HFONT mycreate(int i, int nCharlen, char* chFont);

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
int iFontSign = 0;
//------------������Ϣ������----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//�����豸�������.
	HFONT hF;				//����������.	
	PAINTSTRUCT PtStr;			//���������ͼ��Ϣ�Ľṹ�����
	TEXTMETRIC tm;			//�������������Ϣ�Ľṹ�����.
	static char lpsz_1[] = "�㽭���̴�ѧ  ";	//����������ַ���.
	char chFont[20];				//��������������ַ���.
	int X = 0, Y = 0, i;
	static int nCharlen = strlen(lpsz_1);	//�����ַ������ȱ���.
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &PtStr);
		for (i = 0; i<nCharlen; i += 2)		//����ĳ���������ɫ����ַ���.
		{
			SetTextColor(hDC, RGB((long)(255.0 / nCharlen * i),//����������ɫ.
				(long)(255.0 / nCharlen * i),
				(long)(255.0 / nCharlen * i)));
			if (iFontSign % 5 == 0) strcpy(chFont, "����_GB2312");	//���ð���������Ϣ���ַ���.
			else if (iFontSign % 5 == 1) strcpy(chFont, "����");	//iFont%��ʾ��5Ϊ����ѭ���ı�����.
			else if (iFontSign % 5 == 2) strcpy(chFont, "����");
			else if (iFontSign % 5 == 3) strcpy(chFont, "����");
			else strcpy(chFont, "��Բ");
			hF = mycreate(i, nCharlen, chFont);
			SelectObject(hDC, hF);			//ѡ������.
			GetTextMetrics(hDC, &tm);		//�õ�����������Ϣ�Ľṹ��.
			X = X + tm.tmAveCharWidth * 2;		//��������ַ���X����.
			Y = iFontSign % 5 * 40 + tm.tmExternalLeading;	//��������ַ���Y����.
			TextOut(hDC, X, Y, &lpsz_1[i], 2);	//�����i���ַ�.����������Ч��.
			Sleep(400);						//��ͣ0.4��.
			DeleteObject(hF);		//ɾ��������.
		}
		iFontSign++;				//�����־����
		InvalidateRect(hwnd, NULL, 1);//ˢ���û���.
		EndPaint(hwnd, &PtStr);
		break;
	default:	//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

HFONT mycreate(int i,int nCharlen,char* chFont) {
	return CreateFont(				//����������.
		(long)(8 + 32.0*i / nCharlen),	//����߶�.
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
		DEFAULT_PITCH | FF_DONTCARE,	//�ּ�������ϵ��ʹ��ȱʡֵ.
		chFont);					//��������.
}