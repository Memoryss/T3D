#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include <Plane.h>

namespace T3D {

	enum ProjectionType
	{
		PT_ORTHOGRAPHIC, //����ͶӰ
		PT_PERSPECTIVE, //͸��ͶӰ
	};

	enum FrustumPlaneType
	{
		FR_PLANE_NEAR = 0,
		FR_PLANE_FAR,
		FR_PLANE_RIGHT,
		FR_PLANE_LEFT,
		FR_PLANE_TOP,
		FR_PLANE_BOTTOM,
		FRUSTUM_PLANES
	};

	/************************************************************************/
	/* ��׶��                                                                     */
	/************************************************************************/
	class Frustum
	{
	public:
		Frustum();
		Frustum(const Frustum &rhs);
		Frustum(float near, float far, float xfov, float yfov, bool ortho = false);

		virtual ~Frustum();

		Frustum & operator=(const Frustum &rhs);

		bool operator==(const Frustum &rhs);

		void SetProjType(ProjectionType type);

	protected:
		void updateFrustum();

	protected:
		ProjectionType m_projType; //ͶӰ����

		float m_fov; //y�����fov
		float m_far; //Զ�ü���ľ���
		float m_near; //���ü���ľ���
		float m_aspect; //��߱�

		Plane m_planes[FRUSTUM_PLANES];
	};
}
#endif // !

