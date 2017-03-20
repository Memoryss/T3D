#include "BasicShaders.h"

void T3D::FlatShader::ProcessVertex(uint8* vOut, const uint8 vInRef)
{
	Vec4 &pos = *(Vec4*)vInRef;
	Vec3 &nor = *(Vec3*)(4 * sizeof(float) + vInRef);
	Vec2 &texcoord = *(Vec2*)(4 * sizeof(float) + vInRef);

	//保存世界坐标系的坐标
	Vec3 wPos = g_matrixs[SM_World] * pos;

	//转换到投影空间
	Vec4 *vPost = (Vec4*)vOut;
	*vPost = g_matrixs[SM_WorldViewProj] * pos;
	 
	//法线转换到世界空间
	Vec3 normal = g_matrixs[SM_World] * nor;
	normal.Normalize();

	Vec3 viewDir = g_shaderContants[SC_CameraPos].XYZ - wPos;
}
