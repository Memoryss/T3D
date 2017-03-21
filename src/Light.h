#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Vector.h>

#include "Node.h"
#include "Color.h"

namespace T3D{

	enum LightType
	{
		Light_Direction = 0,
		Light_Point,
		Light_Spot,
	};

	class Light
	{
	public:

		Light(LightType type);

		float GetRadius() const;
		void SetRadius(float radius);

		//激活
		void Active(bool val);
		bool IsActive() const;

		LightType GetLightType() const;

		void SetDirection(const Vec3 &dir);
		const Vec3 & GetDirection() const;

		void SetAmbientColor(const Color &color);
		const Color & GetAmbientColor();

		void SetDiffuseColor(const Color &color);
		const Color & GetDiffuseColor();

		void SetSpecularColor(const Color &color);
		const Color & GetSpecularColor();

		void SetAmbientIntensity(float intensity);
		float GetAmbientIntensity();

		void SetDiffuseIntensity(float intensity);
		float GetDiffuseIntensity();

	private:

		LightType m_lightType;

		Vec3 m_direction;  //平行光使用
		float m_radius;

		Color m_ambientColor;
		Color m_diffuseColor;
		Color m_specularColor;

		float m_ambientIntensity;
		float m_diffuseIntensity;

		bool m_isActive;
	};

	class PointLight : public Light
	{
	public:
		PointLight();

		void SetPosition(const Vec3 &pos);
		const Vec3 & GetPosition();



	private:
		Vec3 m_pos;

		//float m_radius；
	};

	class DirectionLight : public Light
	{
	public:
		DirectionLight();

		void SetDirection(const Vec3 &pos);
		const Vec3 & GetDirection();

	private:
		Vec3 m_dir;
	};

}

#endif
