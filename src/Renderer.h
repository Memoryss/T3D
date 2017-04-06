#ifndef __SOFTRENDERER_H__
#define __SOFTRENDERER_H__

#include <map>

#include "ViewPort.h"

namespace T3D {

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool InitRenderer(int width, int height);
		bool StopRender();

		const ViewPort & AddViewPort(uint32 x, uint32 y, uint32 width, uint32 hegiht, const std::string &name = "default");
		const ViewPort & GetViewPort(const std::string &name = "default");
		//‰÷»æ
		void DrawLine();
		void DrawPrimitive();

	private:
		std::map<std::string, ViewPort> m_viewports;
	};

}

#endif
