#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>

#include <assimp/material.h>
#include <Vector.h>
#include "Color.h"


namespace T3D {
	
	class Texture;

	//TODO暂时就是使用这种材质参数
	class Material
	{
	public:
		Material();
		~Material();

		Color m_specular = { 0.f, 0.f, 0.f, 1.f };
		Color m_diffuse = { 0.f, 0.f, 0.f, 1.f };
		Color m_ambient = { 0.f, 0.f, 0.f, 1.f };
		Color m_emission = { 0.f, 0.f, 0.f, 1.f };
		
		float m_shininess;  //高光相关

		std::map<aiTextureType, std::vector<Texture*>> m_textures;
		//Texture* m_textures[aiTextureType_UNKNOWN - 1] = {0};  //除去第一个和最后一个
	};

}

#endif