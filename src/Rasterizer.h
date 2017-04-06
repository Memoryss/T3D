#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <list>
#include "Mesh.h"

namespace T3D {

	class Renderer;
	class Shader;

	//渲染顶点结构体，使用Primitive构造新的顶点  类似于opengl的layout组装的结构体	TODO暂时支持三个通道
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


	//默认逆时针为正面，剔除背面  在相机空间的中，-z轴的物体才可见，因此法线朝向是+z轴才是正面
	class Rasterizer
	{
	public:

		bool DrawPrimitive(const Primitive *pri);

		//对三角形进行视锥的裁剪，并提交
		//znear和zfar的作用是裁剪插值使用
		//TODO 暂时现将使用的shader传进来
		static void Rasterizer_Triangle_Clip(RastTriangle *tri, Shader *shader, float zNear, float zFar);

		static void Rasterizer_Triangle(RastTriangle *tri);

		static bool DrawLine();

	public:
		static Renderer *m_renderer;

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