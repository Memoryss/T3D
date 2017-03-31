#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <list>
#include "Mesh.h"

namespace T3D {

	class Rasterizer
	{
	public:

		bool DrawPrimitive(const Primitive *pri);

		static void Rasterizer_Triangle(const Primitive *tri);

		static bool DrawLine();

	private:
		//光栅化函数
		static void rasterizer_Top_Triangle(const Primitive *topTri);
		static void rasterizer_Bottom_Triangle(const Primitive *bottoomTri);

	private:
		//Primitive 假定为三角形 后续根据需要处理其他形状的渲染 TODO
		std::list <Primitive*> m_rendPrimitives;
	};

}

#endif