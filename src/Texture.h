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
		SF_Nearest = 0, //临近点采样
		SF_Linear,  //双线性过滤
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

		
		//纹理坐标应该是在0.0 - 1.0之间
		uint32 Sample(float x, float y, SamplerFilter filter);

	protected:
		//获取x y坐标的像素值 BGRA  整数采样不需要过滤？
		uint32 sampleImp(uint32 x, uint32 y) const;

		//领近点采样
		uint32 sampleNearest(float u, float v);
		//双线性采样  周围的四个像素点
		uint32 sampleLinear(float u, float v);

	private:

		uint32 m_width;
		uint32 m_height;
		uint32 m_byteCount;   //每个像素的字节数  1 黑白图 4 8 24 32等
		uint32 m_pitch;

		std::string m_filename;
		aiTextureType m_type; //纹理类型

		uint8 *m_rawData;

		uint8 *m_data;
		//格式argb 8888
		//Texel *m_data;
	};

}


#endif
