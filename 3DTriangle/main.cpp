#define WIN32_LEAN_AND_MEAN  //去除无用的头文件，加快编译速度

#include <Windows.h>

#define WINDOW_CLASS_NAME "WIN3DCLASS"
#define WINDOW_TITLE "3DTriangle"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//全局变量
HWND main_window_handle;
HINSTANCE main_instance;

//窗口处理函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;  //WM_PAINT中使用
	HDC hdc;  

	switch (msg)
	{
	case WM_CREATE:
		{
		//做初始化工作
		return 0;
		}
		break;
	case WM_PAINT:
		{
		//绘制
		hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
		return 0;
		}
		break;
	case WM_DESTROY:
		{
		//关闭应用程序
		PostQuitMessage(0);
		return 0;
		}
		break;
	}//end switch

	//处理我们不关心得其他消息
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdstr, int ncmdshow)
{
	WNDCLASS winclass; //窗口创建结构体
	HWND hwnd;  //窗口句柄
	MSG msg; //窗口消息
	HDC hdc;  //设备上下文的属性信息
	PAINTSTRUCT ps; //窗口绘制客户区的信息

	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;  //创建的窗口样式
	winclass.lpfnWndProc = WindowProc; //窗口处理函数
	winclass.cbClsExtra = 0; //WNDCLASS类的额外空间，成为附属内存，可以为属于这个窗口类的所有窗口共享
	winclass.cbWndExtra = 0; //为每个窗口分配额外附加内存空间

	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //加载图标
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //鼠标
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;

	//注册窗口类
	if (!RegisterClass(&winclass)) return 1;

	//创建窗口类
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, WINDOW_TITLE, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hinstance, NULL))) return 1;

	main_instance = hinstance;
	main_window_handle = hwnd;


	//窗口重新设置下
	RECT window_rect = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	AdjustWindowRect(&window_rect, GetWindowStyle(main_window_handle))
}