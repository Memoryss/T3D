#include "T3DUtil.h"

namespace T3D {


	UNSHORT RGB16Bit565(int r, int g, int b)
	{
		r >>= 3;
		g >>= 2;
		b >>= 3;

		UNSHORT x = 0;
		x = x | (r << 11);
		x = x | (g << 5);
		x = x | b;

		return x;
	}

	UNSHORT RGB16Bit555(int r, int g, int b)
	{
		r >>= 3;
		g >>= 2;
		b >>= 3;

		UNSHORT x = 0;
		x = x | (r << 10);
		x = x | (g << 5);
		x = x | b;

		return x;
	}

}