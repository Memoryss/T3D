#include "Camera.h"

namespace T3D {

	void Camera::Update()
	{
		if (m_dirty) {
			UpdateFrustum(m_pos, m_quat);
		}
	}

	void Camera::SetPosition(const Vec3 &pos)
	{
		m_dirty = true;
		m_pos = pos;
	}

	const Vec3 & Camera::GetPosition()
	{
		return m_pos;
	}

	void Camera::SetRotate(const Quaternion &quat)
	{
		m_quat = quat;
		m_dirty = true;
	}

	void Camera::Rotate(float pitch, float yaw, float roll)
	{
		Quaternion xquat(pitch, Vec3::UNIT_X);
		Quaternion yquat(yaw, Vec3::UNIT_Y);
		Quaternion zquat(roll, Vec3::UNIT_Z);


	}

}