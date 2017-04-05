#include "BasicShaders.h"

namespace T3D {

	void FlatShader::ProcessVertex(void *vOut, const void *vInRef)
	{
		VertexP4N3T2 *in = (VertexP4N3T2*)vInRef;
		FlatShader_Output *out = (FlatShader_Output*)vOut;
		//������������ϵ������
		out->wPos = g_matrixs[SM_World] * in->pos;

		//ת����ͶӰ�ռ�
		out->pos = g_matrixs[SM_WorldViewProj] * in->pos;

		//����ת��������ռ�
		out->normal = g_matrixs[SM_World] * in->normal;
		out->normal.Normalize();
		out->texcoord = in->texcoord;
	}

	void FlatShader::ProcessRasterizer(void * vOut, const void * vInRef0, const void * vInRef1, float ratio)
	{
		auto ver0 = (FlatShader_Output*)(vInRef0);
		auto ver1 = (FlatShader_Output*)(vInRef1);

		auto ver = (FlatShader_Output*)(vOut);

		//��ò�ֵ�Ķ���
		ver->pos = Math::FastLerp(ver0->pos, ver1->pos, ratio);
		ver->wPos = Math::FastLerp(ver0->wPos, ver1->wPos, ratio);
		ver->normal = Math::FastLerp(ver0->normal, ver1->normal, ratio);
		ver->texcoord = Math::FastLerp(ver0->texcoord, ver1->texcoord, ratio);
	}

	void FlatShader::ProcessFragment(void *vOut, const void *vIn)
	{
		const FlatShader_Output *in = (FlatShader_Output*)vIn;

		//���������ɫ
		Color color;
		calcLights(in->wPos, in->normal, color);

		//out->color = color;
	}
}
