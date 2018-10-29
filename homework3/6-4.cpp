#include<windows.h>	//����Ӧ�ó�����������������ͺ����ݽṹ�Ķ���
#include<tchar.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
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

HFONT mycreate(const TCHAR *fontname);//��������

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
int pos = 0, scret_pos = 0, size = 10, x = 0, y = 0, flag = 0, r_flag = 0, g_flag = 0, b_flag = 0, max_raw, can_c=0;
//pos Ϊ������ַ����ȣ�scret_pos�ǹ��λ�ã��ַ����ڼ����ַ�������sizeΪ�ַ�����󳤶ȣ�x,yΪ��ǰ��ӡ���꣬flag����Ƿ������룬rgb_flag��ʾ��ǰ������ɫ��max_rawΪ��ǰ����һ�����洢�ַ�����can_c��ǵ�ǰ�Ƿ�Ϊȫѡ״̬������ʱ�ã�
bool Ctrl_Down = false, Ctrl_A_Down = false, Ctrl_C_DOWN = false, Ctrl_V_DOWN = false, Ctrl_S_DOWN = false;
char *s=(char*)malloc(sizeof(char)*size), *cv=(char*)malloc(sizeof(char)*size);

//------------������Ϣ������----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM  wParam, LPARAM  lParam)
{
	HDC hDC;				//�����豸�������.
	HFONT hF;				//����������.	
	HPEN hP;
	HBRUSH hB;
	PAINTSTRUCT PtStr;			//���������ͼ��Ϣ�Ľṹ�����
	TEXTMETRIC tm;
	RECT rc;
	SIZE sz;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		if (flag) {
			x = y = 0;
			hDC = BeginPaint(hwnd, &PtStr);
			char c[2];
			hF = mycreate("����");
			SelectObject(hDC, hF);
			if (r_flag) {
				SetTextColor(hDC, RGB(255, 0, 0));
			}
			else if (g_flag) {
				SetTextColor(hDC, RGB(0, 255, 0));
			}
			else if (b_flag) {
				SetTextColor(hDC, RGB(0, 0, 255));
			}
			else {
				SetTextColor(hDC, RGB(0, 0, 0));
			}
			if (Ctrl_A_Down) {
				Ctrl_A_Down = false;
				SetBkColor(hDC, RGB(0, 0, 255));
			}
			for (int i = 0; s[i]; i++) {
				c[0] = s[i];
				c[1] = 0;
				TextOut(hDC, x, y, c, sizeof(c));
				GetTextMetrics(hDC, &tm);
				CreateCaret(hwnd, NULL, 1, tm.tmHeight);
				//ShowCaret(hwnd);
				GetTextExtentPoint32(hDC, c, sizeof(c), &sz);
				x = x + sz.cx - tm.tmPitchAndFamily;
				GetClientRect(hwnd, &rc);
				max_raw = (rc.right / (sz.cx - tm.tmPitchAndFamily))-1;
				if (x + sz.cx > rc.right) {
					x = 0;
					y = y + tm.tmHeight + tm.tmExternalLeading;
				}
				if (i == scret_pos-1) {
					SetCaretPos(x, y);
				}
			}
			if (scret_pos == 0) {
				SetCaretPos(0, 0);
			}
			if (GetBkColor(hDC) == RGB(0, 0, 255)) {
				can_c = 1;
			}
			else {
				can_c = 0;
			}
			EndPaint(hwnd, &PtStr);
		}
		break;
	case WM_CHAR:
		if ((wParam >= 'a'&&wParam <= 'z') || (wParam >= 'A'&&wParam <= 'Z')) {
			cv[0] = 0;
			flag = 1;
			if (pos + 5 > size) {
				size *= 2;
				s = (char*)realloc(s, sizeof(char)*size);
				cv = (char*)realloc(cv, sizeof(char)*size);
			}
			if (pos == scret_pos) {
				s[pos] = wParam;
				s[++pos] = 0;
				scret_pos++;
			}
			else {
				char a = wParam;
				for (int i = scret_pos; i < pos+1; i++) {
					s[i] ^= a;
					a ^= s[i];
					s[i] ^= a;
				}
				s[++pos] = a;
				scret_pos++;
			}
			InvalidateRect(hwnd, NULL, false);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_CONTROL) {
			Ctrl_Down = true;
			//MessageBox(NULL, _T("Ctrl"), _T("������Ϣ"), NULL);
		}
		else if (wParam == 'A'&&Ctrl_Down) {
			Ctrl_A_Down = true;
			Ctrl_Down = false;
			//MessageBox(NULL, _T("Ctrl-A"), _T("������Ϣ"), NULL);
			InvalidateRect(hwnd, NULL, false);
			
		}
		else if (wParam == 'C'&&Ctrl_Down&& can_c) {
			Ctrl_C_DOWN = true;
			Ctrl_Down = false;
			strcpy(cv, s);
		}
		else if (wParam == 'V'&&Ctrl_Down) {
			Ctrl_V_DOWN = true;
			Ctrl_Down = false;
			if (strlen(s) * 2 > size) {
				size *= 2;
				s = (char*)realloc(s, sizeof(char)*size);
				cv = (char*)realloc(cv, sizeof(char)*size);
			}
			if (scret_pos == pos) {
				strcat(s, cv);
				scret_pos += strlen(cv) ;
			}
			else {
				char *tmp = (char*)malloc(sizeof(char)*size);
				for (int i = scret_pos;; i++) {
					if (s[i] == 0) {
						tmp[i - scret_pos] = 0;
						break;
					}
					else {
						tmp[i - scret_pos] = s[i];
					}
				}
				s[scret_pos] = 0;
				strcat(s, cv);
				strcat(s, tmp);
				scret_pos += strlen(cv);
			}
			pos = strlen(s);
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'S'&&Ctrl_Down) {
			Ctrl_S_DOWN = true;
			Ctrl_Down = false;
			FILE *fp;
			fp = fopen("./save.txt", "w");
			fprintf(fp, s);
			fclose(fp);
			MessageBox(NULL, "�ѱ���", "����һ����Ϣ", NULL);
		}
		else if (wParam == 'R') {
			//MessageBox(NULL, _T("Red"), _T("������Ϣ"), NULL);
			r_flag ^= 1;
			g_flag = 0;
			b_flag = 0;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'G') {
			//MessageBox(NULL, _T("Green"), _T("������Ϣ"), NULL);
			g_flag ^= 1;
			r_flag = 0;
			b_flag = 0;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == 'B') {
			//MessageBox(NULL, _T("Blue"), _T("������Ϣ"), NULL);
			b_flag ^= 1;
			r_flag = 0;
			g_flag = 0;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_LEFT && scret_pos) {
			scret_pos--;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_RIGHT && scret_pos < pos) {
			scret_pos++;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_UP && scret_pos > max_raw) {
			scret_pos -= max_raw;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (wParam == VK_DOWN && pos - scret_pos > max_raw) {
			scret_pos += max_raw;
			InvalidateRect(hwnd, NULL, false);
		}
		else {

		}
		break;
	case WM_KEYUP:
		if (wParam == VK_CONTROL) {
			Ctrl_Down = false;
		}
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