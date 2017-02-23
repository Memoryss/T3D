#ifndef __T3D_DEVICE_H__
#define __T3D_DEVICE_H__

#include "T3DUtil.h"

namespace T3D {
	//window相关
	class Device
	{
	public:
		void Init();

	private:
		UCHAR **m_framebuffer;  //帧缓存 二维数组
		int m_background_color;  //背景颜色
		int m_foreground_color;  //前景颜色

		float **m_zbuffer; //深度缓存 每个像素一个深度缓存

		int m_width; //窗口宽度
		int m_height;  //窗口高度

		int m_state;
	};

}

#endif