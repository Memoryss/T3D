#include "BasicShaders.h"

namespace T3D {

	void FlatShader::ProcessVertex(uint8* vOut, const uint8 vInRef)
	{
		Vec4 &pos = *(Vec4*)vInRef;
		Vec3 &nor = *(Vec3*)(sizeof(Vec4) + vInRef);
		Vec2 &texcoord = *(Vec2*)(sizeof(Vec4) + sizeof(Vec3) + vInRef);

		//������������ϵ������
		Vec3 wPos = g_matrixs[SM_World] * pos;

		//ת����ͶӰ�ռ�
		Vec4 *vPost = (Vec4*)vOut;
		*vPost = g_matrixs[SM_WorldViewProj] * pos;

		//����ת��������ռ�
		Vec3 wNor = g_matrixs[SM_World] * nor;
		wNor.Normalize();

		//���������ɫ
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
