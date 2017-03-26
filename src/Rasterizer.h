#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <list>
#include "Mesh.h"

namespace T3D {

	class Rasterizer
	{
	public:

		static bool DrawLine()

	private:
		std::list <Face*> m_rendFaces;
	};

}

#endif