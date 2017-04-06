#include "Rasterizer.h"

#include <assert.h>

#include <TMath.h>

#include "Renderer.h"

namespace T3D {



	bool Rasterizer::DrawPrimitive(const Primitive * pri)
	{
		return false;
	}

	//调用该函数的时候，顶点已经执行过了透视投影  顶点在投影空间
	void Rasterizer::Rasterizer_Triangle_Clip(RastTriangle * tri, Shader *shader, float zNear, float zFar)
	{
		// 裁剪的区域判断码
#define CLIP_CODE_MORE_Z 0X0001 //z > z_max
#define CLIP_CODE_LESS_Z 0X0002 // z < z_min
#define CLIP_CODE_IN_Z 0X004 // z_min < z < z_max

#define CLIP_CODE_MORE_X 0X0001 //x > x_max
#define CLIP_CODE_LESS_X 0X0002 // x < x_min
#define CLIP_CODE_IN_X 0X004 // x_min < x < x_max

#define CLIP_CODE_MORE_Y 0X0001 //y > y_max
#define CLIP_CODE_LESS_Y 0X0002 // y < y_min
#define CLIP_CODE_IN_Y 0X004 // y_min < y < y_max

		//先执行透视除法  cvv(-1 ~ 1)
		for (uint32 index; index < 3; ++index)
		{
			//透视除法
			auto &vertex = tri->p[index];
			assert(vertex.pos.w != 0);

			float w = vertex.pos.z;
			vertex.pos = vertex.pos * (1 / vertex.pos.w);
			vertex.pos.w = vertex.pos.w;
		}

		//cvv裁剪
		int vertex_flag[3];
		int num_vertexs_in_z; //判断有几个顶点在近平面内

		//裁剪x轴
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

		//X坐标全部都在cvv之外 直接剔除
		if (vertex_flag[0] == CLIP_CODE_MORE_X && vertex_flag[1] == CLIP_CODE_MORE_X && vertex_flag[2] == CLIP_CODE_MORE_X
			|| vertex_flag[0] == CLIP_CODE_LESS_X && vertex_flag[1] == CLIP_CODE_LESS_X && vertex_flag[2] == CLIP_CODE_LESS_X)
			return;

		//裁剪Y坐标
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

		//Y坐标全部都在cvv之外 直接剔除
		if (vertex_flag[0] == CLIP_CODE_MORE_Y && vertex_flag[1] == CLIP_CODE_MORE_Y && vertex_flag[2] == CLIP_CODE_MORE_Y
			|| vertex_flag[0] == CLIP_CODE_LESS_Y && vertex_flag[1] == CLIP_CODE_LESS_Y && vertex_flag[2] == CLIP_CODE_LESS_Y)
			return;

		//裁剪Z坐标
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

		//Y坐标全部都在cvv之外 直接剔除
		if (vertex_flag[0] == CLIP_CODE_MORE_Z && vertex_flag[1] == CLIP_CODE_MORE_Z && vertex_flag[2] == CLIP_CODE_MORE_Z
			|| vertex_flag[0] == CLIP_CODE_LESS_Z && vertex_flag[1] == CLIP_CODE_LESS_Z && vertex_flag[2] == CLIP_CODE_LESS_Z)
			return;

		//暂时不对x/y方向的坐标进行裁剪
		//如果z坐标不需要裁剪 直接提交光栅化 然后在投影到屏幕后进行裁剪
		if (vertex_flag[0] == CLIP_CODE_IN_Z && vertex_flag[1] == CLIP_CODE_IN_Z && vertex_flag[2] == CLIP_CODE_IN_Z)
		{
			Rasterizer_Triangle(tri);
		}
		//判断是否有点在近平面内
		else if ((vertex_flag[0] | vertex_flag[1] | vertex_flag[2]) & CLIP_CODE_LESS_X)
		{
			int v0, v1, v2;
			//如果只有一个在近平面内，直接裁减  裁剪后只会有一个三角形
			if (num_vertexs_in_z == 1)
			{
				//1.先简单排序，把视锥里面的顶点排到第一个
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

				// 2.裁剪
				auto p0 = tri->p[v0];
				auto p1 = tri->p[v1];
				auto p2 = tri->p[v2];

				// FIXME DIVIDE 0
				assert(abs(p0.pos.w - p1.pos.w) > FLOAT_PRECISION);
				assert(abs(p0.pos.w - p2.pos.w) > FLOAT_PRECISION);

				float ratio1 = (p0.pos.w - zNear) / (p0.pos.w - p1.pos.w);
				float ratio2 = (p0.pos.w - zNear) / (p0.pos.w - p2.pos.w);
				
				//获得裁剪后的顶点
				shader->ProcessRasterizer(&p1, &tri->p[v0], &tri->p[v1], ratio1);
				shader->ProcessRasterizer(&p2, &tri->p[v0], &tri->p[v2], ratio2);
				
				tri->p[v1] = p1;
				tri->p[v2] = p2;

				//裁剪完毕，提交渲染 TODO
				Rasterizer_Triangle(tri);
			}
			else if (num_vertexs_in_z == 2)  //如果两个顶点在近裁减面上 则裁剪后会有两个三角形
			{
				//1.找出不在视锥体内部的顶点 重新排序
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

				//2.裁剪
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

				//3.构造新的三角形
				RastTriangle tri1 = *tri;
				RastTriangle tri2 = *tri;

				tri1.p[v0] = p3;

				tri2.p[v0] = p4;
				tri2.p[v1] = p3;

				//提交分割后的三角形
				Rasterizer_Triangle(&tri1);
				Rasterizer_Triangle(&tri2);
			}
		}
	}

	//已经进行过透视除法
	void Rasterizer::Rasterizer_Triangle(RastTriangle * tri)
	{
		//1.背面剔除
		assert(tri->p[0].pos.w > FLOAT_PRECISION);
		assert(tri->p[1].pos.w > FLOAT_PRECISION);
		assert(tri->p[2].pos.w > FLOAT_PRECISION);

		//计算法线
		Vec3 v0v1 = tri->p[1].pos.XYZ - tri->p[0].pos.XYZ;
		Vec3 v1v2 = tri->p[2].pos.XYZ - tri->p[1].pos.XYZ;
		v0v1.z = 0.f;  //只计算方向 与Z坐标无关，可置为0
		v1v2.z = 0.f;
		Vec3 nor = v0v1.Cross(v1v2);
		//法线朝向为-z 表示为背面，剔除
		if (nor.z < 0) return;

		//TODO 可以有个pitch shader

		//此时顶点在cvv中，需要转化到屏幕空间
		for (uint32 index = 0; index < 3; ++index)
		{
			auto &vertex = tri->p[index];
			vertex.pos.x = (vertex.pos.x * 0.5f + 0.5f) * m_renderer->GetViewPort().width;
			vertex.pos.y = ( - vertex.pos.y * 0.5f + 0.5f) * m_renderer->GetViewPort().height;

			//排序三角形
			//光栅化分为平顶和平底和不规则三角形
		}

	}

}