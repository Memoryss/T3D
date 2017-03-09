#ifndef __MESH_H__
#define __MESH_H__

#include <string>

#include <Vector.h>

typedef unsigned int uint32;

namespace T3D {

	struct Vertex
	{
		Vec3 position;
		Vec3 normal;
		Vec2 texcoords;
		Vec3 tangent;
		Vec3 bitangent;
		Vec4 color;
	};

	//Í¼Ôª
	struct Face
	{
		Face():m_indices(NULL), m_numIndices(0){}

		~Face() { delete[]m_indices; }

		Face(const Face &f) : m_indices(NULL) { *this = f; }

		Face & operator=(const Face &f ) {
			if (&f == this) {
				return *this;
			}

			delete[] m_indices;
			m_numIndices = f.m_numIndices;
			if (m_numIndices) {
				m_indices = new uint32[m_numIndices];
				memcpy(m_indices, f.m_indices, m_numIndices * sizeof(uint32));
			}
			else {
				m_indices = NULL;
			}

			return *this;
		}

		bool operator==(const Face &f) {
			if (m_indices == f.m_indices)return true;
			else if (m_indices && m_numIndices == f.m_numIndices)
			{
				for (unsigned int i = 0; i < this->m_numIndices; ++i)
					if (m_indices[i] != o.m_indices[i])return false;
				return true;
			}
			return false;
		}

		uint32 m_numIndices;
		uint32 *m_indices;
	};

	class Mesh
	{
	public:
		void Draw(); //»æÖÆ

	private:
		Face *m_faces;
		uint32 m_numFaces;

	};

}

#endif // !__MESH_H__

