#include "T3DMath.h"

#include <math.h>
#include <amp_math.h>

#include "T3DLog.h"

namespace T3D {

	float CommonMath::sin_look[361];
	float CommonMath::cos_look[361];

	void CommonMath::BuildSinCosTables()
	{
		for (int i = 0; i < 361; ++i)
		{
			sin_look[i] = sinf(DEG_TO_RAN(i));
			cos_look[i] = cosf(DEG_TO_RAN(i));
		}
	}

	float CommonMath::FastSin(float theta)
	{
		theta = fmodf(theta, 360);
		if (theta < 0) theta += 360;

		int theta_int = (int)theta;
		float theta_frac = theta - theta_int;

		return sin_look[theta_int] + theta_frac * (sin_look[theta_int + 1] - sin_look[theta_int]);
	}

	float CommonMath::FastCos(float theta)
	{
		theta = fmodf(theta, 360);
		if (theta < 0) theta += 360;

		int theta_int = (int)theta;
		float theta_frac = theta - theta_int;

		return cos_look[theta_int] + theta_frac * (cos_look[theta_int + 1] - cos_look[theta_int]);
	}

	float CommonMath::FastDistance2D(float x, float y)
	{
		return sqrtf(x*x + y*y);
	}

	float CommonMath::FastDistance3D(float x, float y, float z)
	{
		return sqrtf(x*x + y*y + z*z);
	}

	void CommonMath::Polar2DToPoint2D(const Polar2D &polar, Point2D &point)
	{
		point.m_x = polar.m_r * FastCos(RAD_TO_DEG(polar.m_theta));
		point.m_y = polar.m_r * FastSin(RAD_TO_DEG(polar.m_theta));
	}

	void CommonMath::Point2DToPolar2D(const Point2D &point, Polar2D &polar)
	{
		polar.m_r = sqrt(point.m_x * point.m_x + point.m_y * point.m_y);
		polar.m_theta = atan2f(point.m_y, point.m_x);  //TODO 返回的是弧度
	}

	void CommonMath::Cylindrical3DToPoint3D(const Cylindrical3D &c3d, Point3D &point)
	{
		point.m_x = c3d.m_r * FastCos(RAD_TO_DEG(c3d.m_theta));
		point.m_y = c3d.m_r * FastSin(RAD_TO_DEG(c3d.m_theta));
		point.m_z = c3d.m_z;
	}

	void CommonMath::Point3DToCylindrical3D(const Point3D &point, Cylindrical3D &c3d)
	{
		c3d.m_r = sqrt(point.m_x * point.m_x + point.m_y * point.m_y);
		c3d.m_theta = atan2f(point.m_y, point.m_x);
		c3d.m_z = point.m_z;
	}

	void CommonMath::Spherical3DToPoint3D(const Spherical3D &s3d, Point3D &point)
	{
		point.m_z = s3d.m_p * FastCos(RAD_TO_DEG(s3d.m_theta));
		float xy_r = s3d.m_p * FastSin(RAD_TO_DEG(s3d.m_theta));
		point.m_x = xy_r * FastCos(RAD_TO_DEG(s3d.m_phi));
		point.m_y = xy_r * FastSin(RAD_TO_DEG(s3d.m_phi));
	}

	void CommonMath::Point3DToSpherical3D(const Point3D &point, Spherical3D &s3d)
	{
		s3d.m_p = sqrt(point.m_x * point.m_x + point.m_y * point.m_y + point.m_z * point.m_z);
		s3d.m_phi = atan2f(point.m_y, point.m_x);
		s3d.m_theta = acosf(point.m_z / s3d.m_p);
	}

	void CommonMath::Vector2DAdd(const Vector2D &va, const Vector2D &vb, Vector2D &vsum)
	{
		vsum.m_x = va.m_x + vb.m_x;
		vsum.m_y = va.m_y + vb.m_y;
	}
	
	void CommonMath::Vector3DAdd(const Vector3D &va, const Vector3D &vb, Vector3D &vsum)
	{
		vsum.m_x = va.m_x + vb.m_x;
		vsum.m_y = va.m_y + vb.m_y;
		vsum.m_z = va.m_z + vb.m_z;
	}

	void CommonMath::Vector4DAdd(const Vector4D &va, const Vector4D &vb, Vector4D &vsum)
	{
		vsum.m_x = va.m_x + vb.m_x;
		vsum.m_y = va.m_y + vb.m_y;
		vsum.m_z = va.m_z + vb.m_z;
		//w值不作处理
	}

	void CommonMath::Vector2DSub(const Vector2D &va, const Vector2D &vb, Vector2D &vsub)
	{
		vsub.m_x = va.m_x - vb.m_x;
		vsub.m_y = va.m_y - vb.m_y;
	}

	void CommonMath::Vector3DSub(const Vector3D &va, const Vector3D &vb, Vector3D &vsub)
	{
		vsub.m_x = va.m_x - vb.m_x;
		vsub.m_y = va.m_y - vb.m_y;
		vsub.m_z = va.m_z - vb.m_z;
	}

	void CommonMath::Vector4DSub(const Vector4D &va, const Vector4D &vb, Vector4D &vsub)
	{
		vsub.m_x = va.m_x - vb.m_x;
		vsub.m_y = va.m_y - vb.m_y;
		vsub.m_z = va.m_z - vb.m_z;
		//w值不作处理
	}

	void CommonMath::Vector2DScale(float scale, Vector2D &v)
	{
		v.m_x *= scale;
		v.m_y *= scale;
	}

	void CommonMath::Vector3DScale(float scale, Vector3D &v)
	{
		v.m_x *= scale;
		v.m_y *= scale;
		v.m_z *= scale;
		//w值不作处理
	}

	void CommonMath::Vector4DScale(float scale, Vector4D &v)
	{
		v.m_x *= scale;
		v.m_y *= scale;
		v.m_z *= scale;
	}

	float CommonMath::Vector2DDot(const Vector2D &va, const Vector2D &vb)
	{
		return va.m_x * vb.m_x + va.m_y * vb.m_y;
	}

	float CommonMath::Vector3DDot(const Vector3D &va, const Vector3D &vb)
	{
		return va.m_x * vb.m_x + va.m_y * vb.m_y + va.m_z * vb.m_z;
	}

	float CommonMath::Vector4DDot(const Vector4D &va, const Vector4D &vb)
	{
		return va.m_x * vb.m_x + va.m_y * vb.m_y + va.m_z * vb.m_z;  //w不作处理
	}

	void CommonMath::Vector3DCross(const Vector3D &va, const Vector3D &vb, Vector3D &vcross)
	{
		vcross.m_x = va.m_y * vb.m_z - va.m_z * vb.m_y;
		vcross.m_y = va.m_z * vb.m_x - va.m_x * vb.m_z;
		vcross.m_z = va.m_x * vb.m_y - va.m_y * vb.m_x;
	}

	void CommonMath::Vector4DCross(const Vector4D &va, const Vector4D &vb, Vector4D &vcross)
	{
		vcross.m_x = va.m_y * vb.m_z - va.m_z * vb.m_y;
		vcross.m_y = va.m_z * vb.m_x - va.m_x * vb.m_z;
		vcross.m_z = va.m_x * vb.m_y - va.m_y * vb.m_x;
		//w不作处理
	}

	float CommonMath::Vector2DLength(const Vector2D &v)
	{
		return sqrt(v.m_x * v.m_x + v.m_y * v.m_y);
	}

	float CommonMath::Vector3DLength(const Vector3D &v)
	{
		return sqrt(v.m_x * v.m_x + v.m_y * v.m_y + v.m_z * v.m_z);
	}

	float CommonMath::Vector4DLength(const Vector4D &v)
	{
		return sqrt(v.m_x * v.m_x + v.m_y * v.m_y + v.m_z * v.m_z);  //w不作处理
	}

	float CommonMath::Vector2DLengthFast(const Vector2D &v)
	{
		// TODO传说使用泰勒级数
		return 0;
	}

	float CommonMath::Vector3DLengthFast(const Vector3D &v)
	{
		// TODO传说使用泰勒级数
		return 0;
	}

	float CommonMath::Vector4DLengthFast(const Vector4D &v)
	{
		// TODO传说使用泰勒级数
		return 0;
	}

	void CommonMath::Vector2DNormalize(Vector2D &v)
	{
		float length = Vector2DLength(v);
		v.m_x /= length;
		v.m_y /= length;
	}

	void CommonMath::Vector3DNormalize(Vector3D &v)
	{
		float length = Vector3DLength(v);
		v.m_x /= length;
		v.m_y /= length;
		v.m_z /= length;
	}

	void CommonMath::Vector4DNormalize(Vector4D &v)
	{
		float length = Vector4DLength(v);
		v.m_x /= length;
		v.m_y /= length;
		v.m_z /= length;
		//w不作处理
	}

	void CommonMath::Vector2DBuild(const Vector2D &va, const Vector2D &vb, Vector2D &vbuild)
	{
		vbuild.m_x = vb.m_x - va.m_x;
		vbuild.m_y = vb.m_y - va.m_y;
	}

	void CommonMath::Vector3DBuild(const Vector3D &va, const Vector3D &vb, Vector3D &vbuild)
	{
		vbuild.m_x = vb.m_x - va.m_x;
		vbuild.m_y = vb.m_y - va.m_y;
		vbuild.m_z = vb.m_z - va.m_z;
	}

	void CommonMath::Vector4DBuild(const Vector4D &va, const Vector4D &vb, Vector4D &vbuild)
	{
		vbuild.m_x = vb.m_x - va.m_x;
		vbuild.m_y = vb.m_y - va.m_y;
		vbuild.m_z = vb.m_z - va.m_z;
		//w不作处理
	}

	float CommonMath::Vector2DCosTh(const Vector2D &va, const Vector2D &vb)
	{
		return Vector2DDot(va, vb) / (Vector2DLength(va) * Vector2DLength(vb));
	}

	float CommonMath::Vector3DCosTh(const Vector3D &va, const Vector3D &vb)
	{
		return Vector3DDot(va, vb) / (Vector3DLength(va) * Vector3DLength(vb));
	}

	float CommonMath::Vector4DCosTh(const Vector4D &va, const Vector4D &vb)
	{
		return Vector4DDot(va, vb) / (Vector4DLength(va) * Vector4DLength(vb));
	}

	void CommonMath::Vector2DPrint(const Vector2D &va, char *name)
	{
		Log::WriteError("%s, x=%f, y=%f", name, va.m_x, va.m_y);
	}

	void CommonMath::Vector3DPrint(const Vector3D &va, char *name)
	{
		Log::WriteError("%s, x=%f, y=%f, z=%f", name, va.m_x, va.m_y, va.m_z);
	}

	void CommonMath::Vector4DPrint(const Vector4D &va, char *name)
	{
		Log::WriteError("%s, x=%f, y=%f, z=%f, w=%f", name, va.m_x, va.m_y, va.m_z, va.m_w);
	}

	void CommonMath::Mat22Init(Matrix22 &matrix, float m00, float m01, float m10, float m11)
	{
		matrix.m_mat[0][0] = m00;
		matrix.m_mat[0][1] = m01;
		matrix.m_mat[1][0] = m10;
		matrix.m_mat[1][1] = m11;
	}

	void CommonMath::Mat22Add(const Matrix22 &ma, const Matrix22 &mb, Matrix22 &msum)
	{
		msum.m_mat[0][0] = ma.m_mat[0][0] + mb.m_mat[0][0];
		msum.m_mat[0][1] = ma.m_mat[0][1] + mb.m_mat[0][1];
		msum.m_mat[1][0] = ma.m_mat[1][0] + mb.m_mat[1][0];
		msum.m_mat[1][1] = ma.m_mat[1][1] + mb.m_mat[1][1];
	}

	void CommonMath::Mat22Mul(const Matrix22 &ma, const Matrix22 &mb, Matrix22 &mprod)
	{
		mprod.m_mat[0][0] = ma.m_mat[0][0] * mb.m_mat[0][0] + ma.m_mat[0][1] * mb.m_mat[1][0];
		mprod.m_mat[0][1] = ma.m_mat[0][0] * mb.m_mat[0][1] + ma.m_mat[0][1] * mb.m_mat[1][1];
		mprod.m_mat[1][0] = ma.m_mat[1][0] * mb.m_mat[0][0] + ma.m_mat[1][1] * mb.m_mat[1][0];
		mprod.m_mat[1][1] = ma.m_mat[1][0] * mb.m_mat[0][1] + ma.m_mat[1][1] * mb.m_mat[1][1];
	}

	int CommonMath::Solve22System(const Matrix22 & A, Matrix12 & X, const Matrix12 & B)
	{
		float det_A = Mat22Det(A);

		// test if det(a) is zero, if so then there is no solution
		if (fabs(det_A) < EPSILON_E5)
			return 1;

		// step 2: create x,y numerator matrices by taking A and
		// replacing each column of it with B(transpose) and solve
		Matrix22 work_mat; // working matrix

							// solve for x /////////////////

							// copy A into working matrix
		work_mat.InitWithMat22(A);

		// swap out column 0 (x column)
		//MAT_COLUMN_SWAP_2X2(&work_mat, 0, B);
		work_mat.m_mat[0][0] = B.m_mat[0][0];
		work_mat.m_mat[1][0] = B.m_mat[1][0];

		// compute determinate of A with B swapped into x column
		float det_ABx = Mat22Det(work_mat);

		// now solve for X00
		X.m_mat[0][0] = det_ABx / det_A;

		// solve for y /////////////////

		// copy A into working matrix
		work_mat.InitWithMat22(A);

		// swap out column 1 (y column)
		//MAT_COLUMN_SWAP_2X2(&work_mat, 1, B);
		work_mat.m_mat[0][1] = B.m_mat[0][1];
		work_mat.m_mat[1][1] = B.m_mat[1][1];

		// compute determinate of A with B swapped into y column
		float det_ABy = Mat22Det(work_mat);

		// now solve for X01
		X.m_mat[0][1] = det_ABy / det_A;

		// return success
		return 0;
	}

	void CommonMath::Mat12MulMat32(const Matrix12 &ma, const Matrix32 &mb, Matrix12 &mprod)
	{
		mprod.m_mat[0][0] = ma.m_mat[0][0] * mb.m_mat[0][0] + ma.m_mat[0][1] * mb.m_mat[1][0] + 1 * mb.m_mat[2][0];
		mprod.m_mat[0][1] = ma.m_mat[0][0] * mb.m_mat[0][1] + ma.m_mat[0][1] * mb.m_mat[1][1] + 1 * mb.m_mat[2][1];
	}

	float CommonMath::Mat22Det(const Matrix22 &m)
	{
		return m.m_mat[0][0] * m.m_mat[1][1] - m.m_mat[1][0] * m.m_mat[0][1];
	}

	int CommonMath::Mat22Inverse(const Matrix22 &m, Matrix22 &mi)
	{
		float det = m.m_mat[0][0] * m.m_mat[1][1] - m.m_mat[0][1] * m.m_mat[1][0];  //计算行列式
		if (fabs(det) < EPSILON_E5) return 1;

		float det_inv = 1.0 / det;
		mi.m_mat[0][0] = m.m_mat[1][1] * det_inv;
		mi.m_mat[0][1] = m.m_mat[0][1] * det_inv;
		mi.m_mat[1][0] = m.m_mat[1][0] * det_inv;
		mi.m_mat[1][1] = m.m_mat[0][0] * det_inv;

		return 0;
	}

	void CommonMath::PrintMat22(const Matrix22 &matrix, char *name)
	{
		Log::WriteError("%s, 00=%f, 01=%f, 10=%f, 11=%f", name, matrix.m_mat[0][0], matrix.m_mat[0][1], matrix.m_mat[1][0], matrix.m_mat[1][1]);
	}

	void CommonMath::Mat33Init(Matrix33 &m, float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
	{
		m.m_mat[0][0] = m00;
		m.m_mat[0][1] = m01;
		m.m_mat[0][2] = m02;
		m.m_mat[1][0] = m10;
		m.m_mat[1][1] = m11;
		m.m_mat[1][2] = m12;
		m.m_mat[2][0] = m20;
		m.m_mat[2][1] = m21;
		m.m_mat[2][2] = m22;
	}

	int CommonMath::Mat32Init(Matrix32 &ma, float m00, float m01, float m10, float m11, float m20, float m21)
	{
		ma.m_mat[0][0] = m00;
		ma.m_mat[0][1] = m01;
		ma.m_mat[1][0] = m10;
		ma.m_mat[1][1] = m11;
		ma.m_mat[2][0] = m20;
		ma.m_mat[2][1] = m21;
	}


	void CommonMath::Mat33Add(const Matrix33 &ma, const Matrix33 &mb, Matrix33 &msum)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				msum.m_mat[i][j] = ma.m_mat[i][j] + mb.m_mat[i][j];
			}
		}
	}
	
	void CommonMath::Vec3MulMat33(const Vector3D &va, const Matrix33 &mb, Vector3D &vprod)
	{
		vprod.m_x = va.m_x * mb.m_mat[0][0] + va.m_y * mb.m_mat[1][0] + va.m_z * mb.m_mat[2][0];
		vprod.m_y = va.m_x * mb.m_mat[0][1] + va.m_y * mb.m_mat[1][1] + va.m_z * mb.m_mat[2][1];
		vprod.m_z = va.m_x * mb.m_mat[0][2] + va.m_y * mb.m_mat[1][2] + va.m_z * mb.m_mat[2][2];
	}

	int CommonMath::Mat13MulMat33(const Matrix13 &ma, const Matrix33 &mb, Matrix13 &mprod)
	{
		mprod.m_mat[0][0] = ma.m_mat[0][0] * mb.m_mat[0][0] + ma.m_mat[0][1] * mb.m_mat[1][0] + ma.m_mat[0][2] * mb.m_mat[2][0];
		mprod.m_mat[0][1] = ma.m_mat[0][0] * mb.m_mat[0][1] + ma.m_mat[0][1] * mb.m_mat[1][1] + ma.m_mat[0][2] * mb.m_mat[2][1];
		mprod.m_mat[0][2] = ma.m_mat[0][0] * mb.m_mat[0][2] + ma.m_mat[0][1] * mb.m_mat[1][2] + ma.m_mat[0][2] * mb.m_mat[2][2];
	}

	void CommonMath::Mat33MulMat33(const Matrix33 &ma, const Matrix33 &mb, Matrix33 &mprod)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				mprod.m_mat[i][j] = ma.m_mat[i][0] * mb.m_mat[0][j] + ma.m_mat[i][1] * mb.m_mat[1][j] + ma.m_mat[i][2] * mb.m_mat[2][j];
			}
		}
	}

	float CommonMath::Mat33Det(const Matrix33 &m)
	{
		return	m.m_mat[0][0] * m.m_mat[1][1] * m.m_mat[2][2] +
				m.m_mat[0][1] * m.m_mat[1][2] * m.m_mat[0][3] +
				m.m_mat[0][2] * m.m_mat[1][0] * m.m_mat[2][1] -
				m.m_mat[0][2] * m.m_mat[1][1] * m.m_mat[2][0] -
				m.m_mat[1][2] * m.m_mat[2][1] * m.m_mat[0][0] -
				m.m_mat[2][2] * m.m_mat[0][1] * m.m_mat[1][0];
	}

	int CommonMath::Mat33Inverse(const Matrix33 &m, Matrix33 &mi)
	{
		float det = Mat33Det(m);
		if (fabs(det) < EPSILON_E5) return 1;

		float det_inv = 1.0 / det;

		mi.m_mat[0][0] = det_inv*(m.m_mat[1][1] * m.m_mat[2][2] - m.m_mat[2][1] * m.m_mat[1][2]);
		mi.m_mat[1][0] = -det_inv*(m.m_mat[1][0] * m.m_mat[2][2] - m.m_mat[2][0] * m.m_mat[1][2]);
		mi.m_mat[2][0] = det_inv*(m.m_mat[1][0] * m.m_mat[2][1] - m.m_mat[2][0] * m.m_mat[1][1]);

		mi.m_mat[0][1] = -det_inv*(m.m_mat[0][1] * m.m_mat[2][2] - m.m_mat[2][1] * m.m_mat[0][2]);
		mi.m_mat[1][1] = det_inv*(m.m_mat[0][0] * m.m_mat[2][2] - m.m_mat[2][0] * m.m_mat[0][2]);
		mi.m_mat[2][1] = -det_inv*(m.m_mat[0][0] * m.m_mat[2][1] - m.m_mat[2][0] * m.m_mat[0][1]);

		mi.m_mat[0][2] = det_inv*(m.m_mat[0][1] * m.m_mat[1][2] - m.m_mat[1][1] * m.m_mat[0][2]);
		mi.m_mat[1][2] = -det_inv*(m.m_mat[0][0] * m.m_mat[1][2] - m.m_mat[1][0] * m.m_mat[0][2]);
		mi.m_mat[2][2] = det_inv*(m.m_mat[0][0] * m.m_mat[1][1] - m.m_mat[1][0] * m.m_mat[0][1]);

		return 0;
	}

	int CommonMath::SolveMat33System(Matrix33 & A, Matrix13 & X, Matrix13 & B)
	{
		// step 1: compute determinate of A
		float det_A = Mat33Det(A);

		// test if det(a) is zero, if so then there is no solution
		if (fabs(det_A) < EPSILON_E5)
			return(0);

		// step 2: create x,y,z numerator matrices by taking A and
		// replacing each column of it with B(transpose) and solve
		Matrix33 work_mat; // working matrix

							// solve for x /////////////////

							// copy A into working matrix
		work_mat.InitWithMat33(A);

		// swap out column 0 (x column)
		//MAT_COLUMN_SWAP_3X3(&work_mat, 0, B);
		work_mat.m_mat[0][0] = B.m_mat[0][0];
		work_mat.m_mat[1][0] = B.m_mat[1][0];
		work_mat.m_mat[2][0] = B.m_mat[2][0];

		// compute determinate of A with B swapped into x column
		float det_ABx = Mat33Det(work_mat);

		// now solve for X00
		X.m_mat[0][0] = det_ABx / det_A;

		// solve for y /////////////////

		// copy A into working matrix
		work_mat.InitWithMat33(A);

		// swap out column 1 (y column)
		//MAT_COLUMN_SWAP_3X3(&work_mat, 1, B);
		work_mat.m_mat[0][1] = B.m_mat[0][1];
		work_mat.m_mat[1][1] = B.m_mat[1][1];
		work_mat.m_mat[2][1] = B.m_mat[2][1];

		// compute determinate of A with B swapped into y column
		float det_ABy = Mat33Det(work_mat);

		// now solve for X01
		X.m_mat[0][1] = det_ABy / det_A;

		// solve for z /////////////////

		// copy A into working matrix
		work_mat.InitWithMat33(A);

		// swap out column 2 (z column)
		//MAT_COLUMN_SWAP_3X3(&work_mat, 2, B);
		work_mat.m_mat[0][2] = B.m_mat[0][2];
		work_mat.m_mat[1][2] = B.m_mat[1][2];
		work_mat.m_mat[2][2] = B.m_mat[2][2];

		// compute determinate of A with B swapped into z column
		float det_ABz = Mat33Det(work_mat);

		// now solve for X02
		X.m_mat[0][2] = det_ABz / det_A;

		// return success
		return 0;
	}

	void CommonMath::PrintMat33(const Matrix33 &ma, char *name)
	{
		Log::WriteError("%s", name);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				Log::WriteError(", %d%d=%f", i, j, ma.m_mat[i][j]);
			}
		}
		Log::WriteError("\n");
	}

	void CommonMath::Mat44Add(const Matrix44 & ma, const Matrix44 & mb, Matrix44 & msum)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				msum.m_mat[i][j] = ma.m_mat[i][j] + mb.m_mat[i][j];
			}
		}
	}

	void CommonMath::Mat44Mul(const Matrix44 & ma, const Matrix44 & mb, Matrix44 & mprod)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mprod.m_mat[i][j] = ma.m_mat[i][0] * mb.m_mat[0][j] + ma.m_mat[i][1] * mb.m_mat[1][j] + ma.m_mat[i][2] * mb.m_mat[2][j] + ma.m_mat[i][3] * mb.m_mat[3][j];
			}
		}
	}

	void CommonMath::Mat14MulMat44(const Matrix14 & ma, const Matrix44 & mb, Matrix14 & mprod)
	{
		mprod.m_mat[0][0] = ma.m_mat[0][0] * mb.m_mat[0][0] + ma.m_mat[0][1] * mb.m_mat[1][0] + ma.m_mat[0][2] * mb.m_mat[2][0] + ma.m_mat[0][3] * mb.m_mat[3][0];
		mprod.m_mat[0][1] = ma.m_mat[0][0] * mb.m_mat[0][1] + ma.m_mat[0][1] * mb.m_mat[1][1] + ma.m_mat[0][2] * mb.m_mat[2][1] + ma.m_mat[0][3] * mb.m_mat[3][1];
		mprod.m_mat[0][2] = ma.m_mat[0][0] * mb.m_mat[0][2] + ma.m_mat[0][1] * mb.m_mat[1][2] + ma.m_mat[0][2] * mb.m_mat[2][2] + ma.m_mat[0][3] * mb.m_mat[3][2];
		mprod.m_mat[0][3] = ma.m_mat[0][0] * mb.m_mat[0][3] + ma.m_mat[0][1] * mb.m_mat[1][3] + ma.m_mat[0][2] * mb.m_mat[2][3] + ma.m_mat[0][3] * mb.m_mat[3][3];
	}

	void CommonMath::V3dMulMat44(const Vector3D & va, const Matrix44 & mb, Vector3D & vprod)
	{
		vprod.m_x = va.m_x * mb.m_mat[0][0] + va.m_y * mb.m_mat[1][0] + va.m_z * mb.m_mat[2][0] + 1.0 * mb.m_mat[3][0];
		vprod.m_y = va.m_x * mb.m_mat[0][1] + va.m_y * mb.m_mat[1][1] + va.m_z * mb.m_mat[2][1] + 1.0 * mb.m_mat[3][1];
		vprod.m_z = va.m_x * mb.m_mat[0][2] + va.m_y * mb.m_mat[1][2] + va.m_z * mb.m_mat[2][2] + 1.0 * mb.m_mat[3][2];
	}

	void CommonMath::V3dMulMat43(const Vector3D & va, const Matrix43 & mb, Vector3D & vprod)
	{
		vprod.m_x = va.m_x * mb.m_mat[0][0] + va.m_y * mb.m_mat[1][0] + va.m_z * mb.m_mat[2][0] + 1.0 * mb.m_mat[3][0];
		vprod.m_y = va.m_x * mb.m_mat[0][1] + va.m_y * mb.m_mat[1][1] + va.m_z * mb.m_mat[2][1] + 1.0 * mb.m_mat[3][1];
		vprod.m_z = va.m_x * mb.m_mat[0][2] + va.m_y * mb.m_mat[1][2] + va.m_z * mb.m_mat[2][2] + 1.0 * mb.m_mat[3][2];
	}

	void CommonMath::V4dMulMat44(const Vector4D & va, const Matrix44 & mb, Vector4D & vprod)
	{
		vprod.m_x = va.m_x * mb.m_mat[0][0] + va.m_y * mb.m_mat[1][0] + va.m_z * mb.m_mat[2][0] + va.m_w * mb.m_mat[3][0];
		vprod.m_y = va.m_x * mb.m_mat[0][1] + va.m_y * mb.m_mat[1][1] + va.m_z * mb.m_mat[2][1] + va.m_w * mb.m_mat[3][1];
		vprod.m_z = va.m_x * mb.m_mat[0][2] + va.m_y * mb.m_mat[1][2] + va.m_z * mb.m_mat[2][2] + va.m_w * mb.m_mat[3][2];
		vprod.m_w = va.m_x * mb.m_mat[0][3] + va.m_y * mb.m_mat[1][3] + va.m_z * mb.m_mat[2][3] + va.m_w * mb.m_mat[3][3];
	}

	void CommonMath::V4dMulMat43(const Vector4D & va, const Matrix43 & mb, Vector4D & vprod)
	{
		vprod.m_x = va.m_x * mb.m_mat[0][0] + va.m_y * mb.m_mat[1][0] + va.m_z * mb.m_mat[2][0] + va.m_w * mb.m_mat[3][0];
		vprod.m_y = va.m_x * mb.m_mat[0][1] + va.m_y * mb.m_mat[1][1] + va.m_z * mb.m_mat[2][1] + va.m_w * mb.m_mat[3][1];
		vprod.m_z = va.m_x * mb.m_mat[0][2] + va.m_y * mb.m_mat[1][2] + va.m_z * mb.m_mat[2][2] + va.m_w * mb.m_mat[3][2];
		vprod.m_w = va.m_w;
	}

	int CommonMath::Mat44Inverse(const Matrix44 & m, Matrix44 & mi)
	{
		float det = (m.m_mat[0][0] * (m.m_mat[1][1] * m.m_mat[2][2] - m.m_mat[1][2] * m.m_mat[2][1]) -
			m.m_mat[0][1] * (m.m_mat[1][0] * m.m_mat[2][2] - m.m_mat[1][2] * m.m_mat[2][0]) +
			m.m_mat[0][2] * (m.m_mat[1][0] * m.m_mat[2][1] - m.m_mat[1][1] * m.m_mat[2][0]));

		// test determinate to see if it's 0
		if (fabs(det) < EPSILON_E5)
			return(1);

		float det_inv = 1.0f / det;

		mi.m_mat[0][0] = det_inv * (m.m_mat[1][1] * m.m_mat[2][2] - m.m_mat[1][2] * m.m_mat[2][1]);
		mi.m_mat[0][1] = -det_inv * (m.m_mat[0][1] * m.m_mat[2][2] - m.m_mat[0][2] * m.m_mat[2][1]);
		mi.m_mat[0][2] = det_inv * (m.m_mat[0][1] * m.m_mat[1][2] - m.m_mat[0][2] * m.m_mat[1][1]);
		mi.m_mat[0][3] = 0.0f; // always 0

		mi.m_mat[1][0] = -det_inv * (m.m_mat[1][0] * m.m_mat[2][2] - m.m_mat[1][2] * m.m_mat[2][0]);
		mi.m_mat[1][1] = det_inv * (m.m_mat[0][0] * m.m_mat[2][2] - m.m_mat[0][2] * m.m_mat[2][0]);
		mi.m_mat[1][2] = -det_inv * (m.m_mat[0][0] * m.m_mat[1][2] - m.m_mat[0][2] * m.m_mat[1][0]);
		mi.m_mat[1][3] = 0.0f; // always 0

		mi.m_mat[2][0] = det_inv * (m.m_mat[1][0] * m.m_mat[2][1] - m.m_mat[1][1] * m.m_mat[2][0]);
		mi.m_mat[2][1] = -det_inv * (m.m_mat[0][0] * m.m_mat[2][1] - m.m_mat[0][1] * m.m_mat[2][0]);
		mi.m_mat[2][2] = det_inv * (m.m_mat[0][0] * m.m_mat[1][1] - m.m_mat[0][1] * m.m_mat[1][0]);
		mi.m_mat[2][3] = 0.0f; // always 0

		mi.m_mat[3][0] = -(m.m_mat[3][0] * mi.m_mat[0][0] + m.m_mat[3][1] * mi.m_mat[1][0] + m.m_mat[3][2] * mi.m_mat[2][0]);
		mi.m_mat[3][1] = -(m.m_mat[3][0] * mi.m_mat[0][1] + m.m_mat[3][1] * mi.m_mat[1][1] + m.m_mat[3][2] * mi.m_mat[2][1]);
		mi.m_mat[3][2] = -(m.m_mat[3][0] * mi.m_mat[0][2] + m.m_mat[3][1] * mi.m_mat[1][2] + m.m_mat[3][2] * mi.m_mat[2][2]);
		mi.m_mat[3][3] = 1.0f; // always 0

		return 0;
	}

	void CommonMath::Mat44Init(Matrix44 & m, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
	{
		m.m_mat[0][0] = m00;
		m.m_mat[0][1] = m01;
		m.m_mat[0][2] = m02;
		m.m_mat[0][3] = m03;
		m.m_mat[1][0] = m10;
		m.m_mat[1][1] = m11;
		m.m_mat[1][2] = m12;
		m.m_mat[1][3] = m13;
		m.m_mat[2][0] = m20;
		m.m_mat[2][1] = m21;
		m.m_mat[2][2] = m22;
		m.m_mat[2][3] = m23;
		m.m_mat[3][0] = m30;
		m.m_mat[3][1] = m31;
		m.m_mat[3][2] = m32;
		m.m_mat[3][3] = m33;
	}

	void CommonMath::PrintMat44(const Matrix44 & ma, char * name)
	{
		Log::WriteError("%s", name);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				Log::WriteError(", %d%d=%f", i, j, ma.m_mat[i][j]);
			}
		}
		Log::WriteError("\n");
	}

	void CommonMath::InitParmLine2D(const Point2D & pInit, const Point2D & pTerm, ParmLine2D & p)
	{
		p.m_p0 = pInit;
		p.m_p1 = pTerm;
		p.m_vec.m_x = pTerm.m_x - pInit.m_x;
		p.m_vec.m_y = pTerm.m_y - pInit.m_y;
	}

	void CommonMath::ComputeParmLine2D(ParmLine2D & p, float t, Point2D & pt)
	{
		pt.m_x = p.m_p0.m_x + p.m_vec.m_x * t;
		pt.m_y = p.m_p0.m_y + p.m_vec.m_y * t;
	}

	int CommonMath::IntersectParmLines2D(ParmLine2D & p1, ParmLine2D & p2, Point2D & pt)
	{
		//判断是否平行（计算行列式）
		float det_p1p2 = p1.m_vec.m_x * p2.m_vec.m_y - p1.m_vec.m_y * p2.m_vec.m_x;
		if (det_p1p2 < EPSILON_E5) return PARM_LINE_NO_INTERSECT;

		float t1, t2;
		t1 = (p2.m_vec.m_x * (p1.m_p0.m_y - p2.m_p0.m_y) - p2.m_vec.m_y*(p1.m_p0.m_x - p2.m_p0.m_x)) / det_p1p2;
		t2 = (p1.m_vec.m_x * (p1.m_p0.m_y - p2.m_p0.m_y) - p1.m_vec.m_y*(p1.m_p0.m_x - p2.m_p0.m_x)) / det_p1p2;

		ComputeParmLine2D(p1, t1, pt);

		if (t1 >= 0 && t1 <= 1 || t2 >= 0 && t2 <= 1)
		{
			return PARM_LINE_INTERSECT_IN_SEGMENT;
		}
		else
		{
			return PARM_LINE_INTERSECT_OUT_SEGMENT;
		}

		return 0;
	}

	void CommonMath::InitParmLine3D(const Point3D & pInit, const Point3D & pTerm, ParmLine3D & p)
	{
		p.m_p0 = pInit;
		p.m_p1 = pTerm;
		p.m_vec.m_x = pTerm.m_x - pInit.m_x;
		p.m_vec.m_y = pTerm.m_y - pInit.m_y;
		p.m_vec.m_z = pTerm.m_z - pInit.m_z;
	}

	void CommonMath::ComputeParmLine3D(const ParmLine3D & p, float t, Point3D & pt)
	{
		pt.m_x = p.m_p0.m_x * t;
		pt.m_y = p.m_p0.m_y * t;
		pt.m_z = p.m_p0.m_z * t;
	}

	void CommonMath::Plane3DInit(Plane3D & plane, const Point3D & p0, const Vector3D & normal, bool normalize)
	{
		plane.m_p0 = p0;
		plane.m_normal = normal;
		if (normalize)
		{
			Vector3DNormalize(plane.m_normal);
		}
	}

	float CommonMath::ComputePointInPlane3D(const Point3D & pt, const Plane3D & plane)
	{
		float hs = plane.m_normal.m_x * (plane.m_p0.m_x - pt.m_x) + plane.m_normal.m_y * (plane.m_p0.m_y - pt.m_y) + plane.m_normal.m_z * (plane.m_p0.m_z - pt.m_z);

		return hs;
	}

	int CommonMath::IntersectParmLinePlane3D(const ParmLine3D & line, Plane3D & plane, float & t, Point3D & pt)
	{
		//判断是否平行
		float plane_dot_line = Vector3DDot(line.m_vec, plane.m_normal);
		if (fabs(plane_dot_line) < EPSILON_E5) return PARM_LINE_NO_INTERSECT;

		float t = -(plane.m_normal.m_x * line.m_p0.m_x +
			plane.m_normal.m_y * line.m_p0.m_y +
			plane.m_normal.m_z * line.m_p0.m_z -
			plane.m_normal.m_x * plane.m_p0.m_x -
			plane.m_normal.m_y * plane.m_p0.m_y -
			plane.m_normal.m_z * plane.m_p0.m_z) / plane_dot_line;

		pt.m_x = line.m_p0.m_x + line.m_vec.m_x * t;
		pt.m_y = line.m_p0.m_y + line.m_vec.m_y * t;
		pt.m_z = line.m_p0.m_z + line.m_vec.m_z * t;

		if (t >= 0 && t <= 1.0)
		{
			return PARM_LINE_INTERSECT_IN_SEGMENT;
		}
		else
		{
			return PARM_LINE_INTERSECT_OUT_SEGMENT;
		}
	}
	void CommonMath::V3DThetaToQuat(Quat & q, const Vector3D & v, float theta)
	{
		//使用3d向量和一个角度来初始化一个四元数

		//方向向量必须是单位向量，角度的单位是弧度
		float theta_div_2 = (0.5) * theta;
		
		//计算四元数
		float sinf_theta = sinf(theta_div_2);

		q.m_q0 = sinf_theta * v.m_x;
		q.m_qv.m_x = sinf_theta * v.m_y;
		q.m_qv.m_y = sinf_theta * v.m_z;
		q.m_qv.m_z = cosf(theta_div_2);
	}

	void CommonMath::V4DThetaToQuat( Quat &q, const Vector4D &v, float theta )
	{
		//使用3d向量和一个角度来初始化一个四元数

		//方向向量必须是单位向量，角度的单位是弧度
		float theta_div_2 = (0.5) * theta;

		//计算四元数
		float sinf_theta = sinf(theta_div_2);

		q.m_q0 = sinf_theta * v.m_x;
		q.m_qv.m_x = sinf_theta * v.m_y;
		q.m_qv.m_y = sinf_theta * v.m_z;
		q.m_qv.m_z = cosf(theta_div_2);
	}

	void CommonMath::EulerZYXToQuat( Quat &q, float theta_z, float theta_y, float theta_x )
	{
		//这个函数根据绕x, y, z的旋转的角度，创建一个的zyx顺序进行旋转的四元数 应该还有11个根据旋转角度创建四元数的函数

		//预先计算一些值
		float cos_z_2 = 0.5 * cosf(theta_z);
		float cos_y_2 = 0.5 * cosf(theta_y);
		float cos_x_2 = 0.5 * cosf(theta_x);

		float sin_z_2 = 0.5 * sinf(theta_z);
		float sin_y_2 = 0.5 * sinf(theta_y);
		float sin_x_2 = 0.5 * sinf(theta_x); 

		//计算四元数
		q.m_q0 = cos_z_2 * cos_y_2 * cos_x_2 + sin_x_2 * sin_z_2 * sin_y_2;
		q.m_qv.m_x = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_x_2 * cos_x_2;
		q.m_qv.m_y = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_x_2 * sin_x_2;
		q.m_qv.m_z = sin_z_2 * cos_y_2 * cos_x_2 + cos_z_2 * sin_y_2 * sin_x_2;
	}

	void CommonMath::QuatToV3DTheta(const Quat & q, Vector3D & v, float & theta)
	{
		//将一个单位四元数转化为一个单位方向向量和一个绕该向量旋转的角度

		theta = acosf(q.m_q0);

		float sinf_theta_inv = 1.0 / sinf(theta);
		v.m_x = q.m_qv.m_x * sinf_theta_inv;
		v.m_y = q.m_qv.m_y * sinf_theta_inv;
		v.m_z = q.m_qv.m_z * sinf_theta_inv;

		theta *= 2;
	}

	void CommonMath::QuatPrint(const Quat & q, char * name)
	{
		Log::WriteError("%s, w=%d, x=%d, y=%d, z=%d", name, q.m_q0, q.m_qv.m_x, q.m_qv.m_y, q.m_qv.m_z);
	}

	void CommonMath::QuatAdd(const Quat & q1, const Quat & q2, Quat & qsum)
	{
		qsum.m_q0 = q1.m_q0 + q2.m_q0;
		Vector3DAdd(q1.m_qv, q2.m_qv, qsum.m_qv);
	}
	void CommonMath::QuatSub(const Quat & q1, const Quat & q2, Quat & qdiff)
	{
		qdiff.m_q0 = q1.m_q0 - q2.m_q0;
		Vector3DSub(q1.m_qv, q2.m_qv, qdiff.m_qv);
	}
	void CommonMath::QuatConjugate(const Quat & q1, Quat & qconj)
	{
		qconj.m_q0 = q1.m_q0;
		qconj.m_qv.m_x = q1.m_qv.m_x;
		qconj.m_qv.m_y = q1.m_qv.m_y;
		qconj.m_qv.m_z = q1.m_qv.m_z;
	}
	void CommonMath::QuatScale(const Quat & q, float scale, Quat & qs)
	{
		qs.m_q0 = q.m_q0 * scale;
		qs.m_qv.InitWithVec3(qs.m_qv);
		Vector3DScale(scale, qs.m_qv);
	}
	float CommonMath::QuatNorm(const Quat & q)
	{
		return sqrtf(q.m_q0 * q.m_q0 + q.m_qv.m_x * q.m_qv.m_x + q.m_qv.m_y * q.m_qv.m_y + q.m_qv.m_z * q.m_qv.m_z);
	}
	void CommonMath::QuatNormalize(const Quat & q, Quat & qn)
	{
		float qlength = QuatNorm(q);
		qn.m_q0 = q.m_q0 / qlength;
		qn.m_qv.m_x = q.m_qv.m_x / qlength;
		qn.m_qv.m_y = q.m_qv.m_y / qlength;
		qn.m_qv.m_z = q.m_qv.m_z / qlength;
	}
	void CommonMath::QuatUnitInverse(const Quat & q, Quat & qi)
	{
		qi.m_q0 = q.m_q0;
		qi.m_qv.InitWithVec3(q.m_qv);
		Vector3DScale(-1, qi.m_qv);
	}
	void CommonMath::QuatInverse(const Quat & q, Quat & qi)
	{
		float norm2_inv = 1.0 / (q.m_q0 * q.m_q0 + q.m_qv.m_x * q.m_qv.m_x + q.m_qv.m_y * q.m_qv.m_y + q.m_qv.m_z * q.m_qv.m_z);

		qi.m_q0 = q.m_q0 * norm2_inv;
		qi.m_qv.InitWithVec3(q.m_qv);
		Vector3DScale(norm2_inv, qi.m_qv);
	}
	void CommonMath::QuatMul(const Quat & q1, const Quat & q2, Quat & qprod)
	{
		float prd_0 = (q1.m_qv.m_z - q1.m_qv.m_y) * (q2.m_qv.m_y - q2.m_qv.m_z);
		float prd_1 = (q1.m_q0 + q1.m_qv.m_x) * (q2.m_q0 + q2.m_qv.m_x);
		float prd_2 = (q1.m_q0 - q1.m_qv.m_x) * (q2.m_qv.m_y + q2.m_qv.m_z);
		float prd_3 = (q1.m_qv.m_y + q1.m_qv.m_z) * (q2.m_q0 - q2.m_qv.m_x);
		float prd_4 = (q1.m_qv.m_z - q1.m_qv.m_x) * (q2.m_qv.m_x - q2.m_qv.m_y);
		float prd_5 = (q1.m_qv.m_z + q1.m_qv.m_x) * (q2.m_qv.m_x + q2.m_qv.m_y);
		float prd_6 = (q1.m_q0 + q1.m_qv.m_y) * (q2.m_q0 - q2.m_qv.m_z);
		float prd_7 = (q1.m_q0 - q1.m_qv.m_y) * (q2.m_q0 + q2.m_qv.m_z);

		float prd_8 = prd_5 + prd_6 + prd_7;
		float prd_9 = 0.5 * (prd_4 + prd_8);

		// and finally build up the result with the temporary products

		qprod.m_q0 = prd_0 + prd_9 - prd_5;
		qprod.m_qv.m_x = prd_1 + prd_9 - prd_8;
		qprod.m_qv.m_y = prd_2 + prd_9 - prd_7;
		qprod.m_qv.m_z = prd_3 + prd_9 - prd_6;
	}
	void CommonMath::QuatTripleProduct(const Quat & q1, const Quat & q2, const Quat & q3, Quat & qprod)
	{
		Quat qtmp;
		QuatMul(q1, q2, qtmp);
		QuatMul(qtmp, q3, qprod);
	}
}