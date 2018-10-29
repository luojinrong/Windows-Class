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
int x, y, flag = 0, X, Y;
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
		Ellipse(hDC, x, y, X, Y);
		EndPaint(hwnd, &PtStr);
		break;
	case WM_CHAR:
		if (wParam == 'l' || wParam == 'L') {
			if (x > X) {
				x ^= X; X ^= x; x ^= X;
			}
			if (y > Y) {
				y ^= Y; Y ^= y; y ^= Y;
			}
			x -= 5; y -= 5; X += 5; Y += 5;
			InvalidateRect(hwnd, NULL, true);
		}
		if (wParam == 's' || wParam == 'S') {
			if (x > X) {
				x ^= X; X ^= x; x ^= X;
			}
			if (X - x < 10) {
				int mid = (x + X) >> 1;
				x = mid;
				X = mid;
			}
			else {
				x += 5; X -= 5;
			}
			if (y > Y) {
				y ^= Y; Y ^= y; y ^= Y;
			}
			if (Y - y < 10) {
				int mid = (y + Y) >> 1;
				y = mid;
				Y = mid;
			}
			else {
				y += 5; Y -= 5;
			}
			InvalidateRect(hwnd, NULL, true);
		}
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		flag = 1;
		break;
	case WM_LBUTTONUP:
		flag = 0;
		break;
	case WM_MOUSEMOVE:
		if (flag) {
			X = LOWORD(lParam);
			Y = HIWORD(lParam);
			InvalidateRect(hwnd, NULL, true);
		}
		break;
	default:	//ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return(0);
}