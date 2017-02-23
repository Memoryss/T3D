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

		//关闭HDC和窗口等
		void Close();

	private:
		HWND m_handle; //窗口句柄
		HDC m_hdc; //设备上下文
		HBITMAP m_hb;
		HBITMAP m_ob;
		LPVOID *m_framebuffer;

		int m_width; //窗口宽度 
		int m_height; //窗口高度
		std::string m_title; //窗口名称
	};

}

#endif
