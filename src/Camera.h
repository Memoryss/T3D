#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Frustum.h>

namespace T3D {

	class Camera : public Frustum
	{
	public:

		void SetPosition(const Vec3 &pos);
		const Vec3 & GetPosition();

		void SetDirection(const Vec3 &dir);
		const Vec3 & GetDirection();

	protected:
		Vec3 m_pos;  //�������λ��
		Quaternion m_quat;  //�������ת��Ԫ��

	};

}

#endif
