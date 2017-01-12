#ifndef __T3DMATH_H__
#define __T3DMATH_H__

#include <string.h>

namespace T3D {

	struct Point2D
	{
		float m_x;
		float m_y;

		void Init(const Point2D &p2) {
			m_x = p2.m_x;
			m_y = p2.m_y;
		}
	};

	struct Point3D
	{
		float m_x;
		float m_y;
		float m_z;

		void Init(const Point3D &p3) {
			m_x = p3.m_x;
			m_y = p3.m_y;
			m_z = p3.m_z;
		}
	};

	//不包含齐次坐标的w分量
	struct Vector2D
	{
		float m_x;
		float m_y;

		void InitZero() {
			m_x = 0;
			m_y = 0;
		}

		void InitXY(int x, int y) {
			m_x = x;
			m_y = y;
		}

		void InitWithVec2(const Vector2D & vec2) {
			m_x = vec2.m_x;
			m_y = vec2.m_y;
		}
	};

	//不包含齐次坐标的w分量
	struct Vector3D
	{
		float m_x;
		float m_y;
		float m_z;

		void InitZero() {
			m_x = 0;
			m_y = 0;
			m_z = 0;
		}

		void InitXYZ(int x, int y, int z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}

		void InitWithVec3(const Vector3D & vec3) {
			m_x = vec3.m_x;
			m_y = vec3.m_y;
			m_z = vec3.m_z;
		}
	};


	//包含齐次坐标的三维向量
	struct Vector4D
	{
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		void InitZero() {
			m_x = 0;
			m_y = 0;
			m_z = 0;
			m_w = 0;
		}

		void InitXYZW(float x, float, y, float z, float w) {
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		void InitWithVec4(const Vector4D & vec4) {
			m_x = vec4.m_x;
			m_y = vec4.m_y;
			m_z = vec4.m_z;
			m_w = vec4.m_w;
		}
	};

	//参数化方程
	struct ParmLine2D
	{
		Point2D m_p0;
		Point2D m_p1;
		Vector2D m_vec;
	};

	struct ParmLine3D
	{
		Point3D m_p0;
		Point3D m_p1;
		Vector3D m_vec;
	};

	struct Plane3D
	{
		Point3D m_p0;
		Vector3D m_normal;
	};

	struct Matrix44
	{
		float m_mat[4][4];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix44));
		}
		
		void Identity() {
			memcpy((void*)m_mat, (void*)&IMAT44, sizeof(Matrix44));
		}

		void InitWithMat44(const Matrix22 &m44) {
			memcpy((void*)m_mat, (void*)&m44, sizeof(Matrix44));
		}

		void Transpose(Matrix44 &m44) {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					m44.m_mat[i][j] = m_mat[j][i];
				}
			}
		}
	};

	struct Matrix43
	{
		float m_mat[4][3];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix43));
		}

		void Identity() {
			memcpy((void*)m_mat, (void*)&IMAT43, sizeof(Matrix43));
		}

		void InitWithMat43(const Matrix22 &m43) {
			memcpy((void*)m_mat, (void*)&m43, sizeof(Matrix43));
		}
	};

	struct Matrix14
	{
		float m_mat[1][4];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix14));
		} 
	};

	struct Matrix33
	{
		float m_mat[3][3];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix33));
		}

		void Identity() {
			memcpy((void*)m_mat, (void*)&IMAT33, sizeof(Matrix33));
		}

		void InitWithMat33(const Matrix22 &m33) {
			memcpy((void*)m_mat, (void*)&m33, sizeof(Matrix33));
		}

		void Transpose(Matrix33 &m33) {
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					m33.m_mat[i][j] = m_mat[j][i];
				}
			}
		}
	};

	struct Matrix13
	{
		float m_mat[1][3];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix13));
		}
	};

	struct Matrix32
	{
		float m_mat[3][2];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix32));
		}
	};

	struct Matrix22
	{
		float m_mat[2][2];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix22));
		}

		void Identity() {
			memcpy((void*)m_mat, (void*)&IMAT22, sizeof(Matrix22));
		}

		void InitWithMat22(const Matrix22 &m22) {
			memcpy((void*)m_mat, (void*)&m22, sizeof(Matrix22));
		}

		void Transpose(Matrix22 &m22) {
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {
					m22.m_mat[i][j] = m_mat[j][i];
				}
			}
		}
	};

	struct Matrix12
	{
		float m_mat[1][2];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix12));
		}
	};

	struct Quat
	{
		float m_q0; //实部
		Vector3D m_qv; //虚部

		void InitZero() {
			m_qv.m_x = 0;
			m_qv.m_y = 0;
			m_qv.m_z = 0;
			m_q0 = 0;
		}

		void InitWithQuat(const Quat &quat) {
			m_q0 = quat.m_q0;
			m_qv.InitWithVec3(quat.m_qv);
		}

		void InitWithVec3(const Vector3D &vec3) {
			m_q0 = 0;
			m_qv.InitWithVec3(vec3);
		}
	};

	//极坐标
	struct Polar2D
	{
		float m_r;  //半径
		float m_theta;  //角度 弧度
	};

	//柱面坐标
	struct Cylindrical3D
	{
		float m_r;
		float m_theta;
		float m_z;  //z坐标
	};

	//球面坐标
	struct Spherical3D
	{
		float m_p; //到原点的距离
		float m_theta; //原点到p线段和Z轴的夹角
		float m_phi;  //原点到p线段在x-y平面投影和x轴的夹角
	};

#define PI ((float)3.141592654f)
#define PI2 ((float)6.283185307f)
#define PI_DIV_2 ((float)1.570796327f)
#define PI_DIV_4 ((float)0.785398163f)
#define PI_INV ((float)0.318309886f)

#define EPSILON_E4 (float)(1E-4)
#define EPSILON_E5 (float)(1E-5)
#define EPSILON_E6 (float)(1E-6)

#define PARM_LINE_NO_INTERSECT 0
#define PARM_LINE_INTERSECT_IN_SEGMENT 1
#define PARM_LINE_INTERSECT_OUT_SEGMENT 2
#define PARM_LINE_INTERSECT_EVERYWHERE 3

	const Matrix44 IMAT44 = {	
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	const Matrix43 IMAT43 = {
		1, 0, 0, 
		0, 1, 0,
		0, 0, 1,
		0, 0, 0
	};

	const Matrix33 IMAT33 = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	const Matrix22 IMAT22 = {
		1, 0,
		0, 1
	};

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define SWAP(a, b, t) {t = a; a = b; b = t;}

#define DEG_TO_RAN(ang) ((ang)*PI / 180.0)
#define RAD_TO_DEG(rads) ((rads)*180.0/PI)

#define RAND_RANGE(x, y) ( (x) + (rand() % ((y) - (x) + 1)))


	//数学函数
	class CommonMath
	{
	public:
		//三角函数
		static FastSin(float theta);
		static FastCos(float theta);

		//距离
		static int FastDistance2D(int x, int y);
		static float FastDistance3D(float x, float, float z);

		//极坐标
		static void Polar2DToPoint2D(const Polar2D &polar, Point2D &point);
		static void Point2DToPolar2D(const Point2D &point, Polar2D &polar);
		static void Cylindrical3DToPoint3D(const )
	};
}



#endif
