#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Vector.h>

#include "Color.h"

namespace T3D{

	enum LightType
	{
		LIGHT_Directional = 0,
		LIGHT_Point,
		LIGHT_Spot,
	};

	class Light : 
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

		//以后可以抽象出来的
		void SetVisible(bool visible);
		bool IsVisible() const;

	private:

		LightType m_lightType;

		Vec3 m_direction;
		Vec3 m_worldPos;
		float m_radius;

		Color m_ambientColor;
		Color m_diffuseColor;
		Color m_specularColor;

		//以后可以抽象出来的
		bool m_isVisible;

		bool m_isActive;
	};

}

#endif
