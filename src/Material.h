#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>

#include "Resource.h"
#include "Color.h"

namespace T3D {
	
	class Texture;

	class Material : public Resource
	{
	public:
		Material(const char *filename);
		~Material();

		Color m_specularColor = { 0.f, 0.f, 0.f, 1.f };
		Color m_diffuseColor = { 0.f, 0.f, 0.f, 1.f };
		Color m_ambientColor = { 0.f, 0.f, 0.f, 1.f };

		float m_d = 1.0;  //渐隐指数   0.0~1.0   0.0 表示完全透明，1.0表示完全不透明
		float m_ns = 500; //反射指数   0~1000   值越高 高光越密集
		float m_sharpness = 500; //清晰度  0~1000 越大越清晰
		float m_ni = 1.0; //折射度   0.001 ~ 10   1.0光通过的不发生弯曲  玻璃的折射率是1.5

		std::string m_mapKd; 
		std::string m_mapKa;
		std::string m_mapKs;

		std::vector<Texture *> m_textures;
	};

}

#endif