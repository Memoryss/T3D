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

		//根据相机的位置和欧拉角度计算矩阵
		//参数表示旋转的顺序  xyz xzy ...
		void BuildCameraMatrixEuler(int cam_rot_seq);

		//根据相机的位置和uvn向量计算矩阵
		void BuildCameraMatrixUVN(int mode);

	private:

		int m_state;
		int m_attr;  //CAM_MODEL_ELUER CAM_MODEL_UVN

		Vec4 m_pos;  //相機在世界坐標系中的位置
		Vec4 m_dir;  //相機在世界坐標系的朝向  歐拉相機模型的軸線角、uvn相機時 x為球面左邊的仰角 y為方向角

		//uvn相機朝向
		Vec4 m_u;
		Vec4 m_v;
		Vec4 m_n;
		Vec4 m_target; //uvn模型的目標位置

		//float m_view_dist_h;  //水平視距和垂直視距
		//float m_view_dist_v;
		float m_view_dist;

		float m_fov; //水平方向和垂直方向的視野

		//3d 裁剪面
		//如果視野不是90度，3d裁剪面將是一個一般性的平面方程
		float m_near_clip_z; //近裁剪面
		float m_far_clip_z;  //遠裁剪面

		Plane3D m_rt_clip_plane;  //右裁剪面
		Plane3D m_lt_clip_plane;  //左
		Plane3D m_tp_clip_plane;  //上
		Plane3D m_bt_clip_plane;  //下

		float m_viewplane_width;  //視平面的寬度和高度
		float m_viewplane_height; //對於歸一化投影，為2*2 否則大小和視口或屏幕窗口相同

		//屏幕和視口是同義詞
		float m_viewport_width;  //屏幕、視口的寬度和高度
		float m_viewport_height;
		float m_viewport_center_x;  //中心
		float m_viewport_center_y;

		float m_aspect_ratio; //屏幕的寬高比

		Matrix44 m_cam;  //世界到相機
		Matrix44 m_per;  //相機到透視
		Matrix44 m_scr;  //透視到屏幕
	};

}

#endif
