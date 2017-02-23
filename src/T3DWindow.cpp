#include "T3DWindow.h"

#include <tchar.h>

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
		}//end switch

		 //�������ǲ����ĵ�������Ϣ
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	Window::Window(int width, int height, LPSTR title)	
	{
		WNDCLASS ws = { CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW , WindowProc, 0, 0, 0, NULL, NULL, NULL, NULL, _T(title) };
		

	}
}