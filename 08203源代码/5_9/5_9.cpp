  
//   HELLO60.C -- Displays "Hello,VC++ 6.0!" in client area

#include <windows.h>//������windows�������������ͣ��ṹ����������

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM) ;//Wndproc�Ǵ��ڹ��̺�����

int WINAPI WinMain(		//windowsϣ��winmainʹ��ͨ�õ�API��������Լ��
	HINSTANCE hInstance,	//��ǰʵ�����
	HINSTANCE hPrevInstance,//ǰһ��ʵ�����
        LPSTR lpszCmdParam,	//ָ���ַ�����ָ�룬����ָ�����ڴ����г������Ļ�����
	int nCmdShow)		//Ӧ�ó���ʼִ��ʱ���ڵ���ʾ��ʽ������SW_SHOWNORMAL
{
 static char szAppName[] = "Hello60" ;	//����������֣�����Ϊ������
 HWND        hwnd ;			//���ھ��
 MSG         msg ;			//��Ϣ�ṹ��
 WNDCLASS    wndclass ;			//������

 if(!hPrevInstance)				
    {
     wndclass.style = CS_HREDRAW | CS_VREDRAW ;//���崰������Ϊ���������ػ�
     wndclass.lpfnWndProc= WndProc ;		//���ڴ�����
     wndclass.cbClsExtra = 0 ;			//����������ṹ�ռ�(����������չ)
     wndclass.cbWndExtra = 0 ;			//�������ⴰ�ڽṹ�ռ�(����ʵ������չ)
     wndclass.hInstance = hInstance ;		//����winmain�ĵ�һ������
     wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);//IDI_APPLICATIONΪ������С��ȷʡͼ��
     wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;//���崰�ڲ���IDC_ARROW(��ͷ)���
     wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;//���ڿͻ����ı���Ϊǳ��ɫ
     wndclass.lpszMenuName  = NULL ;	//Ӧ�ó��򴰿���û�в˵������Բ˵���ΪNULL
     wndclass.lpszClassName = szAppName ;//����������֣�һ��Ӧ�ͳ�������һ��
     RegisterClass (&wndclass) ;//�����������ע�ᴰ����
    }

     hwnd = CreateWindow (				//�ú�������һ������ʵ��
			szAppName,			// window class name
			"The Hello Program",		// ����ʵ��������
                    	WS_OVERLAPPEDWINDOW,		// window style
                    	CW_USEDEFAULT,CW_USEDEFAULT,	// �������Ͻ����� 
                    	CW_USEDEFAULT,CW_USEDEFAULT,	// ���ڵĸߺͿ�
                    	NULL,				// parent window handle
                    	NULL,				// window menu handle
                    	hInstance,			// program instance handle of current window
			NULL);				// creation parameters

     ShowWindow (hwnd, nCmdShow) ;			//nCmdShow��־��ʾ��ʽ
     UpdateWindow (hwnd) ;				//�����û���������WM_PAINT��Ϣ

     while (GetMessage (&msg, NULL, 0, 0))//ȡ����Ϣ�����ܵ�WM_QUIT�⣬�κ���Ϣ������TRUE
          {
          TranslateMessage (&msg) ;		//��һЩ������Ϣ���з���
          DispatchMessage (&msg) ;		//����Ϣ���͸���MSG�ṹ��Ϊ������ָ������Ϣ������
          }
     return msg.wParam ;				//������ֹʱ��֪ϵͳ
 }

LRESULT CALLBACK WndProc( HWND hwnd,	//������Ϣ�Ĵ��ھ��
			  UINT message, //���õ���Ϣ��
			  WPARAM wParam,//��Ϣ����
			  LPARAM lParam)//��Ϣ����
{
     HDC         hdc ;		//�豸���
     PAINTSTRUCT ps ;		//��ˢ�ṹ
     RECT	 rect ;		//��Ч������
     static LOGFONT lf;			
     HFONT holdFont,hnewFont;	

     switch (message)		//��Ϣ������
      {   
       case WM_CREATE:		//���ڴ���������0
        return 0;

		case WM_PAINT:										//������Ϣ
			lf.lfHeight=-64;	
			lf.lfWeight=500;	
			lf.lfPitchAndFamily=DEFAULT_PITCH & FF_DONTCARE;
			lf.lfCharSet=GB2312_CHARSET;						//ѡ���ַ���				
			strcpy(lf.lfFaceName,"����");					//�ַ�����ֵ����������
			hnewFont=CreateFontIndirect(&lf);					//����һ���µ��߼�����
			hdc = BeginPaint (hwnd, &ps);					//�õ��豸�������        	GetClientRect (hwnd, &rect);						//�õ���Ҫ���ƵĿͻ���
			GetClientRect (hwnd, &rect) ;			//�õ���Ҫ���ƵĿͻ���
			holdFont=(HFONT)SelectObject(hdc,hnewFont);		//ѡ���µ������ʽ�����ұ����ϵĻ���
			SetTextColor(hdc,RGB(255,0,0));					//�����ı���ɫ
			SetBkColor(hdc,RGB(255,255,0));					//���ñ�����ɫ

			DrawText(hdc,									//����ı�
				 "VC����ʾ�����뱳��",						//������ַ���
	 			 -1,										//�Զ���������ַ��ĸ���
				&rect,									//����ı�������
				DT_SINGLELINE|DT_CENTER|DT_VCENTER);			//��������ھ��οͻ���������
	 		SelectObject(hdc,holdFont);						//����ԭ���������ʽ

			DeleteObject(hnewFont);							//ɾ���µ������ʽ
			EndPaint (hwnd, &ps) ;						//�������ƣ���BeiginPaint��������
        	return 0 ;

       case WM_DESTROY:		//�˳���Ϣ
        PostQuitMessage (0) ;	//����ϵͳ�˳�����
        return 0 ;  
}
  return DefWindowProc(hwnd,message,wParam,lParam) ;//����Ĭ�Ϻ�������û�д������Ϣ
}