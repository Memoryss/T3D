#include "Renderer.h"

namespace T3D {

	const ViewPort & Renderer::AddViewPort(uint32 x, uint32 y, uint32 width, uint32 hegiht, const std::string & name)
	{
		auto iter = m_viewports.find(name);
		if (iter != m_viewports.end())
		{
			return iter->second;
		}

		ViewPort port(x, y, width, hegiht);
		return m_viewports.emplace(name, port).first->second;
	}
	const ViewPort & Renderer::GetViewPort(const std::string & name)
	{
		auto iter = m_viewports.find(name);
		if (iter != m_viewports.end())
		{
			return iter->second;
		}

		ViewPort port;
		return m_viewports.emplace(name, port).first->second;
	}
}