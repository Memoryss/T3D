#ifndef __NODE_H__
#define __NODE_H__

#include <Vector.h>
#include <Quaternion.h>

namespace T3D {

	class Node
	{
	public:

		void SetPosition(const Vec3 &pos);
		const Vec3 & GetPosition();
		
		void SetRotate(const Quaternion &quat);
		const Quaternion & GetRotate();

		void SetVisible(bool visible);
		bool IsVisible();

		virtual void Update() = 0;

	protected:
		Vec3 m_pos;
		Vec3 m_scale;
		Quaternion m_quat;

		bool m_isVisible;
		bool m_dirty;
	};

}

#endif
