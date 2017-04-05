#ifndef __BASICSHADERS_H__
#define __BASICSHADERS_H__

#include "Shader.h"

namespace T3D {

	//flat shader专用输出数据结构
	struct FlatShader_Output
	{
		Vec4 pos;
		Vec4 wPos;
		Vec3 normal;
		Vec2 texcoord;
	};

	//flat shader 每个多边形上的颜色一样，没有插值
	class FlatShader : public Shader
	{
	public:

		FlatShader() : Shader("Flat") {}
		~FlatShader() {}

		virtual void ProcessVertex(void *vOut, const void *vInRef) override;
		virtual void ProcessRasterizer(void *vOut, const void *vInRef0, const void *vInRef1, float ratio) override;
		virtual void ProcessFragment(void *rOut, const void *rIn) override;
	};

}

#endif
