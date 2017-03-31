#include "Rasterizer.h"

#include <assert.h>

namespace T3D {



	bool Rasterizer::DrawPrimitive(const Primitive * pri)
	{
		return false;
	}

	void Rasterizer::Rasterizer_Triangle(const Primitive * tri)
	{
		auto &vertex0 = tri->m_vertics[tri->m_indices[0]];
		auto &vertex1 = tri->m_vertics[tri->m_indices[1]];
		auto &vertex2 = tri->m_vertics[tri->m_indices[2]];
		assert(vertex0.position.w != 0);
		assert(vertex1.position.w != 0);
		assert(vertex2.position.w != 0);

		//透视除法 转换到cvv中
		Vec3 side1 = vertex0.position.XYZ / vertex0.position.w - vertex1.position.XYZ / vertex1.position.w;
		Vec3 side2 = vertex1.position.XYZ / vertex1.position.w - vertex2.position.XYZ / vertex2.position.w;


	}

}