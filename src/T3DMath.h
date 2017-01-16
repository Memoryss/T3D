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
		static void Polar2DToPoint2D(const Polar2D &polar, Point2D &point);
		static void Point2DToPolar2D(const Point2D &point, Polar2D &polar);
		static void Cylindrical3DToPoint3D(const Cylindrical3D &c3d, Point3D &p3d);
		static void Point3DToCylindrical3D(const Point3D &p3d, Cylindrical3D &c3d);
		static void Spherical3DToPoint3D(const Spherical3D &s3d, Point3D &p3d);
		static void Point3DToSpherical3D(const Point3D &p3d, Spherical3D &s3d);

		//2d向量函数
		static void Vector2DAdd(const Vector2D &va, const Vector2D &vb, Vector2D& vsum);
		static void Vector2DSub(const Vector2D &va, const Vector2D &vb, Vector2D& vsub);
		static void Vector2DScale(float k, Vector2D &va);
		static float Vector2DDot(const Vector2D &va, const Vector2D &vb);
		static float Vector2DLength(const Vector2D &va);
		static float Vector2DLengthFast(const Vector2D &va);
		static void Vector2DNormalize(Vector2D &va);
		static void Vector2DBuild(const Vector2D &va, const Vector2D &vb, Vector2D &vbuild);  //va + vbuild = vb
		static float Vector2DCosTh(const Vector2D &va, const Vector2D &vb);  //两个向量夹角的cos
		static void Vector2DPrint(const Vector2D &va, char *name);

		//3D向量函数
		static void Vector3DAdd(const Vector3D &va, const Vector3D &vb, Vector3D& vsum);
		static void Vector3DSub(const Vector3D &va, const Vector3D &vb, Vector3D& vsub);
		static void Vector3DScale(float k, Vector3D &va);
		static float Vector3DDot(const Vector3D &va, const Vector3D &vb);
		static void Vector3DCross(const Vector3D &va, const Vector3D &vb, Vector3D &vc);
		static float Vector3DLength(const Vector3D &va);
		static float Vector3DLengthFast(const Vector3D &va);
		static void Vector3DNormalize(Vector3D &va);
		static void Vector3DBuild(const Vector3D &va, const Vector3D &vb, Vector3D &vbuild);
		static float Vector3DCosTh(const Vector3D &va, const Vector3D &vb);
		static void Vector3DPrint(const Vector3D &va, char *name);

		//4D向量函数
		static void Vector4DAdd(const Vector4D &va, const Vector4D &vb, Vector4D& vsum);
		static void Vector4DSub(const Vector4D &va, const Vector4D &vb, Vector4D& vsub);
		static void Vector4DScale(float k, Vector4D &va);
		static float Vector4DDot(const Vector4D &va, const Vector4D &vb);
		static void Vector4DCross(const Vector4D &va, const Vector4D &vb, Vector4D &vc);
		static float Vector4DLength(const Vector4D &va);
		static float Vector4DLengthFast(const Vector4D &va);
		static void Vector4DNormalize(Vector4D &va);
		static void Vector4DBuild(const Vector4D &va, const Vector4D &vb, Vector4D &vbuild);
		static float Vector4DCosTh(const Vector4D &va, const Vector4D &vb);
		static void Vector4DPrint(const Vector4D &va, char *name);

		//2*2矩阵
		static void Mat22Init(Matrix22 &matrix, float m00, float m01, float m10, float m11);
		static void PrintMat22(const Matrix22 &matrix, char *name);
		static float Mat22Det(const Matrix22 &matrix);  //行列式
		static void Mat22Add(const Matrix22 &ma, const Matrix22 &mb, Matrix22 &msum);
		static void Mat22Mul(const Matrix22 &ma, const Matrix22 &mb, Matrix22 &mprod);
		static int Mat22Inverse(const Matrix22 &m, Matrix22 &mi);  //逆矩阵
		static int Solve22System(const Matrix22 &A, const Matrix22 &X, const Matrix22 &B);
		static void Mat12MulMat32(const Matrix12 &ma, const Matrix32 &mb, Matrix12 &mprod);  //matrix12最后一个使用1补上

		//3*3矩阵
		static int Mat13MulMat33(const Matrix13 &ma, const Matrix33 &mb, Matrix13 &mprod);
		static void Mat33MulMat33(const Matrix33 &ma, const Matrix33 &mb, Matrix33 &mprod);
		static int Mat32Init(Matrix32 &ma, float m00, float m01, float m10, float m11, float m20, float m21);
		static void Mat33Add(const Matrix33 &ma, const Matrix33 &mb, Matrix33 &msum);
		static void Vec3MulMat33(const Vector3D &va, const Matrix33 &mb, Vector3D &vprod);
		static int Mat33Inverse(const Matrix33 &m, Matrix33 &mi);
		static void Mat33Init(Matrix33 &m, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
		static int SolveMat33System(Matrix33 &A, Matrix33 &X, Matrix33 &B);
		static void PrintMat33(const Matrix33 &ma, char *name);
		static float Mat33Det(const Matrix33 &m);

		// 4 * 4 矩阵
		static void Mat44Add(const Matrix44 &ma, const Matrix44 &mb, Matrix44 &msum);
		static void Mat44Mul(const Matrix44 &ma, const Matrix44 &mb, Matrix44 &mprod);
		static void Mat14MulMat44(const Matrix14 &ma, const Matrix44 &mb, Matrix14 &mprod);
		static void V3dMulMat44(const Vector3D &va, const Matrix44 &mb, Vector3D &vprod);
		static void V3dMulMat43(const Vector3D &va, const Matrix43 &mb, Vector3D &vprod);
		static void V4dMulMat44(const Vector4D &va, const Matrix44 &mb, Vector4D &vprod);
		static void V4dMulMat43(const Vector4D &va, const Matrix43 &mb, Vector4D &vprod);
		static int Mat44Inverse(const Matrix44 &m, Matrix44 &mi);
		static void Mat44Init(Matrix44 &m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
		static void PrintMat44(const Matrix44 &ma, char *name);

		//四元数函数
		static void QuatAdd(const Quat &q1, const Quat &q2, Quat &qsum);
		static void QuatSub(const Quat &q1, const Quat &q2, Quat &qdiff);
		static void QuatConjugate(const Quat &q1, Quat &qconj);
		static void QuatScale(const Quat &q, float scale, Quat &qs);
		static void QuatNorm(Quat &q);
		static void QuatNormalize(const Quat &q, Quat &qn);
		static void QuatUnitInverse(const Quat &q, Quat & qi);
		static void QuatInverse(const Quat &q, Quat &qi);
		static void QuatMul(const Quat &q1, const Quat &q2, Quat &qprod);
		static void QuatTripleProduct(const Quat &q1, const Quat &q2, const Quat &q3, Quat &qprod);
		static void V3DThetaToQuat(Quat &q, const Vector3D &v, float theta);
		static void V4DThetaToQuat(Quat &q, const Vector4D &v, float theta);
		static void EulerZYXToQuat(Quat &q, float theta_z, float theta_y, float theta_x);
		static void QuatToV3DTheta(const Quat &q, Vector3D &v, float &theta);
		static void QuatPrint(const Quat &q, char *name);


		//2d参数化直线函数
		static void InitParmLine2D(const Point2D &pInit, const Point2D &pTerm, ParmLine2D &p);
		static void ComputeParmLine2D(ParmLine2D &p, float t, Point2D &pt);
		static int IntersectParmLines2D(ParmLine2D &p1, ParmLine2D &p2, Point2D &pt);

		//3d参数化直线函数
		static void InitParmLine3D(const Point3D &pInit, const Point3D &pTerm, ParmLine3D &p);
		static void ComputeParmLine3D(const ParmLine3D &p, float t, Point3D &pt);

		// 3d平面函数
		static void Plane3DInit(Plane3D &plane, const Point3D &p0, const Vector3D &normal, bool normalize);
		static float ComputePointInPlane3D(const Point3D &pt, const Plane3D &plane);
		static int IntersectParmLinePlane3D(const ParmLine3D &line, Plane3D &plane, float &t, Point3D &pt);

		static float cos_look[361];
		static float sin_look[361];

	};
}



#endif
