#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Color.h"

#include <assimp/material.h>
#include <string>

typedef unsigned int uint32;
typedef unsigned char uint8;

namespace T3D {

	enum SamplerFilter
	{
		SF_Nearest = 0, //�ٽ������
		SF_Linear,  //˫���Թ���
	};

	struct Texel
	{
		uint8 r, g, b, a;

		bool operator==(const Texel &rhs)
		{
			return rhs.r == r && rhs.g == rhs.g && rhs.b == rhs.b && rhs.a == rhs.a;
		}

		operator Color4D() const
		{
			return Color4D(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
		}
	};


	class Texture
	{
	public:

		Texture(const char *filename, aiTextureType type);

		Texture();

		void SetPathAndType(const char *filepath, aiTextureType type);

		void ReadFile();

		~Texture()
		{
			delete[]m_rawData;
		}

		
		//��������Ӧ������0.0 - 1.0֮��
		uint32 Sample(float x, float y, SamplerFilter filter);

	protected:
		//��ȡx y���������ֵ BGRA  ������������Ҫ���ˣ�
		uint32 sampleImp(uint32 x, uint32 y) const;

		//��������
		uint32 sampleNearest(float u, float v);
		//˫���Բ���  ��Χ���ĸ����ص�
		uint32 sampleLinear(float u, float v);

	private:

		uint32 m_width;
		uint32 m_height;
		uint32 m_byteCount;   //ÿ�����ص��ֽ���  1 �ڰ�ͼ 4 8 24 32��
		uint32 m_pitch;

		std::string m_filename;
		aiTextureType m_type; //��������

		uint8 *m_rawData;

		uint8 *m_data;
		//��ʽargb 8888
		//Texel *m_data;
	};

}


#endif
