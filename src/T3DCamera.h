#ifndef __T3D_CAMERA_H__
#define __T3D_CAMERA_H__

#include "T3DMath.h"
#include "T3DUtil.h"

//define camera rotation sequences
#define CAM_ROT_SEQ_XYZ 0
#define CAM_ROT_SEQ_YXZ 1
#define CAM_ROT_SEQ_XZY 2
#define CAM_ROT_SEQ_YZX 3
#define CAM_ROT_SEQ_ZYX 4
#define CAM_ROT_SEQ_ZXY 5

#define UVN_MODE_SIMPLE 0
#define UVN_MODE_SPHERICAL 1

//相机属性
#define CAM_PROJ_NORMALIZED 0X0001
#define CAM_PROJ_SCREEN		0X0002
#define CAM_PROJ_FOV90		0X004

#define CAM_MODEL_EULER		0X0008
#define CAM_MODEL_UVN		0X0010

namespace T3D {

	struct ViewPort
	{
		int m_x;
		int m_y;
		int m_width;
		int m_height;

		ViewPort() {}
		ViewPort(int x, int y, int width, int height)
			:m_x(x), m_y(y), m_width(width), m_height(height) { }
	};

	// UVN 相机 n 注视向量， v 上方的向量， u 右方的向量

	class Camera 
	{
	public:
		Camera(Vec4 cam_pos, Vec4 cam_dir, Vec4 cam_target, float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height, int cam_attr = CAM_MODEL_UVN);

		//根据相机的位置和欧拉角度计算矩阵
		//参数表示旋转的顺序  xyz xzy ...
		void BuildCameraMatrixEuler(int cam_rot_seq);

		//根据相机的位置和uvn向量计算矩阵
		void BuildCameraMatrixUVN(int mode);
		//透視投影矩陣
		void BuildPerspectiveMatrix(Matrix44 mat);
		//投影到屏幕矩陣
		void BuildScreenMatrix(Matrix44 mat);

		//视口
		void SetViewPort(int x, int y, int width, int height);
		const ViewPort & GetViewPort() const;
	public:

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

		//视口
		ViewPort m_viewport;

		float m_aspect_ratio; //屏幕的寬高比

		Matrix44 m_cam;  //世界到相機
		Matrix44 m_per;  //相機到透視
		Matrix44 m_scr;  //透視到屏幕
	};

}

#endif
