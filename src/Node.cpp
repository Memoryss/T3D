#include "Node.h"

namespace T3D {

	void Node::SetPosition(const Vec3 & pos)
	{
		m_pos = pos;
		m_dirty = true;
	}

	const Vec3 & Node::GetPosition()
	{
		if (m_dirty)
		{
			m_dirty = false;
			Update();
		}

		return m_pos;
	}

	void Node::SetRotate(const Quaternion & quat)
	{
		m_quat = quat;
		m_dirty = true;
	}

	const Quaternion & Node::GetRotate()
	{
		if (m_dirty)
		{
			m_dirty = false;
			Update();
		}

		return m_quat;
	}

	void Node::SetVisible(bool visible)
	{
		m_isVisible = true;
	}

	bool Node::IsVisible()
	{
		return m_isVisible;
	}

}