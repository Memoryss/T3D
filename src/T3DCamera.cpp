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

	//将所有的矩阵设为单位矩阵
	m_cam.Identity();
	m_per.Identity();
	m_scr.Identity();

	m_fov = fov;

	// 视平面大小设为2 * (2 / ar)
	m_viewplane_width = 2.0f;
	m_viewplane_height = 2.0f / m_aspect_ratio;

	//根据fov和视平面的大小计算视距、
	float tan_for_div2 = tanf(DEG_TO_RAN(fov / 2));
	m_view_dist = (0.5) * m_viewplane_width / tan_for_div2;

	//判断fov是否是90度
	if (m_fov == 90.0f)
	{
		//建立裁剪面
		Vec3 point;
		point.InitZero();

		Vec3 normal;  //normal to plane

		//right plane
		normal.InitXYZ(1.0f, 0.0f, -1.0f);   //x-z
		CommonMath::Plane3DInit(m_rt_clip_plane, point, normal, 1);

		//left plane
		normal.InitXYZ(-1.0f, 0.0f, -1.0f);  //x-z
		CommonMath::Plane3DInit(m_lt_clip_plane, point, normal, 1);

		//top plane
		normal.InitXYZ(0.0f, 1.0f, -1.0f); //y-z
		CommonMath::Plane3DInit(m_tp_clip_plane, point, normal, 1);

		//bottom plane
		normal.InitXYZ(0.0f, -1.0f, -1.0f); //y-z
		CommonMath::Plane3DInit(m_bt_clip_plane, point, normal, 1);
	} // end if
	else
	{
		Vec3 point;
		point.InitZero();

		Vec3 normal;

		//right plane
		normal.InitXYZ(1.0f, 0.0f, -tan_for_div2);  //x-z
		CommonMath::Plane3DInit(m_rt_clip_plane, point, normal, 1);

		//left plane
		normal.InitXYZ(-1.0f, 0.0f, -tan_for_div2);  //x-z
		CommonMath::Plane3DInit(m_lt_clip_plane, point, normal, 1);

		//top plane
		normal.InitXYZ(0.0f, 1.0f, -tan_for_div2); //y-z
		CommonMath::Plane3DInit(m_tp_clip_plane, point, normal, 1);

		//bottom plane
		normal.InitXYZ(0.0f, -1.0f, -tan_for_div2); //y-z
		CommonMath::Plane3DInit(m_bt_clip_plane, point, normal, 1);
	} // end else
} //end 
