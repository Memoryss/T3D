#include "T3DWindow.h"

#include <tchar.h>

namespace T3D {

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

	Window::Window(int width, int height, LPSTR title)	
	{
		WNDCLASS ws = { CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW , WindowProc, 0, 0, 0, NULL, NULL, NULL, NULL, _T(title) };
		

	}
}