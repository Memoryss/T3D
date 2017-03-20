#include "BasicShaders.h"

void T3D::FlatShader::ProcessVertex(uint8* vOut, const uint8 vInRef)
{
	Vec4 &pos = *(Vec4*)vInRef;
	Vec3 &nor = *(Vec3*)(4 * sizeof(float) + vInRef);
	Vec2 &texcoord = *(Vec2*)(4 * sizeof(float) + vInRef);

	//������������ϵ������
	Vec3 wPos = g_matrixs[SM_World] * pos;

	//ת����ͶӰ�ռ�
	Vec4 *vPost = (Vec4*)vOut;
	*vPost = g_matrixs[SM_WorldViewProj] * pos;
	 
	//����ת��������ռ�
	Vec3 normal = g_matrixs[SM_World] * nor;
	normal.Normalize();

	Vec3 viewDir = g_shaderContants[SC_CameraPos].XYZ - wPos;
}
