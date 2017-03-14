#ifndef __NODE_H__
#define __NODE_H__

#include <Vector.h>
#include <Quaternion.h>

namespace T3D {

	class Node
	{
	public:

		void SetPosition(const Vec3 &pos);
		CO

	private:
		Vec3 m_pos;

		Quaternion m_quat;
	};

}

#endif
