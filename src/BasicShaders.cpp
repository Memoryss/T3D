#include "BasicShaders.h"

namespace T3D {

	void FlatShader::ProcessVertex(uint8* vOut, const uint8 vInRef)
	{
		Vec4 &pos = *(Vec4*)vInRef;
		Vec3 &nor = *(Vec3*)(sizeof(Vec4) + vInRef);
		Vec2 &texcoord = *(Vec2*)(sizeof(Vec4) + sizeof(Vec3) + vInRef);

		//保存世界坐标系的坐标
		Vec3 wPos = g_matrixs[SM_World] * pos;

		//转换到投影空间
		Vec4 *vPost = (Vec4*)vOut;
		*vPost = g_matrixs[SM_WorldViewProj] * pos;

		//法线转换到世界空间
		Vec3 wNor = g_matrixs[SM_World] * nor;
		wNor.Normalize();

		//计算光照颜色
		Color color;
		calcLights(wPos, wNor, color);

		Color *vColor = (Color*)(vOut + sizeof(Vec4));
		*vColor = color;

		Vec2 *vTexcoord = (Vec2*)(vOut + sizeof(Vec4) + sizeof(Vec2));
		*vTexcoord = texcoord;
	}

	void FlatShader::ProcessFragment(uint8 *vOut, const uint8 *vIn)
	{

	}
}
