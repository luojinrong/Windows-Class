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
int x = 300, y = 200, v = 0, flag = 0, fl = 0;
//------------������Ϣ������----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//�����豸�������.
	HFONT hF;				//����������.	
	HPEN hP;
	HBRUSH hB;
	PAINTSTRUCT PtStr;			//���������ͼ��Ϣ�Ľṹ�����
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &PtStr);
		if (flag) {
			hB = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hDC, hB);
		}
		else {
			hB = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hDC, hB);
		}
		if (fl) {
			Ellipse(hDC, x, y, x + 50, y + 50);
		}
		else {
			Rectangle(hDC, x, y, x + 50, y + 50);
		}
		EndPaint(hwnd, &PtStr);
		break;
	case WM_CHAR:
		if (wParam == 'b' || wParam == 'B') {
			flag ^= 1;
		}
		if (wParam == 'c' || wParam == 'C') {
			fl = 1;
		}
		if (wParam == 'r' || wParam == 'R') {
			fl = 0;
		}
		InvalidateRect(hwnd, NULL, true);
		break;
	case WM_KEYUP:
		if (wParam == VK_LEFT && x > 0) {
			x -= 10;
		}
		else if (wParam == VK_UP && y > 0) {
			y -= 10;
		}
		else if (wParam == VK_RIGHT && x < 800) {
			x += 10;
		}
		else if (wParam == VK_DOWN && y < 400) {
			y += 10;
		}
		InvalidateRect(hwnd, NULL, true);
		break;
	default:	//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}