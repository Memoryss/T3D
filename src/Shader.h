#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <vector>

#include <Vector.h>
#include <Matrix.h>

#include "Light.h"
#include "Texture.h"

typedef unsigned char uint8;
typedef unsigned int uint32;

namespace T3D {

	class Texture;

	enum ShaderConstant
	{
		SC_CameraPos = 0,
		ShaderConstant_Count = 16,
	};
	
	enum ShaderMatrix
	{
		SM_WorldViewProj = 0,
		SM_World,
		SM_View,
		SM_Projection,
		SM_Count,
	};

	class Shader
	{
	public:
		virtual void ProcessVertex(uint8* vOut, const uint8 vInRef) = 0;
		virtual void ProcessRasterize() = 0;
		virtual void ProcessPixel() = 0;

	protected:
		static inline void calcLights(Vec3 &wPos, Vec3 &norDir, Vec3 &viewDir, Vec4 &diffuseAcc, Vec4 &specularAcc)
		{
			for (uint32 index = 0; index < g_lights.size(); ++index)
			{
				Light *lt = g_lights[index];
				Vec3 lightPos = lt->GetPosition();
				Vec3 lightDir = lightPos - wPos;
				lightDir.Normalize();

				float diffuse; //漫反射
				float specular;  //镜面反射
				Vec3 dir = lt->GetDirection();
			}
		}

	private:
		//平行光  没有衰减参数
		static inline void calcDirectionalLight()
		{

		}

	public:
		static Vec4 g_shaderContants[ShaderConstant_Count];
		static std::vector<Matrix44> g_matrixs;
		static std::vector<Texture *> g_textures;
		static std::vector<Light *> g_lights;
		static bool g_alphaTest;
		static bool g_culling;

	private:
		std::string m_name;
	};

}

#endif // !__SHADER_H__

