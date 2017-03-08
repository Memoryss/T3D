#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Frustum.h>
#include <Quaternion.h>

namespace T3D {

	class Camera : public Frustum
	{
	public:

		void Update();

		void SetPosition(const Vec3 &pos);
		const Vec3 & GetPosition();

		void SetRotate(const Quaternion &dir);

		/************************************************************************/
		/*	pitch��x����ת��������
			yaw��y����ת��ƫ����
			roll��z����ת��������														*/
		/************************************************************************/
		void Rotate(float pitch, float yaw, float roll);

	protected:
		Vec3 m_pos;  //�������λ��
		Quaternion m_quat;  //�������ת��Ԫ��

		bool m_dirty = false;  //�Ƿ���Ҫ����Frustum

	};

}

#endif
