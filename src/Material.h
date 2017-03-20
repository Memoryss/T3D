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

		float m_d;  //����ָ��   0.0~1.0   0.0 ��ʾ��ȫ͸����1.0��ʾ��ȫ��͸��
		float m_ns; //����ָ��   0~1000   ֵԽ�� �߹�Խ�ܼ�
		float m_sharpness; //������  0~1000 Խ��Խ����
		float m_ni; //�����   0.001 ~ 10   1.0��ͨ���Ĳ���������  ��������������1.5

		std::vector<Texture *> m_textures;
	};

}

#endif