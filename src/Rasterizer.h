#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <list>
#include "Mesh.h"

namespace T3D {

	class Rasterizer
	{
	public:

		bool DrawPrimitive(const Primitive *pri);

		//�������ν�����׶�Ĳü������ύ
		static void Rasterizer_Triangle_Clip(Primitive *tri);

		static void Rasterizer_Triangle(Primitive *tri);

		static bool DrawLine();

	private:
		//��դ������
		static void rasterizer_Top_Triangle(const Primitive *topTri);
		static void rasterizer_Bottom_Triangle(const Primitive *bottoomTri);

	private:
		//Primitive �ٶ�Ϊ������ ����������Ҫ����������״����Ⱦ TODO
		std::list <Primitive*> m_rendPrimitives;
	};

}

#endif