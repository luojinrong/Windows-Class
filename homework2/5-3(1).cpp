#include<windows.h>	//����Ӧ�ó�����������������ͺ����ݽṹ�Ķ���
#include<tchar.h>
HWND hwnd;
MSG Msg;
WNDCLASSEX wndclass;
TCHAR lpszClassName[] = "����";	//��������
TCHAR lpszTitle[] = "My_Windows";	//���ڱ�����

ATOM MyRegisterClass(HINSTANCE hInstance);//ע�ᴰ�ں���

BOOL Create(HINSTANCE hInstance, int nCmdShow);//��������ʵ������

int Run(); //������Ϣѭ������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //���ں���˵��

HFONT mycreate(const TCHAR *fontname);//��������

void OnLbuttonDown(HWND hwnd);

char s1[] = "School of Computer & Information Engineering(SCIE)";
char s2[] = "SCIE was originally the Information Management Department established in 1985.";
char s3[] = "It was renamed as Computer and Information Engineering Department in 1996";

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
int x = 0, y = 0;
//------------������Ϣ������----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//�����豸�������.
	HPEN hPen;				//���廭�ʾ��
	PAINTSTRUCT PtStr;		//���������ͼ��Ϣ�Ľṹ�����
	TEXTMETRIC tm;
	SIZE size;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		
		hDC = BeginPaint(hwnd, &PtStr);
		HFONT hf;
		hf = mycreate("����");
		SelectObject(hDC, hf);
		GetTextMetrics(hDC, &tm);
		TextOut(hDC, x, y, s1, sizeof(s1));
		Sleep(1000);

		GetTextMetrics(hDC, &tm);
		hf = mycreate("Trebuchet MS");
		SelectObject(hDC, hf);
		y = y + tm.tmHeight + tm.tmExternalLeading;
		x = x + 2 * tm.tmAveCharWidth;
		TextOut(hDC, x, y, s2, sizeof(s2));
		GetTextExtentPoint32(hDC, s2, sizeof(s2), &size);
		x = x + size.cx;
		Sleep(1000);

		TextOut(hDC, x, y, s3, sizeof(s3));
		DeleteObject(hf);

		x = y = 0;
		EndPaint(hwnd, &PtStr);
		break;
	case WM_LBUTTONDOWN:
		//OnLbuttonDown(hwnd);
		break;
	default:	//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}

HFONT mycreate(const TCHAR *fontname) {
	return CreateFont(
		0,
		0,
		0,
		0,
		400,
		0,
		0,
		0,
		GB2312_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontname
	);
}
int flag = 0, x0 = 0, y0 = 0;
void OnLbuttonDown(HWND hwnd) {
	HDC hDC;
	HFONT hf;
	TEXTMETRIC tm;
	SIZE size;
	int x, y;
	hDC = GetDC(hwnd);
	if (flag == 0) {
		flag++;
		GetTextMetrics(hDC, &tm);
		hf = mycreate("Trebuchet MS");
		SelectObject(hDC, hf);
		y = y0 + tm.tmHeight + tm.tmExternalLeading;
		x = x0 + 2 * tm.tmAveCharWidth;
		TextOut(hDC, x, y, s2, sizeof(s2));
		GetTextExtentPoint32(hDC, s2, sizeof(s2), &size);
		x0 = x + size.cx;
		y0 = y;
		DeleteObject(hf);
	}
	else if (flag == 1) {
		flag++;
		hf = mycreate("Trebuchet MS");
		SelectObject(hDC, hf);
		TextOut(hDC, x0, y0, s3, sizeof(s3));
		DeleteObject(hf);
	}
	ReleaseDC(hwnd, hDC);
}