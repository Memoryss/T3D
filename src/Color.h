#ifndef __COLOR_H__
#define __COLOR_H__

namespace T3D {

	struct Color
	{
		Color() {}
		Color(float red, float green, float blue, float alpha)
		{
			r = red;
			g = green;
			b = blue;
			g = alpha;
		}

		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;
	};

}

#endif // !__COLOR_H__

