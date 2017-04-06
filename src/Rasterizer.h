#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <list>
#include "Mesh.h"

namespace T3D {

	class Renderer;
	class Shader;

	//��Ⱦ����ṹ�壬ʹ��Primitive�����µĶ���  ������opengl��layout��װ�Ľṹ��	TODO��ʱ֧������ͨ��
	struct RenderVertex
	{
		Vec4 pos;

		Vec4 channel1;
		Vec4 channel2;
		Vec4 channel3;
	};

	struct RastTriangle
	{
		RenderVertex p[3];
		//Primitive *primitive;
	};


	//Ĭ����ʱ��Ϊ���棬�޳�����  ������ռ���У�-z�������ſɼ�����˷��߳�����+z���������
	class Rasterizer
	{
	public:

		bool DrawPrimitive(const Primitive *pri);

		//�������ν�����׶�Ĳü������ύ
		//znear��zfar�������ǲü���ֵʹ��
		//TODO ��ʱ�ֽ�ʹ�õ�shader������
		static void Rasterizer_Triangle_Clip(RastTriangle *tri, Shader *shader, float zNear, float zFar);

		static void Rasterizer_Triangle(RastTriangle *tri);

		static bool DrawLine();

	public:
		static Renderer *m_renderer;

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