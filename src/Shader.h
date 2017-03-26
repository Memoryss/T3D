#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <vector>
#include <math.h>

#include <Vector.h>
#include <Matrix.h>

#include "Light.h"
#include "Texture.h"

typedef unsigned char uint8;
typedef unsigned int uint32;

namespace T3D {

	class Texture;

	enum ShaderVec4Constant
	{
		SV4C_CameraPos = 0,
		SV4C_SpecularPower,
		ShaderVec4Constant_Count,
	};
	
	enum ShaderFloatConstant
	{
		SFC_SpecularPower = 0,
		SFC_SpecularIntensity,
		ShaderFloatConstant_Count,
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
		virtual void ProcessFragment(uint8 *vOut, const uint8 *vIn) = 0;

	protected:
		static inline void calcLights(Vec3 &wPos, Vec3 &norDir, Color &color)
		{
			for (uint32 index = 0; index < g_lights.size(); ++index)
			{
				Light *lt = g_lights[index];
				switch (lt->GetLightType())
				{
				case Light_Direction:
					color += calcDirectionalLight(static_cast<DirectionLight*>(lt), wPos, norDir);
					break;
				case Light_Point:
					color += calcPointLight(static_cast<PointLight*>(lt), wPos, norDir);
					break;
				case Light_Spot:
					color += calcSpotLight(static_cast<SpotLight*>(lt), wPos, norDir);
					break;
				default:
					break;
				}
			}
		}

	private:

		static inline Color calcInternalLight(Light *light, const Vec3 &dir, const Vec3 &wPos, const Vec3 &normal)
		{
			Color ambientColor = light->GetAmbientColor();  //�������Ǿ���ģ��뷨�ߺͽǶ��޹�
			ambientColor *= light->GetAmbientIntensity();
			float diffuseFactor = normal.Dot(-dir);

			Color diffuseColor(0.f, 0.f, 0.f, 0.f);
			Color specularColor(0.f, 0.f, 0.f, 0.f);
			if (diffuseFactor > 0)
			{
				diffuseColor = light->GetDiffuseColor();
				diffuseColor *= light->GetDiffuseIntensity() * diffuseFactor;

				Vec3 vertexToEye = g_shaderVec4Contants[SV4C_CameraPos].XYZ - wPos;  //��ö��㵽���������
				vertexToEye.Normalize();

				Vec3 reflectDir = reflect(light->GetDirection(), normal);  //��÷��������
				reflectDir.Normalize();

				float specularFactor = vertexToEye.Dot(reflectDir);
				if (specularFactor > 0)
				{
					specularFactor = pow(specularFactor, g_shaderFloatContants[SFC_SpecularPower]);
					specularColor = light->GetSpecularColor();
					specularColor *= specularFactor * g_shaderFloatContants[SFC_SpecularIntensity];
				}
			}

			return specularColor + diffuseColor + ambientColor;
		}

		//ƽ�й�  û��˥������
		static inline Color calcDirectionalLight(DirectionLight *light, const Vec3 &wPos, const Vec3 &normal)
		{
			return calcInternalLight(light, light->GetDirection(), wPos, normal);
		}

		//���Դ
		static inline Color calcPointLight(PointLight *light, const Vec3 &wPos, const Vec3 &nor)
		{
			Vec3 lightDir = wPos - light->GetPosition();  //��ù�Դָ�򶥵������
			float distance = lightDir.Normalize();

			Color color = calcInternalLight(light, lightDir, wPos, nor); //�����˥���������color
			
			//���ݾ������˥��
			auto &att = light->GetAttenuation();
			float attenuation = att.m_constant + att.m_linear * distance + att.m_exp * distance * distance;
			return color / attenuation;
		}

		//�۹��  ������Χ�ⲻ����  ��Χ����Ϊ���Դ����
		static inline Color calcSpotLight(SpotLight *light, const Vec3 &wPos, const Vec3 &nor)
		{
			Vec3 lightToPoint = wPos - light->GetPosition();
			lightToPoint.Normalize();

			float spotFactor = lightToPoint.Dot(light->GetDirection());
			if (spotFactor > light->GetCutoff())
			{
				Color color = calcPointLight(light, wPos, nor);
				return color * (1 - (1 - spotFactor) / (1 - light->GetCutoff()));
			}
			else
			{
				return Color(0.f, 0.f, 0.f, 0.f);
			}
		}

		//���ط������� ���� ���������ͷ�������
		static inline Vec3 reflect(const Vec3 &dir, const Vec3 &nor)
		{
			float temp = 2 * dir.Dot(nor);
			return dir - nor * temp;
		}

	public:
		static Vec4 g_shaderVec4Contants[ShaderVec4Constant_Count];
		static float g_shaderFloatContants[ShaderFloatConstant_Count];
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

