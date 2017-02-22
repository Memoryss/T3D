#define WIN32_LEAN_AND_MEAN  //ȥ�����õ�ͷ�ļ����ӿ�����ٶ�

#include <Windows.h>

#define WINDOW_CLASS_NAME "WIN3DCLASS"
#define WINDOW_TITLE "3DTriangle"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//ȫ�ֱ���
HWND main_window_handle;
HINSTANCE main_instance;

//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;  //WM_PAINT��ʹ��
	HDC hdc;  

	switch (msg)
	{
	case WM_CREATE:
		{
		//����ʼ������
		return 0;
		}
		break;
	case WM_PAINT:
		{
		//����
		hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
		return 0;
		}
		break;
	case WM_DESTROY:
		{
		//�ر�Ӧ�ó���
		PostQuitMessage(0);
		return 0;
		}
		break;
	}//end switch

	//�������ǲ����ĵ�������Ϣ
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdstr, int ncmdshow)
{
	WNDCLASS winclass; //���ڴ����ṹ��
	HWND hwnd;  //���ھ��
	MSG msg; //������Ϣ
	HDC hdc;  //�豸�����ĵ�������Ϣ
	PAINTSTRUCT ps; //���ڻ��ƿͻ�������Ϣ

	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;  //�����Ĵ�����ʽ
	winclass.lpfnWndProc = WindowProc; //���ڴ�����
	winclass.cbClsExtra = 0; //WNDCLASS��Ķ���ռ䣬��Ϊ�����ڴ棬����Ϊ�����������������д��ڹ���
	winclass.cbWndExtra = 0; //Ϊÿ�����ڷ�����⸽���ڴ�ռ�

	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //����ͼ��
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //���
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;

	//ע�ᴰ����
	if (!RegisterClass(&winclass)) return 1;

	//����������
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, WINDOW_TITLE, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hinstance, NULL))) return 1;

	main_instance = hinstance;
	main_window_handle = hwnd;


	//��������������
	RECT window_rect = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	AdjustWindowRect(&window_rect, GetWindowStyle(main_window_handle))
}