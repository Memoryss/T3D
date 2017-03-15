#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <Frustum.h>
#include <Quaternion.h>

#include "Node.h"

namespace T3D {

	class Camera : public Frustum, public Node
	{
	public:

		Camera();

		Camera(float fov, float aspect, float zNear, float zFar, ProjectionType type);

		virtual void Update() override;

		/************************************************************************/
		/*	pitchÈÆxÖáĞı×ª£¬¸©Ñö½Ç
			yawÈÆyÖáĞı×ª£¬Æ«º½½Ç
			rollÈÆzÖáĞı×ª£¬·­¹ö½Ç														*/
		/************************************************************************/
		//µ¥Î»£º½Ç¶È
		void Pitch(float pitch);

		void Yaw(float yaw);

		void Roll(float roll);
		
		void Rotate(const Vec3 &axis, float angle);

	private:
		void init();

	};

}

#endif
