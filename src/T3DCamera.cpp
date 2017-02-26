#include "T3DCamera.h"

#include "T3DMath.h"

#include <math.h>

namespace T3D {

	Camera::Camera(Vec4 cam_pos, Vec4 cam_dir, Vec4 cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height, int cam_attr)
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

		m_viewport.m_width = viewport_width;
		m_viewport.m_height = viewport_height;
		m_viewport.m_x = 0;
		m_viewport.m_y = 0;
		m_aspect_ratio = float(m_viewport.m_width) / m_viewport.m_height;

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
	} //end construct

	void Camera::BuildCameraMatrixEuler(int cam_rot_seq)
	{
		Matrix44 mt_inv, //translation inverse
			mx_inv, //rotate x inverse
			my_inv, //rotate y inverse
			mz_inv, //rotate z inverse
			mrot, //multiply x y z matrix
			mtmp; //tmp matrix

				  //translation inverse
		mt_inv.Identity(); //indentity matrix
		mt_inv.m_mat[3][0] = -m_pos.m_x;
		mt_inv.m_mat[3][1] = -m_pos.m_y;
		mt_inv.m_mat[3][2] = -m_pos.m_z;

		// rotate inverse
		// 1. inverse matrix == transpose matrix
		// 2. theta Negate
		float theta_x = m_dir.m_x;
		float theta_y = m_dir.m_y;
		float theta_z = m_dir.m_z;

		//computer cos(theta_x) and sin(theta_x)
		float cos_theta = CommonMath::FastCos(theta_x);   //cos(x) = cos(-x)
		float sin_theta = -CommonMath::FastSin(theta_x);   //sin(x) = -sin(-x)
		mx_inv.Identity();
		mx_inv.m_mat[1][1] = cos_theta;
		mx_inv.m_mat[1][2] = sin_theta;
		mx_inv.m_mat[2][1] = -sin_theta;
		mx_inv.m_mat[2][2] = cos_theta;

		//computer cos(theta_y) and sin(theta_y)
		cos_theta = CommonMath::FastCos(theta_y);
		sin_theta = -CommonMath::FastSin(theta_y);
		my_inv.Identity();
		my_inv.m_mat[0][0] = cos_theta;
		my_inv.m_mat[0][1] = -sin_theta;
		my_inv.m_mat[2][0] = sin_theta;
		my_inv.m_mat[2][1] = cos_theta;

		//computer cos(theta_z) and sin(theta_z)
		cos_theta = CommonMath::FastCos(theta_z);
		sin_theta = -CommonMath::FastSin(theta_z);
		mz_inv.Identity();
		mz_inv.m_mat[0][0] = cos_theta;
		mz_inv.m_mat[0][1] = sin_theta;
		mz_inv.m_mat[1][0] = -sin_theta;
		mz_inv.m_mat[1][1] = cos_theta;

		//multipy rotate matrix
		switch (cam_rot_seq)
		{
		case CAM_ROT_SEQ_XYZ:
			CommonMath::Mat44Mul(mx_inv, my_inv, mtmp);
			CommonMath::Mat44Mul(mtmp, mz_inv, mrot);
			break;
		case CAM_ROT_SEQ_YXZ:
			CommonMath::Mat44Mul(my_inv, mx_inv, mtmp);
			CommonMath::Mat44Mul(mtmp, mz_inv, mrot);
			break;
		case CAM_ROT_SEQ_XZY:
			CommonMath::Mat44Mul(mx_inv, mz_inv, mtmp);
			CommonMath::Mat44Mul(mtmp, my_inv, mrot);
			break;
		case CAM_ROT_SEQ_YZX:
			CommonMath::Mat44Mul(my_inv, mz_inv, mtmp);
			CommonMath::Mat44Mul(mtmp, mx_inv, mrot);
			break;
		case CAM_ROT_SEQ_ZYX:
			CommonMath::Mat44Mul(mz_inv, my_inv, mtmp);
			CommonMath::Mat44Mul(mtmp, mx_inv, mrot);
			break;
		case CAM_ROT_SEQ_ZXY:
			CommonMath::Mat44Mul(mz_inv, mx_inv, mtmp);
			CommonMath::Mat44Mul(mtmp, my_inv, mrot);
			break;
		default:
			break;
		} //end switch

		  // mt_inv * mrot -> mcam
		CommonMath::Mat44Mul(mt_inv, mrot, m_cam);
	} //end build

	void Camera::BuildCameraMatrixUVN(int mode)
	{
		//up v, target n, right u
		// mode 1. UVN_MODE_SIMPLE  simple mode ,just use target and pos
		// mode 2. UVN_MODE_SPHERICAL 球面坐标模式，分量x和y作为观察向量的方位角和仰角

		Matrix44 mt_inv, //translation inverse
			mt_uvn,  //uvn inverse
			mtmp;

		// cam pos create mt_inv
		mt_inv.Identity();
		mt_inv.m_mat[3][0] = -m_pos.m_x;
		mt_inv.m_mat[3][1] = -m_pos.m_y;
		mt_inv.m_mat[3][2] = -m_pos.m_z;

		// step2 
		if (mode == UVN_MODE_SPHERICAL)
		{
			float phi = this->m_dir.m_x;
			float theta = this->m_dir.m_y;

			float sin_phi = CommonMath::FastSin(phi);
			float cos_phi = CommonMath::FastCos(phi);

			float sin_theta = CommonMath::FastSin(theta);
			float cos_theta = CommonMath::FastCos(theta);

			this->m_target.m_x = -1 * sin_phi * sin_theta;
			this->m_target.m_y = 1 * cos_phi;
			this->m_target.m_z = 1 * sin_phi * cos_theta;
		} //end else

		//TODO 当pos 和 target 一样时
		// n = <target - pos>  计算n 
		CommonMath::Vec4Build(this->m_pos, this->m_target, this->m_n);

		// v  假定 0 1 0
		this->m_v.InitXYZW(0, 1, 0, 1);

		// u = v x n  计算出 u 向量
		CommonMath::Vec4Cross(this->m_v, this->m_n, this->m_u);

		// v = n x u  重新计算 v 向量
		CommonMath::Vec4Cross(this->m_n, this->m_u, this->m_v);

		//normalize
		CommonMath::Vec4Normalize(this->m_u);
		CommonMath::Vec4Normalize(this->m_n);
		CommonMath::Vec4Normalize(this->m_v);

		mt_uvn.Identity();
		mt_uvn.m_mat[0][0] = this->m_u.m_x;
		mt_uvn.m_mat[1][0] = this->m_u.m_y;
		mt_uvn.m_mat[2][0] = this->m_u.m_z;

		mt_uvn.m_mat[0][1] = this->m_v.m_x;
		mt_uvn.m_mat[1][1] = this->m_v.m_y;
		mt_uvn.m_mat[2][1] = this->m_v.m_z;

		mt_uvn.m_mat[0][2] = this->m_n.m_x;
		mt_uvn.m_mat[1][2] = this->m_n.m_y;
		mt_uvn.m_mat[2][2] = this->m_n.m_z;

		CommonMath::Mat44Mul(mt_inv, mt_uvn, this->m_cam);
	}// end BuildCameraMatrixUVN

	void Camera::BuildPerspectiveMatrix(Matrix44 mat)
	{
		mat.Identity();
		mat.m_mat[0][0] = m_view_dist;
		mat.m_mat[1][1] = m_view_dist * m_aspect_ratio;
		mat.m_mat[2][3] = 1; //w值为z  为了透视除法
	}

	void Camera::BuildScreenMatrix(Matrix44 mat)
	{
		float alpha = 0.5f * m_viewport.m_width - 0.5f;
		float beta = 0.5f * m_viewport.m_height - 0.5f;

		mat.Identity();
		mat.m_mat[0][0] = alpha;
		mat.m_mat[2][0] = alpha; //此時z值為1
		mat.m_mat[1][1] = -beta;
		mat.m_mat[2][1] = beta;
	}

	void Camera::SetViewPort(int x, int y, int width, int height)
	{
		m_viewport.m_x = x;
		m_viewport.m_y = x;
		m_viewport.m_width = width;
		m_viewport.m_height = height;
	}

	const ViewPort & Camera::GetViewPort() const 
	{
		return m_viewport;
	}
}
