#include "T3DCamera.h"

#include <math.h>

T3D::Camera::Camera(int cam_attr, Vec4 cam_pos, Vec4 cam_dir, Vec4 cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height)
{
	m_attr = cam_attr;
	m_pos.InitWithVec4(cam_pos);
	m_dir.InitWithVec4(cam_dir);

	//uvn
	m_u.InitXYZW(1.0f, 0.0f, 0.0f, 1.0f);
	m_n.InitXYZW(0.0f, 1.0f, 0.0f, 1.0f);
	m_v.InitXYZW(0.0f, 1.0f, 0.0f, 1.0f);
	m_target.InitWithVec4(cam_target);

	m_near_clip_z = near_clip_z;
	m_far_clip_z = far_clip_z;

	m_viewport_width = viewport_width;
	m_viewport_height = viewport_height;
	m_viewport_center_x = (viewport_width - 1) / 2.0f;
	m_viewport_center_y = (viewport_height - 1) / 2.0f;
	m_aspect_ratio = float(m_viewport_width) / m_viewport_height;

	//�����еľ�����Ϊ��λ����
	m_cam.Identity();
	m_per.Identity();
	m_scr.Identity();

	m_fov = fov;

	// ��ƽ���С��Ϊ2 * (2 / ar)
	m_viewplane_width = 2.0f;
	m_viewplane_height = 2.0f / m_aspect_ratio;

	//����fov����ƽ��Ĵ�С�����Ӿࡢ
	float tan_for_div2 = tanf(DEG_TO_RAN(fov / 2));
	m_view_dist = (0.5) 
}
