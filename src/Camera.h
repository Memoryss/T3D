#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Frustum.h>
#include <Quaternion.h>

#include "Node.h"

namespace T3D {

	//使用右手坐标系

	class Camera : public Frustum, public Node
	{
	public:

		Camera();

		Camera(float fov, float aspect, float zNear, float zFar, ProjectionType type);

		virtual void Update() override;

		/************************************************************************/
		/*	pitch绕x轴旋转，俯仰角
			yaw绕y轴旋转，偏航角
			roll绕z轴旋转，翻滚角														*/
		/************************************************************************/
		//单位：角度
		void Pitch(float pitch);

		void Yaw(float yaw);

		void Roll(float roll);
		
		void Rotate(const Vec3 &axis, float angle);

	private:
		void init();

	};

}

#endif
