#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Frustum.h>
#include <Quaternion.h>

namespace T3D {

	class Camera : public Frustum
	{
	public:

		Camera();

		void Update();

		void SetPosition(const Vec3 &pos);
		const Vec3 & GetPosition();

		void SetRotate(const Quaternion &dir);

		/************************************************************************/
		/*	pitch��x����ת��������
			yaw��y����ת��ƫ����
			roll��z����ת��������														*/
		/************************************************************************/
		//��λ���Ƕ�
		void Pitch(float pitch);

		void Yaw(float yaw);

		void Roll(float roll);
		
		void Rotate(const Vec3 &axis, float angle);

	private:
		void init();

	protected:
		Vec3 m_pos;  //�������λ��
		Quaternion m_quat;  //�������ת��Ԫ��

		bool m_dirty = false;  //�Ƿ���Ҫ����Frustum

	};

}

#endif
