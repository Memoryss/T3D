#ifndef __T3D_MATH_H__
#define __T3D_MATH_H__

#include <string.h>

namespace T3D {

	//不包含齐次坐标的w分量
	struct Vec2
	{
		float m_x;
		float m_y;

		void InitZero() {
			m_x = 0;
			m_y = 0;
		}

		void InitXY(float x, float y) {
			m_x = x;
			m_y = y;
		}

		void InitWithVec2(const Vec2 & vec2) {
			m_x = vec2.m_x;
			m_y = vec2.m_y;
		}
	};

	//不包含齐次坐标的w分量
	struct Vec3
	{
		float m_x;
		float m_y;
		float m_z;

		void InitZero() {
			m_x = 0;
			m_y = 0;
			m_z = 0;
		}

		void InitXYZ(float x, float y, float z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}

		void InitWithVec3(const Vec3 & vec3) {
			m_x = vec3.m_x;
			m_y = vec3.m_y;
			m_z = vec3.m_z;
		}
	};


	//包含齐次坐标的三维向量
	struct Vec4
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

		void InitXYZW(float x, float y, float z, float w) {
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		void InitWithVec4(const Vec4 & vec4) {
			m_x = vec4.m_x;
			m_y = vec4.m_y;
			m_z = vec4.m_z;
			m_w = vec4.m_w;
		}
	};

	//参数化方程
	struct ParmLine2D
	{
		Vec2 m_p0;
		Vec2 m_p1;
		Vec2 m_vec;
	};

	struct ParmLine3D
	{
		Vec3 m_p0;
		Vec3 m_p1;
		Vec3 m_vec;
	};

	struct Plane3D
	{
		Vec3 m_p0;
		Vec3 m_normal;
	};

	struct Matrix44
	{
		float m_mat[4][4];

		void InitZero() {
			memset((void*)m_mat, 0, sizeof(Matrix44));
		}

		void InitWithMat44(const Matrix44 &m44) {
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

		void InitWithMat43(const Matrix43 &m43) {
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

		void InitWithMat33(const Matrix33 &m33) {
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

	const struct Matrix22 IMAT22 = {
		1, 0,
		0, 1
	};

	struct Quat
	{
		float m_q0; //实部
		Vec3 m_qv; //虚部

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

		void InitWithVec3(const Vec3 &vec3) {
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

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define SWAP(a, b, t) {t = a; a = b; b = t;}

#define DEG_TO_RAN(ang) ((ang) * PI / 180.0f)
#define RAD_TO_DEG(rads) ((rads) * 180.0f / PI)

#define RAND_RANGE(x, y) ( (x) + (rand() % ((y) - (x) + 1)))

// macros to set the identity matrix
#define MAT_IDENTITY_2X2(m) {memcpy((void *)(m), (void *)&IMAT22, sizeof(Matrix22));}
#define MAT_IDENTITY_3X3(m) {memcpy((void *)(m), (void *)&IMAT33, sizeof(Matrix33));}
#define MAT_IDENTITY_4X4(m) {memcpy((void *)(m), (void *)&IMAT44, sizeof(Matrix44));}
#define MAT_IDENTITY_4X3(m) {memcpy((void *)(m), (void *)&IMAT33, sizeof(Matrix43));}


	//数学函数
	class CommonMath
	{
	public:
		//common  
		//先计算出0~360的sin和cos值保存起来
		static void BuildSinCosTables();

		//三角函数
		//查表以及插值 快速计算
		static float FastSin(float theta);
		static float FastCos(float theta);

		//距离
		static float FastDistance2D(float x, float y);
		static float FastDistance3D(float x, float y, float z);

		//极坐标
		static void Polar2DToVec2(const Polar2D &polar, Vec2 &point);
		static void Vec2ToPolar2D(const Vec2 &point, Polar2D &polar);
		static void Cylindrical3DToVec3(const Cylindrical3D &c3d, Vec3 &p3d);
		static void Vec3ToCylindrical3D(const Vec3 &p3d, Cylindrical3D &c3d);
		static void Spherical3DToVec3(const Spherical3D &s3d, Vec3 &p3d);
		static void Vec3ToSpherical3D(const Vec3 &p3d, Spherical3D &s3d);

		//2d向量函数
		static void Vec2Add(const Vec2 &va, const Vec2 &vb, Vec2& vsum);
		static void Vec2Sub(const Vec2 &va, const Vec2 &vb, Vec2& vsub);
		static void Vec2Scale(float k, Vec2 &va);
		static float Vec2Dot(const Vec2 &va, const Vec2 &vb);
		static float Vec2Length(const Vec2 &va);
		static float Vec2LengthFast(const Vec2 &va);
		static void Vec2Normalize(Vec2 &va);
		static void Vec2Build(const Vec2 &va, const Vec2 &vb, Vec2 &vbuild);  //va + vbuild = vb
		static float Vec2CosTh(const Vec2 &va, const Vec2 &vb);  //两个向量夹角的cos
		static void Vec2Print(const Vec2 &va, char *name);

		//3D向量函数
		static void Vec3Add(const Vec3 &va, const Vec3 &vb, Vec3& vsum);
		static void Vec3Sub(const Vec3 &va, const Vec3 &vb, Vec3& vsub);
		static void Vec3Scale(float k, Vec3 &va);
		static float Vec3Dot(const Vec3 &va, const Vec3 &vb);
		static void Vec3Cross(const Vec3 &va, const Vec3 &vb, Vec3 &vc);
		static float Vec3Length(const Vec3 &va);
		static float Vec3LengthFast(const Vec3 &va);
		static void Vec3Normalize(Vec3 &va);
		static void Vec3Build(const Vec3 &va, const Vec3 &vb, Vec3 &vbuild);
		static float Vec3CosTh(const Vec3 &va, const Vec3 &vb);
		static void Vec3Print(const Vec3 &va, char *name);

		//4D向量函数
		static void Vec4Add(const Vec4 &va, const Vec4 &vb, Vec4& vsum);
		static void Vec4Sub(const Vec4 &va, const Vec4 &vb, Vec4& vsub);
		static void Vec4Scale(float k, Vec4 &va);
		static float Vec4Dot(const Vec4 &va, const Vec4 &vb);
		static void Vec4Cross(const Vec4 &va, const Vec4 &vb, Vec4 &vc);
		static float Vec4Length(const Vec4 &va);
		static float Vec4LengthFast(const Vec4 &va);
		static void Vec4Normalize(Vec4 &va);
		static void Vec4Build(const Vec4 &va, const Vec4 &vb, Vec4 &vbuild);
		static float Vec4CosTh(const Vec4 &va, const Vec4 &vb);
		static void Vec4Print(const Vec4 &va, char *name);

		//2*2矩阵
		static void Mat22Init(Matrix22 &matrix, float m00, float m01, float m10, float m11);
		static void PrintMat22(const Matrix22 &matrix, char *name);
		static float Mat22Det(const Matrix22 &matrix);  //行列式
		static void Mat22Add(const Matrix22 &ma, const Matrix22 &mb, Matrix22 &msum);
		static void Mat22Mul(const Matrix22 &ma, const Matrix22 &mb, Matrix22 &mprod);
		static int Mat22Inverse(const Matrix22 &m, Matrix22 &mi);  //逆矩阵
		//计算2*2方程式
		static int Solve22System(const Matrix22 &A, Matrix12 &X, const Matrix12 &B);
		static void Mat12MulMat32(const Matrix12 &ma, const Matrix32 &mb, Matrix12 &mprod);  //matrix12最后一个使用1补上

		//3*3矩阵
		static int Mat13MulMat33(const Matrix13 &ma, const Matrix33 &mb, Matrix13 &mprod);
		static void Mat33MulMat33(const Matrix33 &ma, const Matrix33 &mb, Matrix33 &mprod);
		static int Mat32Init(Matrix32 &ma, float m00, float m01, float m10, float m11, float m20, float m21);
		static void Mat33Add(const Matrix33 &ma, const Matrix33 &mb, Matrix33 &msum);
		static void Vec3MulMat33(const Vec3 &va, const Matrix33 &mb, Vec3 &vprod);
		static int Mat33Inverse(const Matrix33 &m, Matrix33 &mi);
		static void Mat33Init(Matrix33 &m, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
		//计算2*2方程式
		static int SolveMat33System(Matrix33 &A, Matrix13 &X, Matrix13 &B);
		static void PrintMat33(const Matrix33 &ma, char *name);
		static float Mat33Det(const Matrix33 &m);

		// 4 * 4 矩阵
		static void Mat44Add(const Matrix44 &ma, const Matrix44 &mb, Matrix44 &msum);
		static void Mat44Mul(const Matrix44 &ma, const Matrix44 &mb, Matrix44 &mprod);
		static void Mat14MulMat44(const Matrix14 &ma, const Matrix44 &mb, Matrix14 &mprod);
		static void V3dMulMat44(const Vec3 &va, const Matrix44 &mb, Vec3 &vprod);
		static void V3dMulMat43(const Vec3 &va, const Matrix43 &mb, Vec3 &vprod);
		static void V4dMulMat44(const Vec4 &va, const Matrix44 &mb, Vec4 &vprod);
		static void V4dMulMat43(const Vec4 &va, const Matrix43 &mb, Vec4 &vprod);
		static int Mat44Inverse(const Matrix44 &m, Matrix44 &mi);
		static void Mat44Init(Matrix44 &m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
		static void PrintMat44(const Matrix44 &ma, char *name);

		//四元数函数
		static void QuatAdd(const Quat &q1, const Quat &q2, Quat &qsum);
		static void QuatSub(const Quat &q1, const Quat &q2, Quat &qdiff);
		static void QuatConjugate(const Quat &q1, Quat &qconj);  //计算共轭
		static void QuatScale(const Quat &q, float scale, Quat &qs);
		static float QuatNorm(const Quat &q);
		static void QuatNormalize(const Quat &q, Quat &qn);
		static void QuatUnitInverse(const Quat &q, Quat & qi);
		static void QuatInverse(const Quat &q, Quat &qi);
		static void QuatMul(const Quat &q1, const Quat &q2, Quat &qprod);
		static void QuatTripleProduct(const Quat &q1, const Quat &q2, const Quat &q3, Quat &qprod);
		static void V3DThetaToQuat(Quat &q, const Vec3 &v, float theta);
		static void V4DThetaToQuat(Quat &q, const Vec4 &v, float theta);
		//根据绕z y x旋转的欧拉角创建一个旋转的四元数。
		static void EulerZYXToQuat(Quat &q, float theta_z, float theta_y, float theta_x);
		static void QuatToV3DTheta(const Quat &q, Vec3 &v, float &theta);
		static void QuatPrint(const Quat &q, char *name);


		//2d参数化直线函数
		static void InitParmLine2D(const Vec2 &pInit, const Vec2 &pTerm, ParmLine2D &p);
		static void ComputeParmLine2D(ParmLine2D &p, float t, Vec2 &pt);
		static int IntersectParmLines2D(ParmLine2D &p1, ParmLine2D &p2, Vec2 &pt);

		//3d参数化直线函数
		static void InitParmLine3D(const Vec3 &pInit, const Vec3 &pTerm, ParmLine3D &p);
		static void ComputeParmLine3D(const ParmLine3D &p, float t, Vec3 &pt);

		// 3d平面函数
		static void Plane3DInit(Plane3D &plane, const Vec3 &p0, const Vec3 &normal, bool normalize);
		static float ComputePointInPlane3D(const Vec3 &pt, const Plane3D &plane);
		static int IntersectParmLinePlane3D(const ParmLine3D &line, Plane3D &plane, float &t, Vec3 &pt);

		static float cos_look[361];
		static float sin_look[361];

	};
}



#endif
