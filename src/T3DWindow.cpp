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

	Window::Window(int width, int height, LPSTR title) : m_width(width), m_height(height), m_title(title)
	{
		
	}

	bool Window::Init()
	{
		WNDCLASS wc = { CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW , WindowProc, 0, 0, 0, NULL, NULL, NULL, NULL, _T(m_title.c_str()) };

		// -m_height表示top - bottom
		BITMAPINFO bi = { {sizeof(BITMAPINFOHEADER), m_width, -m_height, 1, 32, BI_RGB, m_width * m_height * 4, 0, 0, 0, 0} };

		RECT rect = { 0, 0, m_width, m_height };

		// 关闭窗口相关
		Close();

		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hInstance = GetModuleHandle(NULL);  //NULL表示本程序的instance
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		if (!RegisterClass(&wc)) 
		{
			return false;
		}

		//创建窗口
		m_handle = CreateWindow(_T("WINDOW"), m_title.c_str(), WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
		if (m_handle == 0) return false;

		HDC hDC = GetDC(m_handle);
		m_hdc = CreateCompatibleDC(hDC);
		ReleaseDC(m_handle, hDC);

		//创建应用程序可以直接写入的，与设备无关的位图
		m_hb = CreateDIBSection(m_hdc, &bi, DIB_RGB_COLORS, m_framebuffer, 0, 0);
		if (m_ob == NULL) return false;

		m_ob = (HBITMAP)SelectObject(m_hdc, m_hb);

		return true;
	}

	void Window::Close()
	{
		if (m_hdc)
		{
			if (m_ob)
			{
				//选择一个对象到制定的设备上下文中，新对象替换先前相同类型的对象
				SelectObject(m_hdc, m_ob);
				m_ob = NULL;
			}
			DeleteDC(m_hdc);
			m_hdc = NULL;
		}

		if (m_hb)
		{
			DeleteObject(m_hb);
			m_hb = NULL;
		}

		if (m_handle)
		{
			CloseWindow(m_handle);
			m_handle = NULL;
		}
	}
}