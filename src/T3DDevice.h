#ifndef __T3D_DEVICE_H__
#define __T3D_DEVICE_H__

#include "T3DUtil.h"
#include "T3DCamera.h"

namespace T3D {

	//window���
	class Device
	{
	public:
		Device(Camera *cam);
		bool Init(unsigned int *fb);

		void Clear();

		void Close();

	private:
		unsigned int **m_framebuffer;  //֡���� ��ά����
		int m_background_color;  //������ɫ
		int m_foreground_color;  //ǰ����ɫ

		float *m_zbuffer; //��Ȼ��� ÿ������һ����Ȼ���

		Camera *m_cam;  //���

		int m_state;
	};

}

#endif