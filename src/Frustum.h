#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

namespace T3D {

	enum ProjectionType
	{
		PT_ORTHOGRAPHIC, //����ͶӰ
		PT_PERSPECTIVE, //͸��ͶӰ
	};

	/************************************************************************/
	/* ��׶��                                                                     */
	/************************************************************************/
	class Frustum
	{
	protected:
		ProjectionType m_projType; //ͶӰ����

		float m_fov; //��ֱ�����fov
		float m_far; //Զ�ü���ľ���
		float m_near; //���ü���ľ���
		float m_aspect; //��߱�

		Plane m_planes[6];
	};
}
#endif // !

