#ifndef __COLOR_H__
#define __COLOR_H__

#include <assimp/color4.h>

namespace T3D {

	class Color
	{
	public:
		Color() {}
		Color(float red, float green, float blue, float alpha)
		{
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		inline Color & operator * (float scale)
		{
			r *= scale;
			g *= scale;
			b *= scale;
			a *= scale;

			return *this;
		}

		inline Color & operator *= (float scale)
		{
			r *= scale;
			g *= scale;
			b *= scale;
			a *= scale;

			return *this;
		}

		inline Color & operator + (const Color &color)
		{
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;

			return *this;
		}

		inline Color & operator += (const Color &color)
		{
			r += color.r;
			g += color.g;
			b += color.b;
			a += color.a;

			return *this;
		}

		inline Color & operator / (float scale)
		{
			r /= scale;
			g /= scale;
			b /= scale;
			a /= scale;

			return *this;
		}

		inline Color & operator /= (float scale)
		{
			r /= scale;
			g /= scale;
			b /= scale;
			a /= scale;

			return *this;
		}

		inline Color & operator = (const Color &rhs)
		{
			r = rhs.r;
			g = rhs.g;
			b = rhs.b;
			a = rhs.a;

			return *this;
		}

		inline Color & operator = (const aiColor4D & color)
		{
			r = color.r;
			g = color.g;
			b = color.b;
			a = color.a;

			return *this;
		}

	public:
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;
	};

}

#endif // !__COLOR_H__

