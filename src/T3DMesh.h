#ifndef __T3DMESH_H__
#define __T3DMESH_H__

#include <string>
#include <vector>

#include "T3DMath.h"

/*
	使用顺时针定点顺序（左手规则），表示面的外方向
*/

namespace T3D {

	//三角形
	struct Triangle
	{
		int m_state;   //状态信息
		int m_attr;    //物理属性
		int m_color;   //多边形的颜色
		Point4D *m_vlist; //定点列表
		int m_vertices[3];//索引
	};

	//三角形面  自包含的多边形数据结构 供渲染列表使用
	struct TriangleFace
	{
		int m_state;
		int m_attr;
		int m_color;
		
		Point4D m_vlist[3];  //三角形顶点
		Point4D m_tvlist[3];  //变化后的顶点
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

		Point4D m_world_pos;  // 世界坐标系中的位置
		Vector4D m_dir;     //局部坐标系下的旋转角度
		Vector4D m_ux, m_uy, m_uz;   //物体朝向的局部坐标轴

		int m_num_vertices;  //顶点数
		
		std::vector<Point4D> m_vlist_local;  //顶点局部坐标
		std::vector<Point4D> m_vlist_trans;  //变换后的数组

		int m_num_polys;  //多边形数
		std::vector<Triangle> m_plist;  //多边形

		int ComputeRadius();
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

		void TransForm(const Matrix44 &mt, int coord_select);

	};

	class PLGLoader
	{
		// 从plg文件中加载一行数据
		// 跳过注释和空行，如果文件为空返回NULL
		static char * GetLinePLG(char *buffer, int maxlength, FILE *fp);
		//初始化物体（比例， 位置，旋转）
		static int LoadObjectPLG(Object *obj, const char *filename, const Vector4D &scale, const Vector4D &pos, const Vector4D &rot)
	};
}

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

//trans
#define TRANSFORM_LOCAL_ONLY 0
#define TRANSFORM_TRANS_ONLY 1
#define TRANSFORM_LOCAL_TO_TRANS 2

#endif // !__T3DMESH_H__

