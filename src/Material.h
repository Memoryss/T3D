#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>

#include <assimp/material.h>
#include <Vector.h>
#include "Color.h"


namespace T3D {
	
	class Texture;

	//TODO��ʱ����ʹ�����ֲ��ʲ���
	class Material
	{
	public:
		Material();
		~Material();

		Color m_specular = { 0.f, 0.f, 0.f, 1.f };
		Color m_diffuse = { 0.f, 0.f, 0.f, 1.f };
		Color m_ambient = { 0.f, 0.f, 0.f, 1.f };
		Color m_emission = { 0.f, 0.f, 0.f, 1.f };
		
		float m_shininess;  //�߹����

		std::map<aiTextureType, std::vector<Texture*>> m_textures;
		//Texture* m_textures[aiTextureType_UNKNOWN - 1] = {0};  //��ȥ��һ�������һ��
	};

}

#endif