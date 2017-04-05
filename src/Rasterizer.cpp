#include "Rasterizer.h"

#include <assert.h>

namespace T3D {



	bool Rasterizer::DrawPrimitive(const Primitive * pri)
	{
		return false;
	}

	//���øú�����ʱ�򣬶����Ѿ�ִ�й���͸��ͶӰ��ͶӰ�ռ�
	void Rasterizer::Rasterizer_Triangle_Clip(Primitive * tri)
	{
		// �ü��������ж���
#define CLIP_CODE_MORE_Z 0X0001 //z > z_max
#define CLIP_CODE_LESS_Z 0X0002 // z < z_min
#define CLIP_CODE_IN_Z 0X004 // z_min < z < z_max

#define CLIP_CODE_MORE_X 0X0001 //x > x_max
#define CLIP_CODE_LESS_X 0X0002 // x < x_min
#define CLIP_CODE_IN_X 0X004 // x_min < x < x_max

#define CLIP_CODE_MORE_Y 0X0001 //y > y_max
#define CLIP_CODE_LESS_Y 0X0002 // y < y_min
#define CLIP_CODE_IN_Y 0X004 // y_min < y < y_max

		//��ִ��͸�ӳ���  cvv(-1 ~ 1)
		for (uint32 index; index < tri->m_numIndices; ++index)
		{
			//͸�ӳ���
			auto &vertex = tri->m_vertics[tri->m_indices[index]];
			assert(vertex.position.w != 0);

			float w = vertex.position.z;
			vertex.position = vertex.position * (1 / vertex.position.w);
			vertex.position.w = vertex.position.w;
		}

		//cvv�ü�
		int vertex_flag[3];
		int num_vertexs_in_z; //�ж��м��������ڽ�ƽ����

		//�ü�x��
		auto &vertex0 = tri->m_vertics[tri->m_indices[0]];
		if (vertex0.position.x > 1.f)
			vertex_flag[0] = CLIP_CODE_MORE_X;
		else if (vertex0.position.x < -1.f)
			vertex_flag[0] = CLIP_CODE_LESS_X;
		else
			vertex_flag[0] = CLIP_CODE_IN_X;

		auto &vertex1 = tri->m_vertics[tri->m_indices[1]];
		if (vertex1.position.x > 1.f)
			vertex_flag[1] = CLIP_CODE_MORE_X;
		else if (vertex1.position.x < -1.f)
			vertex_flag[1] = CLIP_CODE_LESS_X;
		else
			vertex_flag[1] = CLIP_CODE_IN_X;

		auto &vertex2 = tri->m_vertics[tri->m_indices[2]];
		if (vertex2.position.x > 1.f)
			vertex_flag[2] = CLIP_CODE_MORE_X;
		else if (vertex2.position.x < -1.f)
			vertex_flag[2] = CLIP_CODE_LESS_X;
		else
			vertex_flag[2] = CLIP_CODE_IN_X;

		//X����ȫ������cvv֮�� ֱ���޳�
		if (vertex_flag[0] == CLIP_CODE_MORE_X && vertex_flag[1] == CLIP_CODE_MORE_X && vertex_flag[2] == CLIP_CODE_MORE_X
			|| vertex_flag[0] == CLIP_CODE_LESS_X && vertex_flag[1] == CLIP_CODE_LESS_X && vertex_flag[2] == CLIP_CODE_LESS_X)
			return;

		//�ü�Y����
		auto &vertex0 = tri->m_vertics[tri->m_indices[0]];
		if (vertex0.position.y > 1.f)
			vertex_flag[0] = CLIP_CODE_MORE_Y;
		else if (vertex0.position.y < -1.f)
			vertex_flag[0] = CLIP_CODE_LESS_Y;
		else
			vertex_flag[0] = CLIP_CODE_IN_Y;

		auto &vertex1 = tri->m_vertics[tri->m_indices[1]];
		if (vertex1.position.y > 1.f)
			vertex_flag[1] = CLIP_CODE_MORE_Y;
		else if (vertex1.position.y < -1.f)
			vertex_flag[1] = CLIP_CODE_LESS_Y;
		else
			vertex_flag[1] = CLIP_CODE_IN_Y;

		auto &vertex2 = tri->m_vertics[tri->m_indices[2]];
		if (vertex2.position.y > 1.f)
			vertex_flag[2] = CLIP_CODE_MORE_Y;
		else if (vertex2.position.y < -1.f)
			vertex_flag[2] = CLIP_CODE_LESS_Y;
		else
			vertex_flag[2] = CLIP_CODE_IN_Y;

		//Y����ȫ������cvv֮�� ֱ���޳�
		if (vertex_flag[0] == CLIP_CODE_MORE_Y && vertex_flag[1] == CLIP_CODE_MORE_Y && vertex_flag[2] == CLIP_CODE_MORE_Y
			|| vertex_flag[0] == CLIP_CODE_LESS_Y && vertex_flag[1] == CLIP_CODE_LESS_Y && vertex_flag[2] == CLIP_CODE_LESS_Y)
			return;

		//�ü�Z����
		auto &vertex0 = tri->m_vertics[tri->m_indices[0]];
		if (vertex0.position.z > 1.f)
			vertex_flag[0] = CLIP_CODE_MORE_Z;
		else if (vertex0.position.z < -1.f)
			vertex_flag[0] = CLIP_CODE_LESS_Z;
		else
		{
			++num_vertexs_in_z;
			vertex_flag[0] = CLIP_CODE_IN_Z;
		}

		auto &vertex1 = tri->m_vertics[tri->m_indices[1]];
		if (vertex1.position.z > 1.f)
			vertex_flag[1] = CLIP_CODE_MORE_Z;
		else if (vertex1.position.z < -1.f)
			vertex_flag[1] = CLIP_CODE_LESS_Z;
		else
		{
			++num_vertexs_in_z;
			vertex_flag[1] = CLIP_CODE_IN_Z;
		}

		auto &vertex2 = tri->m_vertics[tri->m_indices[2]];
		if (vertex2.position.z > 1.f)
			vertex_flag[2] = CLIP_CODE_MORE_Z;
		else if (vertex2.position.z < -1.f)
			vertex_flag[2] = CLIP_CODE_LESS_Z;
		else
		{
			++num_vertexs_in_z;
			vertex_flag[2] = CLIP_CODE_IN_Z;
		}

		//Y����ȫ������cvv֮�� ֱ���޳�
		if (vertex_flag[0] == CLIP_CODE_MORE_Z && vertex_flag[1] == CLIP_CODE_MORE_Z && vertex_flag[2] == CLIP_CODE_MORE_Z
			|| vertex_flag[0] == CLIP_CODE_LESS_Z && vertex_flag[1] == CLIP_CODE_LESS_Z && vertex_flag[2] == CLIP_CODE_LESS_Z)
			return;

		//��ʱ����x/y�����������вü�
		//���z���겻��Ҫ�ü� ֱ���ύ��դ�� Ȼ����ͶӰ����Ļ����вü�
		if (vertex_flag[0] == CLIP_CODE_IN_Z && vertex_flag[1] == CLIP_CODE_IN_Z && vertex_flag[2] == CLIP_CODE_IN_Z)
		{
			Rasterizer_Triangle(tri);
		}
		//�ж��Ƿ��е��ڽ�ƽ����
		else if ((vertex_flag[0] | vertex_flag[1] | vertex_flag[2]) & CLIP_CODE_LESS_X)
		{
			int v0, v1, v2;
			//���ֻ��һ���ڽ�ƽ���ڣ�ֱ�Ӳü�
			if (num_vertexs_in_z == 1)
			{
				//1.�ȼ����򣬰���׶����Ķ����ŵ���һ��
				if (vertex_flag[0] == CLIP_CODE_IN_Z)
				{
					v0 = 0;
					v1 = 1;
					v2 = 2;
				}
				else if (vertex_flag[1] == CLIP_CODE_IN_Z)
				{
					v0 = 1; v1 = 2; v2 = 0;
				}
				else
				{
					v0 = 2; v1 = 0; v2 = 1;
				}

				// 2.�ü�
				float ratio1 = ()
			}

		}
	}

	void Rasterizer::Rasterizer_Triangle(Primitive * tri)
	{
		auto &vertex0 = tri->m_vertics[tri->m_indices[0]];
		auto &vertex1 = tri->m_vertics[tri->m_indices[1]];
		auto &vertex2 = tri->m_vertics[tri->m_indices[2]];
		assert(vertex0.position.w != 0);
		assert(vertex1.position.w != 0);
		assert(vertex2.position.w != 0);

		//͸�ӳ��� ת����cvv��
		Vec3 side1 = vertex0.position.XYZ / vertex0.position.w - vertex1.position.XYZ / vertex1.position.w;
		Vec3 side2 = vertex1.position.XYZ / vertex1.position.w - vertex2.position.XYZ / vertex2.position.w;


	}

}