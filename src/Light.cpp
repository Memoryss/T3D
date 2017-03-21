#include "Light.h"

namespace T3D {

	Light::Light(LightType type) : m_lightType(type), m_direction(0.f, 0.f, -1.f), m_radius(100.f), m_specularColor(1.f, 1.f, 1.f, 1.f), m_diffuseColor(1.f, 1.f, 1.f, 1.f), m_ambientColor(1.f, 1.f, 1.f, 1.f), m_isActive(true)
	{

	}

	float Light::GetRadius() const
	{
		return m_radius;
	}

	void Light::SetRadius(float radius)
	{
		m_radius = radius;
	}

	void Light::Active(bool val)
	{
		m_isActive = val;
	}

	bool Light::IsActive() const
	{
		return m_isActive;
	}

	LightType Light::GetLightType() const
	{
		return m_lightType;
	}

	void Light::SetDirection(const Vec3 & dir)
	{
		m_direction = dir;
	}

	const Vec3 & Light::GetDirection() const
	{
		return m_direction;
	}

	void Light::SetAmbientColor(const Color & color)
	{
		m_ambientColor = color;
	}

	const Color & Light::GetAmbientColor()
	{
		return m_ambientColor;
	}

	void Light::SetDiffuseColor(const Color & color)
	{
		m_diffuseColor = color;
	}

	const Color & Light::GetDiffuseColor()
	{
		return m_diffuseColor;
	}

	void Light::SetSpecularColor(const Color & color)
	{
		m_specularColor = color;
	}

	const Color & Light::GetSpecularColor()
	{
		return m_specularColor;
	}

	float Light::GetAmbientIntensity()
	{
		return m_ambientIntensity;
	}

	void Light::SetAmbientIntensity(float intensity)
	{
		m_ambientIntensity = intensity;
	}

	float Light::GetDiffuseIntensity()
	{
		return m_diffuseIntensity;
	}

	void Light::SetDiffuseIntensity(float intensity)
	{
		m_diffuseIntensity = intensity;
	}
}