#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

namespace T3D {

	enum ProjectionType
	{
		PT_ORTHOGRAPHIC, //正交投影
		PT_PERSPECTIVE, //透视投影
	};

	/************************************************************************/
	/* 视锥体                                                                     */
	/************************************************************************/
	class Frustum
	{
	protected:
		ProjectionType m_projType; //投影类型

		float m_fov; //垂直方向的fov
		float m_far; //远裁剪面的距离
		float m_near; //近裁剪面的距离
		float m_aspect; //宽高比

		Plane m_planes[6];
	};
}
#endif // !

