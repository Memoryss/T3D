#ifndef __T3D_WINDOW_H__
#define __T3D_WINDOW_H__

#include <Windows.h>
#include <string>

namespace T3D {

	class Window
	{
	public:
		Window(int width = 800, int height = 600, LPSTR title = "");

		bool Init();

		//�ر�HDC�ʹ��ڵ�
		void Close();

	private:
		HWND m_handle; //���ھ��
		HDC m_hdc; //�豸������
		HBITMAP m_hb;
		HBITMAP m_ob;
		LPVOID *m_framebuffer;

		int m_width; //���ڿ�� 
		int m_height; //���ڸ߶�
		std::string m_title; //��������
	};

}

#endif
