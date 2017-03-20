#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>

#include "Color.h"

namespace T3D {
	
	class Texture;

	class Material
	{
	public:


	private:
		Color m_specularColor;
		Color m_diffuseColor;
		Color m_ambientColor;

		float m_d;  //渐隐指数   0.0~1.0   0.0 表示完全透明，1.0表示完全不透明
		float m_ns; //反射指数   0~1000   值越高 高光越密集
		float m_sharpness; //清晰度  0~1000 越大越清晰
		float m_ni; //折射度   0.001 ~ 10   1.0光通过的不发生弯曲  玻璃的折射率是1.5

		std::vector<Texture *> m_textures;
	};

}

#endif