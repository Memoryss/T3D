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
		/*	pitch绕x轴旋转，俯仰角
			yaw绕y轴旋转，偏航角
			roll绕z轴旋转，翻滚角														*/
		/************************************************************************/
		void Rotate(float pitch, float yaw, float roll);

	protected:
		Vec3 m_pos;  //相机坐在位置
		Quaternion m_quat;  //相机的旋转四元数

		bool m_dirty = false;  //是否需要更新Frustum

	};

}

#endif
