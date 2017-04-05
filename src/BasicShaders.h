#ifndef __BASICSHADERS_H__
#define __BASICSHADERS_H__

#include "Shader.h"

namespace T3D {

	//flat shaderר��������ݽṹ
	struct FlatShader_Output
	{
		Vec4 pos;
		Vec4 wPos;
		Vec3 normal;
		Vec2 texcoord;
	};

	//flat shader ÿ��������ϵ���ɫһ����û�в�ֵ
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
