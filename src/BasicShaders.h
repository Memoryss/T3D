#ifndef __BASICSHADERS_H__
#define __BASICSHADERS_H__

#include "Shader.h"

namespace T3D {

	class FlatShader : public Shader
	{
	public:

		FlatShader() : Shader("Flat") {}
		~FlatShader() {}

		virtual void ProcessVertex(uint8* vOut, const uint8 vInRef) override;

	};

}

#endif
