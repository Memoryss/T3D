#ifndef __T3D_MESH_H__
#define __T3D_MESH_H__

#include <string>
#include <vector>

#include "T3DMath.h"
#include "T3DCamera.h"

/*
	使用顺时针定点顺序（左手规则），表示面的外方向
*/


// 多边形和多边形面的属性
#define POLY4DV1_ATTR_2SIDED 0X0001
#define POLY4DV1_ATTR_TRANSPARENT 0X0002
#define POLY4DV1_ATTR_8BITCOLOR	0X0004
#define POLY4DV1_ATTR_RGB16 0X0008
#define POLY4DV1_ATTR_RGB24 0X0010

#define POLY4DV1_ATTR_SHADE_MODE_PURE 0X0020
#define POLY4DV1_ATTR_SHADE_MODE_FLAT 0X0040
#define POLY4DV1_ATTR_SHADE_MODE_GOURAUD 0X0080
#define POLY4DV1_ATTR_SHADE_MODE_PHONG 0X0100

#define POLY4DV1_STATE_ACTIVE 0X0001
#define POLY4DV1_STATE_CLIPPED 0X0002
#define POLY4DV1_STATE_BACKFACE 0X0004

//obj属性
#define OBJECT_STATE_ACTIVE 0X0001
#define OBJECT_STATE_VISIBLE 0X0002
#define OBJECT_STATE_CULLED 0X0004

//加载plx文件
#define PLX_RGB_MASK 0X8000  //抽取RGB/索引颜色模式的掩码
#define PLX_SHADE_MODE_MASK 0X6000	 //抽取着色模式额掩码
#define PLX_2SIDED_MASK  0X1000 //抽取双面状态设置的掩码
#define PLX_COLOR_MASK  0X0fff  //每个rgb分量4位

//颜色模式的标记
#define PLX_COLOR_MODE_RGB_FLAG 0X8000  //多边形使用rgb颜色
#define PLX_COLOR_MODE_INDEXED_FLAG 0X0000  //多边形使用8位索引模式

//双面标记
#define PLX_2SIDED_FLAG 0X1000  //多边形是双面的
#define PLX_1SIDED_FLAG 0x0000  //多边形是单面的

//着色模式标记
#define PLX_SHADE_MODE_PURE_FLAG  0X0000  //多边形使用固定颜色
#define PLX_SHADE_MODE_FLAT_FLAG  0X2000  //恒定着色
#define PLX_SHADE_MODE_GOURAUD_FLAG  0X4000 //gouraud着色
#define PLX_SHADE_MODE_PLONG_FLAG  0X6000   //phone着色

//变换控制标记
#define TRANSFORM_LOCAL_ONLY 0
#define TRANSFORM_TRANS_ONLY 1
#define TRANSFORM_LOCAL_TO_TRANS 2

//裁剪标记
#define CULL_OBJECT_X_PLANE 0X001
#define CULL_OBJECT_Y_PLANE 0X002
#define CULL_OBJECT_Z_PLANE 0X004
#define CULL_OBJECT_XYZ_PLANES (CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE)

namespace T3D {

	//三角形
	struct Triangle
	{
		int m_state = 0;   //状态信息
		int m_attr = 0;    //物理属性
		int m_color = 0;   //多边形的颜色
		Vec4 *m_vlist; //定点列表
		int m_vertices[3];//索引
	};

	//三角形面  自包含的多边形数据结构 供渲染列表使用
	struct TriangleFace
	{
		int m_state;
		int m_attr;
		int m_color;
		
		Vec4 m_vlist[3];  //三角形顶点
		Vec4 m_tvlist[3];  //变化后的顶点
		TriangleFace *m_next;  //列表中下一个多边形的指针
		TriangleFace *m_prev;  //列表中上一个多边形的指针
	};

	//基于顶点列表和多边形列表的物体
	struct Object
	{
		int m_id; //物体的数值ID
		std::string m_name;  //名称
		int m_state;   //状态
		int m_attr;   //属性
		float m_avg_radius;   //平均半径  用于碰撞检测
		float m_max_radisus;  //最大半径

		Vec4 m_world_pos;  // 世界坐标系中的位置
		Vec4 m_dir;     //局部坐标系下的旋转角度
		Vec4 m_ux, m_uy, m_uz;   //物体朝向的局部坐标轴

		int m_num_vertices;  //顶点数
		
		std::vector<Vec4> m_vlist_local;  //顶点局部坐标
		std::vector<Vec4> m_vlist_trans;  //变换后的数组

		int m_num_polys;  //多边形数
		std::vector<Triangle> m_plist;  //多边形

		//设置位置
		void SetPos(const Vec4 &pos);

		int ComputeRadius();
		//最后一个参数是选择是否对朝向向量进行变换
		void Transform(const Matrix44 &mt, int coord_select, int transform_basis);
		//模型坐标系转到世界坐标系
		void ModelToWorld(int coord_select = TRANSFORM_LOCAL_TO_TRANS);
		//model到world的變化矩陣
		void BuildModelToWorldMat44(Matrix44 &mt);
		//world到camera
		void WorldToCamera(const Camera &cam);
		//裁剪
		int Cull(const Camera &cam, int cull_flags);
		//重置
		void Reset();
		//背面剔除
		void RemoveBackfaces(const Camera &cam);
		//透视投影 非矩阵实现
		void CameraToPerspective(const Camera &cam);
		//透视除法 矩陣實現后需要調用該函數
		void PerspectiveDivision();
		//投影到屏幕
		void PerspectiveToScreen(const Camera &cam);
		//繪製線框
		void DrawWire16(const Camera &cam, unsigned int *video_buffer, int lpitch);
		//同步
		void SynchroVertex();
	};
	

	//存储渲染列表的对象，同时可以有多个渲染列表
	struct RenderList
	{
		int m_state;
		int m_attr;

		//渲染列表是一个指针数组 其中每一个指针指向一个自包含的，可渲染的多边形面
		//索引下面存储的资源
		std::vector<TriangleFace *> m_facePtrs;
		
		//避免每一帧都是在为多边形分配和释放存储空间
		std::vector<TriangleFace> m_faces;

		int m_num_trangleface;

		//根据矩阵对渲染列表的顶点进行变换
		void TransForm(const Matrix44 &mt, int coord_select);
		//模型坐标系转到世界坐标系
		void ModelToWorld(Vec4 world_pos, int coord_select = TRANSFORM_LOCAL_TO_TRANS);
		//model到world的變化矩陣
		void BuildModelToWorldMat44(Vec4 world_pos, Matrix44 &mt);
		//world到camera
		void WorldToCamera(const Camera &cam);
		//背面剔除
		void RemoveBackFace(const Camera &cam);
		//透视投影 非矩阵实现
		void CameraToPerspective(const Camera &cam);
		//透视除法 矩陣實現后需要調用該函數
		void PerspectiveDivision();
		//投影到屏幕
		void PerspectiveToScreen(const Camera &cam);
		//绘制线框
		void DrawWire16(const Camera &cam, unsigned int *video_buffer, int lptch);
	};

	class PLGLoader
	{
	public:
		static int LoadObjectPLG(Object *obj, const char *filename, const Vec4 &scale, const Vec4 &pos, const Vec4 &rot);
		// 从plg文件中加载一行数据
		// 跳过注释和空行，如果文件为空返回NULL
		static char * GetLinePLG(char *buffer, int maxlength, FILE *fp);
		//初始化物体（比例， 位置，旋转）
	};
}

#endif // !__T3D_MESH_H__

