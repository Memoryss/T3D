#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Vector.h>

#include "Node.h"
#include "Color.h"

namespace T3D{

	enum LightType
	{
		LIGHT_Directional = 0,
		LIGHT_Point,
		LIGHT_Spot,
	};

	class Light : public Node
	{
	public:

		Light(LightType type);

		float GetRadius() const;
		void SetRadius(float radius);

		//¼¤»î
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

	private:

		LightType m_lightType;

		Vec3 m_direction;
		float m_radius;

		Color m_ambientColor;
		Color m_diffuseColor;
		Color m_specularColor;

		bool m_isActive;
	};

}

#endif
