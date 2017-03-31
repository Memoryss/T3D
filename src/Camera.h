#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Frustum.h>
#include <Quaternion.h>

#include "Node.h"

namespace T3D {

	//ʹ����������ϵ

	class Camera : public Frustum, public Node
	{
	public:

		Camera();

		Camera(float fov, float aspect, float zNear, float zFar, ProjectionType type);

		virtual void Update() override;

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

	};

}

#endif
