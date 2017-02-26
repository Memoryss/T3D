#include "T3DWindow.h"

#include <tchar.h>

bool EXIT = false;

namespace T3D {

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
		case WM_CLOSE:
		{
			EXIT = true;
			return 0;
		}
		break;
		}//end switch

		 //�������ǲ����ĵ�������Ϣ
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	Window::Window(int width, int height, LPSTR title) : m_width(width), m_height(height), m_title(title)
	{
		
	}

	bool Window::Init()
	{
		WNDCLASS wc = { CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW , WindowProc, 0, 0, 0, NULL, NULL, NULL, NULL,_T("WINDOW") };

		// -m_height��ʾtop - bottom
		BITMAPINFO bi = { {sizeof(BITMAPINFOHEADER), m_width, -m_height, 1, 32, BI_RGB, m_width * m_height * 4, 0, 0, 0, 0} };

		RECT rect = { 0, 0, m_width - 1, m_height - 1 };

		// �رմ������
		Close();

		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hInstance = GetModuleHandle(NULL);  //NULL��ʾ�������instance
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		if (!RegisterClass(&wc)) 
		{
			return false;
		}

		//��������
		m_handle = CreateWindow(_T("WINDOW"), m_title.c_str(), WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0, 0, m_width, m_height, NULL, NULL, wc.hInstance, NULL);
		if (m_handle == 0) return false;

		HDC hDC = GetDC(m_handle);
		m_hdc = CreateCompatibleDC(hDC);
		ReleaseDC(m_handle, hDC);

		//����Ӧ�ó������ֱ��д��ģ����豸�޹ص�λͼ
		m_hb = CreateDIBSection(m_hdc, &bi, DIB_RGB_COLORS, &m_framebuffer, 0, 0);
		if (m_hb == NULL) return false;
		m_ob = (HBITMAP)SelectObject(m_hdc, m_hb);

		//�������ڴ�С
		AdjustWindowRect(&rect, GetWindowLong(m_handle, GWL_STYLE), 0);
		int wx = rect.right - rect.left;
		int wy = rect.bottom - rect.top;
		int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2; //�Ǵ���λ��λ������
		int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
		if (sy < 0) sy = 0;

		SetWindowPos(m_handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
		SetForegroundWindow(m_handle); //��������Ȩ�ϸ�

		ShowWindow(m_handle, SW_NORMAL);
		Dispatch();

		memset(m_framebuffer, 0, m_width * m_height * 4);

		return true;
	}

	void Window::Close()
	{
		if (m_hdc)
		{
			if (m_ob)
			{
				//ѡ��һ�������ƶ����豸�������У��¶����滻��ǰ��ͬ���͵Ķ���
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

	void Window::Dispatch()
	{
		MSG msg;
		while (true)
		{
			if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
			if (!GetMessage(&msg, NULL, 0, 0)) break;
			DispatchMessage(&msg);
		}
	}

	void Window::Update()
	{
		HDC hdc = GetDC(m_handle);
		//��Դ�豸������������ת��
		// SRCCOPY ��Դ��������ֱ�ӿ�����Ŀ���������
		BitBlt(hdc, 0, 0, m_width, m_height, m_hdc, 0, 0, SRCCOPY); 
		ReleaseDC(m_handle, hdc);

		Dispatch();
	}

	unsigned int * Window::GetFrameBuffer()
	{
		return (unsigned int *)m_framebuffer;
	}

	bool Window::IsExit()
	{
		return EXIT;
	}
}