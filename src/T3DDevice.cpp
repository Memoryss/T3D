#include "T3DDevice.h"

#include <stdlib.h>
#include<memory>

namespace T3D {

	Device::Device(int width, int height) : m_width(width), m_height(height)
	{

	}

	bool Device::Init(UCHAR *fb)
	{
		m_framebuffer = (UCHAR **)malloc(sizeof(fb) * m_height);
		for (int line = 0; line < m_height; ++line)
		{
			m_framebuffer[line] = fb + m_width * line; //���ڲ�ʹ��dx ����Ӧ�ò��ÿ���pitch����
		}

		m_zbuffer = (float *)malloc(m_width * m_height * sizeof(float));
		memset(m_zbuffer, 0, m_width * m_height * sizeof(float));

		m_foreground_color = 0xc0c0c0;
		m_background_color = 0xffffff;
	}

	void Device::Clear()
	{
		float inv_h = (float)1 / m_height;
		for (int h = 0; h < m_height; ++h)
		{
			for (int w = 0; w < m_height; ++w)
			{
				int c = (float)0x0c * inv_h * (m_height - h);  //�����ɫ
				m_framebuffer[h][w] = (c << 16 | c << 8 | c);
				m_zbuffer[h * m_width + w] = 1.0f;  //���z buffer
			}
		}
	}

	void Device::Close()
	{
		if (m_framebuffer == NULL) free(m_framebuffer);

		if (m_zbuffer == NULL) free(m_zbuffer);
	}
}