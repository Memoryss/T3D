#include "Rasterizer.h"

#include <assert.h>

#include <TMath.h>

#include "Renderer.h"

namespace T3D {



	bool Rasterizer::DrawPrimitive(const Primitive * pri)
	{
		return false;
	}

	//���øú�����ʱ�򣬶����Ѿ�ִ�й���͸��ͶӰ  ������ͶӰ�ռ�
	void Rasterizer::Rasterizer_Triangle_Clip(RastTriangle * tri, Shader *shader, float zNear, float zFar)
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
		for (uint32 index; index < 3; ++index)
		{
			//͸�ӳ���
			auto &vertex = tri->p[index];
			assert(vertex.pos.w != 0);

			float w = vertex.pos.z;
			vertex.pos = vertex.pos * (1 / vertex.pos.w);
			vertex.pos.w = vertex.pos.w;
		}

		//cvv�ü�
		int vertex_flag[3];
		int num_vertexs_in_z; //�ж��м��������ڽ�ƽ����

		//�ü�x��
		auto &vertex0 = tri->p[0];
		if (vertex0.pos.x > 1.f)
			vertex_flag[0] = CLIP_CODE_MORE_X;
		else if (vertex0.pos.x < -1.f)
			vertex_flag[0] = CLIP_CODE_LESS_X;
		else
			vertex_flag[0] = CLIP_CODE_IN_X;

		auto &vertex1 = tri->p[1];
		if (vertex1.pos.x > 1.f)
			vertex_flag[1] = CLIP_CODE_MORE_X;
		else if (vertex1.pos.x < -1.f)
			vertex_flag[1] = CLIP_CODE_LESS_X;
		else
			vertex_flag[1] = CLIP_CODE_IN_X;

		auto &vertex2 = tri->p[2];
		if (vertex2.pos.x > 1.f)
			vertex_flag[2] = CLIP_CODE_MORE_X;
		else if (vertex2.pos.x < -1.f)
			vertex_flag[2] = CLIP_CODE_LESS_X;
		else
			vertex_flag[2] = CLIP_CODE_IN_X;

		//X����ȫ������cvv֮�� ֱ���޳�
		if (vertex_flag[0] == CLIP_CODE_MORE_X && vertex_flag[1] == CLIP_CODE_MORE_X && vertex_flag[2] == CLIP_CODE_MORE_X
			|| vertex_flag[0] == CLIP_CODE_LESS_X && vertex_flag[1] == CLIP_CODE_LESS_X && vertex_flag[2] == CLIP_CODE_LESS_X)
			return;

		//�ü�Y����
		auto &vertex0 = tri->p[0];
		if (vertex0.pos.y > 1.f)
			vertex_flag[0] = CLIP_CODE_MORE_Y;
		else if (vertex0.pos.y < -1.f)
			vertex_flag[0] = CLIP_CODE_LESS_Y;
		else
			vertex_flag[0] = CLIP_CODE_IN_Y;

		auto &vertex1 = tri->p[1];
		if (vertex1.pos.y > 1.f)
			vertex_flag[1] = CLIP_CODE_MORE_Y;
		else if (vertex1.pos.y < -1.f)
			vertex_flag[1] = CLIP_CODE_LESS_Y;
		else
			vertex_flag[1] = CLIP_CODE_IN_Y;

		auto &vertex2 = tri->p[2];
		if (vertex2.pos.y > 1.f)
			vertex_flag[2] = CLIP_CODE_MORE_Y;
		else if (vertex2.pos.y < -1.f)
			vertex_flag[2] = CLIP_CODE_LESS_Y;
		else
			vertex_flag[2] = CLIP_CODE_IN_Y;

		//Y����ȫ������cvv֮�� ֱ���޳�
		if (vertex_flag[0] == CLIP_CODE_MORE_Y && vertex_flag[1] == CLIP_CODE_MORE_Y && vertex_flag[2] == CLIP_CODE_MORE_Y
			|| vertex_flag[0] == CLIP_CODE_LESS_Y && vertex_flag[1] == CLIP_CODE_LESS_Y && vertex_flag[2] == CLIP_CODE_LESS_Y)
			return;

		//�ü�Z����
		auto &vertex0 = tri->p[0];
		if (vertex0.pos.z > 1.f)
			vertex_flag[0] = CLIP_CODE_MORE_Z;
		else if (vertex0.pos.z < -1.f)
			vertex_flag[0] = CLIP_CODE_LESS_Z;
		else
		{
			++num_vertexs_in_z;
			vertex_flag[0] = CLIP_CODE_IN_Z;
		}

		auto &vertex1 = tri->p[1];
		if (vertex1.pos.z > 1.f)
			vertex_flag[1] = CLIP_CODE_MORE_Z;
		else if (vertex1.pos.z < -1.f)
			vertex_flag[1] = CLIP_CODE_LESS_Z;
		else
		{
			++num_vertexs_in_z;
			vertex_flag[1] = CLIP_CODE_IN_Z;
		}

		auto &vertex2 = tri->p[2];
		if (vertex2.pos.z > 1.f)
			vertex_flag[2] = CLIP_CODE_MORE_Z;
		else if (vertex2.pos.z < -1.f)
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
			//���ֻ��һ���ڽ�ƽ���ڣ�ֱ�Ӳü�  �ü���ֻ����һ��������
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
				auto p0 = tri->p[v0];
				auto p1 = tri->p[v1];
				auto p2 = tri->p[v2];

				// FIXME DIVIDE 0
				assert(abs(p0.pos.w - p1.pos.w) > FLOAT_PRECISION);
				assert(abs(p0.pos.w - p2.pos.w) > FLOAT_PRECISION);

				float ratio1 = (p0.pos.w - zNear) / (p0.pos.w - p1.pos.w);
				float ratio2 = (p0.pos.w - zNear) / (p0.pos.w - p2.pos.w);
				
				//��òü���Ķ���
				shader->ProcessRasterizer(&p1, &tri->p[v0], &tri->p[v1], ratio1);
				shader->ProcessRasterizer(&p2, &tri->p[v0], &tri->p[v2], ratio2);
				
				tri->p[v1] = p1;
				tri->p[v2] = p2;

				//�ü���ϣ��ύ��Ⱦ TODO
				Rasterizer_Triangle(tri);
			}
			else if (num_vertexs_in_z == 2)  //������������ڽ��ü����� ��ü����������������
			{
				//1.�ҳ�������׶���ڲ��Ķ��� ��������
				if (vertex_flag[0] == CLIP_CODE_LESS_Z)
				{
					v0 = 0; v1 = 1; v2 = 2;
				}
				else if (vertex_flag[1] == CLIP_CODE_LESS_Z)
				{
					v0 = 1; v1 = 2; v2 = 0;
				}
				else
				{
					v0 = 2; v1 = 0; v2 = 1;
				}

				//2.�ü�
				auto p0 = tri->p[v0];
				auto p1 = tri->p[v1];
				auto p2 = tri->p[v2];

				auto p3 = p1;
				auto p4 = p2;

				assert(p1.pos.w - p0.pos.w > FLOAT_PRECISION);
				assert(p2.pos.w - p0.pos.w > FLOAT_PRECISION);

				float ratio1 = (zNear - p0.pos.w) / (p1.pos.w - p0.pos.w);
				float ratio2 = (zNear - p0.pos.w) / (p2.pos.w - p0.pos.w);

				shader->ProcessRasterizer(&p3, &tri->p[v0], &tri->p[v1], ratio1);
				shader->ProcessRasterizer(&p4, &tri->p[v0], &tri->p[v2], ratio2);

				//3.�����µ�������
				RastTriangle tri1 = *tri;
				RastTriangle tri2 = *tri;

				tri1.p[v0] = p3;

				tri2.p[v0] = p4;
				tri2.p[v1] = p3;

				//�ύ�ָ���������
				Rasterizer_Triangle(&tri1);
				Rasterizer_Triangle(&tri2);
			}
		}
	}

	//�Ѿ����й�͸�ӳ���
	void Rasterizer::Rasterizer_Triangle(RastTriangle * tri)
	{
		//1.�����޳�
		assert(tri->p[0].pos.w > FLOAT_PRECISION);
		assert(tri->p[1].pos.w > FLOAT_PRECISION);
		assert(tri->p[2].pos.w > FLOAT_PRECISION);

		//���㷨��
		Vec3 v0v1 = tri->p[1].pos.XYZ - tri->p[0].pos.XYZ;
		Vec3 v1v2 = tri->p[2].pos.XYZ - tri->p[1].pos.XYZ;
		v0v1.z = 0.f;  //ֻ���㷽�� ��Z�����޹أ�����Ϊ0
		v1v2.z = 0.f;
		Vec3 nor = v0v1.Cross(v1v2);
		//���߳���Ϊ-z ��ʾΪ���棬�޳�
		if (nor.z < 0) return;

		//TODO �����и�pitch shader

		//��ʱ������cvv�У���Ҫת������Ļ�ռ�
		for (uint32 index = 0; index < 3; ++index)
		{
			auto &vertex = tri->p[index];
			vertex.pos.x = (vertex.pos.x * 0.5f + 0.5f) * m_renderer->GetViewPort().width;
			vertex.pos.y = ( - vertex.pos.y * 0.5f + 0.5f) * m_renderer->GetViewPort().height;

			//����������
			//��դ����Ϊƽ����ƽ�׺Ͳ�����������
		}

	}

}