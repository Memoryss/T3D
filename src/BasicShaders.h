#ifndef __BASICSHADERS_H__
#define __BASICSHADERS_H__

#include "Shader.h"

namespace T3D {

	//flat shader ÿ��������ϵ���ɫһ����û�в�ֵ
	class FlatShader : public Shader
	{
	public:

		FlatShader() : Shader("Flat") {}
		~FlatShader() {}

		virtual void ProcessVertex(uint8* vOut, const uint8 vInRef) override;
		virtual void ProcessFragment(uint8 *rOut, const uint8 *rIn) override;
	};

}

#endif
