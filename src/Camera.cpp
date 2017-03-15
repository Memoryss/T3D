#include "Camera.h"

namespace T3D {

	Camera::Camera() : Frustum()
	{
		init();
	}

	Camera::Camera(float fov, float aspect, float zNear, float zFar, ProjectionType type) : 
		Frustum(zNear, zFar, aspect, fov, type)
	{
		init();
	}

	void Camera::Update()
	{
		if (!m_dirty)
		{
			return;
		}

		UpdateFrustum(m_pos, m_quat);
		m_dirty = false;
	}

	void Camera::Pitch(float pitch)
	{
		Vec3 axis = Vec3::UNIT_X;
		Rotate(axis, pitch);
	}

	void Camera::Yaw(float yaw)
	{
		Vec3 axis = Vec3::UNIT_Y;
		Rotate(axis, yaw);
	}

	void Camera::Roll(float roll)
	{
		Vec3 axis = Vec3::UNIT_Z;
		Rotate(axis, roll);
	}

	void Camera::Rotate(const Vec3 &axis, float angle)
	{
		Quaternion quat(angle, axis);
		m_quat = quat * m_quat;
		m_dirty = true;
	}

	void Camera::init()
	{
		m_quat.Identity();
		m_projectionMatrix = Matrix44::IDENTITY;
		m_viewMatrix = Matrix44::IDENTITY;
		m_pos.setValue(0, 0, 0);
	}

}