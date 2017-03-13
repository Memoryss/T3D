#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <list>
#include "Mesh.h"

namespace T3D {

	class Rasterizer
	{
	public:

		static bool Clip_Line();
		static bool Draw_Line();
		static bool Draw_Clip_Line();

	private:
		std::list <Face*> m_rendFaces;
	};

}

#endif