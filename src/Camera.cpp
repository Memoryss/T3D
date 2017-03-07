#include "Camera.h"

namespace T3D {

	void Camera::SetPosition(const Vec3 &pos)
	{
		m_dirty = true;
		m_pos = pos;
	}

	const Vec3 & Camera::GetPosition()
	{
		return m_pos;
	}

}