#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <vector>
#include <string>
#include <assert.h>

#include <Vector.h>

typedef unsigned int uint32;

namespace T3D {

	class Vertex
	{
		Vec3 m_position;
		Vec3 m_normal;
		Vec2 m_texcoords;
	};

	class VertexBuffer
	{
		Vertex *m_data; //¶¥µãÊý¾Ý
		uint32 m_count;

		VertexBuffer()
		{
			memset(m_data, 0, sizeof(VertexBuffer));
		}

		void SetData(void *srcData, uint32 index, uint32 size)
		{
			if (index < m_count && m_data != NULL)
			{
				memcpy(m_data + index * sizeof(Vertex), srcData, size);
				m_count = size;
			}
		}
	};

	class IndexBuffer
	{
		uint32 *m_indices;
		uint32 m_count;
		uint32 m_currAddr;

		void SetData(uint32 srcData, uint32 index)
		{
			if (index < m_count && m_indices != NULL)
			{
				m_indices[index] = srcData;
			}
		}

		void Clear()
		{
			memset(m_indices, 0, m_count * sizeof(uint32));
			m_currAddr = 0;
		}

		void Push_back(uint32 index)
		{
			m_indices[m_currAddr++] = index;
			assert(m_currAddr <= m_count);
		}

		uint32 Size()
		{
			return m_currAddr;
		}
	};

}

#endif
