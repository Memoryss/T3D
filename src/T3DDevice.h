#ifndef __T3D_DEVICE_H__
#define __T3D_DEVICE_H__

#include "T3DUtil.h"

namespace T3D {
	//window���
	class Device
	{
	public:
		void Init();

	private:
		UCHAR **m_framebuffer;  //֡���� ��ά����
		int m_background_color;  //������ɫ
		int m_foreground_color;  //ǰ����ɫ

		float **m_zbuffer; //��Ȼ��� ÿ������һ����Ȼ���

		int m_width; //���ڿ��
		int m_height;  //���ڸ߶�

		int m_state;
	};

}

#endif