#ifndef __T3D_DEVICE_H__
#define __T3D_DEVICE_H__

#include "T3DUtil.h"

namespace T3D {
	//window���
	class Device
	{
	public:
		Device(int widht = 800, int height = 600);
		bool Init(UCHAR *fb);

		void Clear();

		void Close();

	private:
		bool clipLine(int &x1, int &y1, int &x2, int &y2);

	private:
		UCHAR **m_framebuffer;  //֡���� ��ά����
		int m_background_color;  //������ɫ
		int m_foreground_color;  //ǰ����ɫ

		float *m_zbuffer; //��Ȼ��� ÿ������һ����Ȼ���

		Rect m_rect; //���ھ���

		int m_state;
	};

}

#endif