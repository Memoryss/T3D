#ifndef __T3D_DEVICE_H__
#define __T3D_DEVICE_H__

#include "T3DUtil.h"
#include "T3DCamera.h"

namespace T3D {

	//window相关
	class Device
	{
	public:
		Device(Camera *cam);
		bool Init(unsigned int *fb);

		void Clear();

		void Close();

	private:
		unsigned int **m_framebuffer;  //帧缓存 二维数组
		int m_background_color;  //背景颜色
		int m_foreground_color;  //前景颜色

		float *m_zbuffer; //深度缓存 每个像素一个深度缓存

		Camera *m_cam;  //相机

		int m_state;
	};

}

#endif