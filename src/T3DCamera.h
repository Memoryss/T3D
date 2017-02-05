#ifndef __T3D_CAMERA_H__
#define __T3D_CAMERA_H__

#include "T3DMath.h"

//define camera rotation sequences
#define CAM_ROT_SEQ_XYZ 0
#define CAM_ROT_SEQ_YXZ 1
#define CAM_ROT_SEQ_XZY 2
#define CAM_ROT_SEQ_YZX 3
#define CAM_ROT_SEQ_ZYX 4
#define CAM_ROT_SEQ_ZXY 5

namespace T3D {

	class Camera 
	{
	public:
		Camera(int cam_attr, Vec4 cam_pos, Vec4 cam_dir, Vec4 cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height);

		//���������λ�ú�ŷ���Ƕȼ������
		//������ʾ��ת��˳��  xyz xzy ...
		void BuildCameraMatrixEuler(int cam_rot_seq);

		//���������λ�ú�uvn�����������
		void BuildCameraMatrixUVN(int mode);

	private:

		int m_state;
		int m_attr;  //CAM_MODEL_ELUER CAM_MODEL_UVN

		Vec4 m_pos;  //���C����������ϵ�е�λ��
		Vec4 m_dir;  //���C����������ϵ�ĳ���  �W�����Cģ�͵��S���ǡ�uvn���C�r x��������߅������ y�鷽���

		//uvn���C����
		Vec4 m_u;
		Vec4 m_v;
		Vec4 m_n;
		Vec4 m_target; //uvnģ�͵�Ŀ��λ��

		//float m_view_dist_h;  //ˮƽҕ��ʹ�ֱҕ��
		//float m_view_dist_v;
		float m_view_dist;

		float m_fov; //ˮƽ����ʹ�ֱ�����ҕҰ

		//3d �ü���
		//���ҕҰ����90�ȣ�3d�ü��挢��һ��һ���Ե�ƽ�淽��
		float m_near_clip_z; //���ü���
		float m_far_clip_z;  //�h�ü���

		Plane3D m_rt_clip_plane;  //�Ҳü���
		Plane3D m_lt_clip_plane;  //��
		Plane3D m_tp_clip_plane;  //��
		Plane3D m_bt_clip_plane;  //��

		float m_viewplane_width;  //ҕƽ��Č��Ⱥ͸߶�
		float m_viewplane_height; //��춚wһ��ͶӰ����2*2 ��t��С��ҕ�ڻ���Ļ������ͬ

		//��Ļ��ҕ����ͬ�x�~
		float m_viewport_width;  //��Ļ��ҕ�ڵČ��Ⱥ͸߶�
		float m_viewport_height;
		float m_viewport_center_x;  //����
		float m_viewport_center_y;

		float m_aspect_ratio; //��Ļ�Č��߱�

		Matrix44 m_cam;  //���絽���C
		Matrix44 m_per;  //���C��͸ҕ
		Matrix44 m_scr;  //͸ҕ����Ļ
	};

}

#endif
