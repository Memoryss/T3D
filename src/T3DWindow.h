#ifndef __T3D_WINDOW_H__
#define __T3D_WINDOW_H__

#include <Windows.h>

namespace T3D {

	class Window
	{
	public:
		Window(int width = 800, int height = 600, LPSTR title = "");

	private:
		HWND m_handle; //���ھ��
		HDC m_hdc; //�豸������
		HBITMAP m_hb;
		HBITMAP m_ob;
		LPVOID m_framebuffer;

		int m_width; //���ڿ�� 
		int m_height; //���ڸ߶�
	};

}

#endif
