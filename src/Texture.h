#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Color.h"

typedef unsigned int uint32;
typedef unsigned char uint8;

namespace T3D {

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
		uint32 m_width;
		uint32 m_height;

		//∏Ò Ωargb 8888
		Texel *m_pcData;

		Texture() : m_width(0), m_height(0), m_pcData(0)
		{

		}

		~Texture()
		{
			delete[]m_pcData;
		}

	};

}


#endif
