#include "T3DDevice.h"

#include <stdlib.h>
#include<memory>

namespace T3D {

	Device::Device(Camera *cam) : m_cam(cam)
	{

	}

	bool Device::Init(unsigned int *fb)
	{
		const ViewPort &vp = m_cam->GetViewPort();

		m_framebuffer = (unsigned int **)malloc(sizeof(unsigned int*) * vp.m_height);
		for (int line = 0; line < vp.m_height; ++line)
		{
			m_framebuffer[line] = fb + vp.m_width * line; //由于不使用dx 所以应该不用考虑pitch问题
		}

		m_zbuffer = (float *)malloc(vp.m_width * vp.m_height * sizeof(float));
		memset(m_zbuffer, 0, vp.m_width * vp.m_height * sizeof(float));

		m_foreground_color = 0xc0c0c0;
		m_background_color = 0xffffff;

		return true;
	}

	void Device::Clear()
	{
		const ViewPort &vp = m_cam->GetViewPort();

		float inv_h = (float)1 / vp.m_height;
		for (int h = 0; h < 600; ++h)
		{
			for (int w = 0; w < vp.m_width; ++w)
			{
				//int c = (float)0x0c * inv_h * (vp.m_height - h);  //清除颜色
				int c = (float)0xc0 * inv_h * (vp.m_height - h);
				m_framebuffer[h][w] = (c << 16 | c << 8 | c);
				m_zbuffer[h * m_cam->GetViewPort().m_width + w] = 1.0f;  //清除z buffer
			}
		}
	}

	void Device::Close()
	{
		if (m_framebuffer == NULL) free(m_framebuffer);

		if (m_zbuffer == NULL) free(m_zbuffer);
	}
}