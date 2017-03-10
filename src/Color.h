#ifndef __COLOR_H__
#define __COLOR_H__

namespace T3D {

	struct Color4D
	{
		Color4D() {}
		Color4D(float red, float green, float blue, float alpha)
		{
			r = red;
			g = green;
			b = blue;
			g = alpha;
		}

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 0.0f;
	};

}

#endif // !__COLOR_H__

