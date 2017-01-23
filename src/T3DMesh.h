#ifndef __T3DMESH_H__
#define __T3DMESH_H__

#include <string>
#include <vector>

#include "T3DMath.h"

/*
	ʹ��˳ʱ�붨��˳�����ֹ��򣩣���ʾ����ⷽ��
*/

namespace T3D {

	//������
	struct Triangle
	{
		int m_state;   //״̬��Ϣ
		int m_attr;    //��������
		int m_color;   //����ε���ɫ
		Point4D *m_vlist; //�����б�
		int m_vertices[3];//����
	};

	//��������  �԰����Ķ�������ݽṹ ����Ⱦ�б�ʹ��
	struct TriangleFace
	{
		int m_state;
		int m_attr;
		int m_color;
		
		Point4D m_vlist[3];  //�����ζ���
		Point4D m_tvlist[3];  //�仯��Ķ���
		TriangleFace *m_next;  //�б�����һ������ε�ָ��
		TriangleFace *m_prev;  //�б�����һ������ε�ָ��
	};

	//���ڶ����б�Ͷ�����б������
	struct Object
	{
		int m_id; //�������ֵID
		std::string m_name;  //����
		int m_state;   //״̬
		int m_attr;   //����
		float m_avg_radius;   //ƽ���뾶  ������ײ���
		float m_max_radisus;  //���뾶

		Point4D m_world_pos;  // ��������ϵ�е�λ��
		Vector4D m_dir;     //�ֲ�����ϵ�µ���ת�Ƕ�
		Vector4D m_ux, m_uy, m_uz;   //���峯��ľֲ�������

		int m_num_vertices;  //������
		
		std::vector<Point4D> m_vlist_local;  //����ֲ�����
		std::vector<Point4D> m_vlist_trans;  //�任�������

		int m_num_polys;  //�������
		std::vector<Triangle> m_plist;  //�����

		int ComputeRadius();
	};
	

	//�洢��Ⱦ�б�Ķ���ͬʱ�����ж����Ⱦ�б�
	struct RenderList
	{
		int m_state;
		int m_attr;

		//��Ⱦ�б���һ��ָ������ ����ÿһ��ָ��ָ��һ���԰����ģ�����Ⱦ�Ķ������
		//��������洢����Դ
		std::vector<TriangleFace *> m_facePtrs;
		
		//����ÿһ֡������Ϊ����η�����ͷŴ洢�ռ�
		std::vector<TriangleFace> m_faces;

		int m_num_trangleface;

		void TransForm(const Matrix44 &mt, int coord_select);

	};

	class PLGLoader
	{
		// ��plg�ļ��м���һ������
		// ����ע�ͺͿ��У�����ļ�Ϊ�շ���NULL
		static char * GetLinePLG(char *buffer, int maxlength, FILE *fp);
		//��ʼ�����壨������ λ�ã���ת��
		static int LoadObjectPLG(Object *obj, const char *filename, const Vector4D &scale, const Vector4D &pos, const Vector4D &rot)
	};
}

// ����κͶ�����������
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

//obj����
#define OBJECT_STATE_ACTIVE 0X0001
#define OBJECT_STATE_VISIBLE 0X0002
#define OBJECT_STATE_CULLED 0X0004

//����plx�ļ�
#define PLX_RGB_MASK 0X8000  //��ȡRGB/������ɫģʽ������
#define PLX_SHADE_MODE_MASK 0X6000	 //��ȡ��ɫģʽ������
#define PLX_2SIDED_MASK  0X1000 //��ȡ˫��״̬���õ�����
#define PLX_COLOR_MASK  0X0fff  //ÿ��rgb����4λ

//��ɫģʽ�ı��
#define PLX_COLOR_MODE_RGB_FLAG 0X8000  //�����ʹ��rgb��ɫ
#define PLX_COLOR_MODE_INDEXED_FLAG 0X0000  //�����ʹ��8λ����ģʽ
 
//˫����
#define PLX_2SIDED_FLAG 0X1000  //�������˫���
#define PLX_1SIDED_FLAG 0x0000  //������ǵ����

//��ɫģʽ���
#define PLX_SHADE_MODE_PURE_FLAG  0X0000  //�����ʹ�ù̶���ɫ
#define PLX_SHADE_MODE_FLAT_FLAG  0X2000  //�㶨��ɫ
#define PLX_SHADE_MODE_GOURAUD_FLAG  0X4000 //gouraud��ɫ
#define PLX_SHADE_MODE_PLONG_FLAG  0X6000   //phone��ɫ

//trans
#define TRANSFORM_LOCAL_ONLY 0
#define TRANSFORM_TRANS_ONLY 1
#define TRANSFORM_LOCAL_TO_TRANS 2

#endif // !__T3DMESH_H__

