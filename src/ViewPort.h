#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

typedef unsigned int uint32;

namespace T3D {

	class ViewPort
	{
	public:
		ViewPort() : x(0), y(0), width(800), height(600)
		{

		}

		ViewPort(uint32 sx, uint32 sy, uint32 w, uint32 h) : x(sx), y(sy), width(w), height(h)
		{

		}

		uint32 x;
		uint32 y;
		uint32 width;
		uint32 height;
	};

}

#endif // !__VIEWPORT_H__

