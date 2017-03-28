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

		float m_d = 1.0;  //����ָ��   0.0~1.0   0.0 ��ʾ��ȫ͸����1.0��ʾ��ȫ��͸��
		float m_ns = 500; //����ָ��   0~1000   ֵԽ�� �߹�Խ�ܼ�
		float m_sharpness = 500; //������  0~1000 Խ��Խ����
		float m_ni = 1.0; //�����   0.001 ~ 10   1.0��ͨ���Ĳ���������  ��������������1.5

		std::string m_mapKd; 
		std::string m_mapKa;
		std::string m_mapKs;

		std::vector<Texture *> m_textures;
	};

}

#endif