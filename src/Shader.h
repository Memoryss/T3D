#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>

namespace T3D {

	class Shader
	{
	public:
		virtual void ProcessPatch() = 0;
		virtual void ProcessVertex() = 0;
		virtual void ProcessRasterize() = 0;
		virtual void ProcessPixel() = 0;

	private:
		std::string m_name;
	};

}

#endif // !__SHADER_H__

