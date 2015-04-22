#ifndef Matrix_h
#define Matrix_h

// Unit Matrix
const double Unit_M4x4[4][4] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

const double Unit_M4x3[4][3] = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	0, 0, 0
};

const double Unit_M3x3[3][3] = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

const double Unit_M2x2[2][2] = {
	1, 0,
	0, 1
};

struct Matrix1x4
{
	double v[4];

	// Constructor
	Matrix1x4() = default;
	~Matrix1x4() = default;
	Matrix1x4(const Matrix1x4& m) { *this = m; }
	Matrix1x4(double m0, double m1, double m2, double m3);

	// Methods
	void zero();
	void init(double m0, double m1, double m2, double m3);

	// override operator
	Matrix1x4& operator=(const Matrix1x4& m);
};
typedef Matrix1x4* PMatrix1x4;

struct Matrix4x3
{
	double v[4][3];

	// Constructor
	Matrix4x3() = default;
	~Matrix4x3() = default;
	Matrix4x3(const Matrix4x3& m) { *this = m; }
	Matrix4x3(double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22,
		double m30, double m31, double m32);

	// methods
	void zero();
	void init(double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22,
		double m30, double m31, double m32);
	void unit();
	Vector3D mul(Vector3D* vec);
	Vector4D mul(Vector4D* vec);
	void swap(Matrix1x4* m, int c);

	// override operator
	Matrix4x3& operator=(const Matrix4x3& m);
};
typedef Matrix4x3* PMatrix4x3;

struct Matrix4x4
{
	double v[4][4];

	// Constructor
	Matrix4x4() = default;
	~Matrix4x4() = default;
	Matrix4x4(const Matrix4x4& m) { *this = m; }
	Matrix4x4(double m00, double m01, double m02, double m03,
		double m10, double m11, double m12, double m13,
		double m20, double m21, double m22, double m23,
		double m30, double m31, double m32, double m33);

	// Basic methods
	void init(double m00, double m01, double m02, double m03,
		double m10, double m11, double m12, double m13,
		double m20, double m21, double m22, double m23,
		double m30, double m31, double m32, double m33);
	void zero();
	void unit();
	void transpose();
	void swap(Matrix1x4* m, int c);
	double simple_det();
	void build(double theta_x, double theta_y, double theta_z);

	Matrix4x4 inverse();
	Matrix1x4 mul(Matrix1x4* m);
	Vector3D mul(Vector3D* vec);
	Vector4D mul(Vector4D* vec);
	Vertex4D mul(Vertex4D* vertex);

	// override operator
	Matrix4x4& operator=(const Matrix4x4& m);
	Matrix4x4 operator+(const Matrix4x4& m);
	Matrix4x4& operator+=(const Matrix4x4& m);
	Matrix4x4 operator*(const Matrix4x4& m);
	Matrix4x4& operator*=(const Matrix4x4& m);

};
typedef Matrix4x4* PMatrix4x4;

struct Matrix1x3
{
	double v[3];

	// Constructor
	Matrix1x3() = default;
	~Matrix1x3() = default;
	Matrix1x3(const Matrix1x3& m) { *this = m; }
	Matrix1x3(double m0, double m1, double m2);

	// basic methods
	void zero();
	void init(double m0, double m1, double m2);

	// override operator
	Matrix1x3& operator=(const Matrix1x3& m);
};
typedef Matrix1x3* PMatrix1x3;

struct Matrix3x2
{
	double v[3][2];

	// Constructor
	Matrix3x2() = default;
	~Matrix3x2() = default;
	Matrix3x2(const Matrix3x2& m) { *this = m; }
	Matrix3x2(double m00, double m01, double m10, double m11, double m20, double m21);

	// basic methods
	void zero();
	void init(double m00, double m01, double m10, double m11, double m20, double m21);

	// override operator
	Matrix3x2& operator=(const Matrix3x2& m);
};
typedef Matrix3x2* PMatrix3x2;

struct Matrix3x3
{
	double v[3][3];

	// Constructor
	Matrix3x3() = default;
	~Matrix3x3() = default;
	Matrix3x3(const Matrix3x3& m) { *this = m; }
	Matrix3x3(double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22);

	// basic methods
	void zero();
	void init(double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22);
	void unit();
	void transpose();
	void swap(Matrix1x3* m, int c);
	double det();
	Matrix3x3 inverse();

	// override operator
	Matrix3x3& operator=(const Matrix3x3& m);
	Matrix3x3 operator+(const Matrix3x3& m);
	Matrix3x3& operator+=(const Matrix3x3& m);
	Matrix3x3 operator*(const Matrix3x3& m);
	Matrix3x3& operator*=(const Matrix3x3& m);
};
typedef Matrix3x3* PMatrix3x3;

struct Matrix1x2
{
	double v[2];

	// Constructor
	Matrix1x2() = default;
	~Matrix1x2() = default;
	Matrix1x2(const Matrix1x2& m) { *this = m; }
	Matrix1x2(double m0, double m1);

	// basic methods
	void zero();
	void init(double m0, double m1);
	void mul_3x2(const Matrix3x2* m);

	// override operator
	Matrix1x2& operator=(const Matrix1x2& m);
};
typedef Matrix1x2* PMatrix1x2;

struct Matrix2x2
{
	double v[2][2];

	// Constructor
	Matrix2x2() = default;
	~Matrix2x2() = default;
	Matrix2x2(const Matrix2x2& m) { *this = m; }
	Matrix2x2(double m00, double m01, double m10, double m11);

	// basic methods
	void zero();
	void init(double m00, double m01, double m10, double m11);
	void unit();
	void transpose();
	void swap(Matrix1x2* m, int c);
	double det(); 
	Matrix2x2 inverse();

	// override operator
	Matrix2x2& operator=(const Matrix2x2& m);
	Matrix2x2 operator+(const Matrix2x2& m);
	Matrix2x2& operator+=(const Matrix2x2& m);
	Matrix2x2 operator-(const Matrix2x2& m);
	Matrix2x2& operator-=(const Matrix2x2& m);
	Matrix2x2 operator*(const Matrix2x2& m);
	Matrix2x2& operator*=(const Matrix2x2& m);

};
typedef Matrix2x2* PMatrix2x2;


// Matrix1x4 methods implement
inline Matrix1x4::Matrix1x4(double m0, double m1, double m2, double m3)
{
	v[0] = m0; v[1] = m1; v[2] = m2; v[3] = m3;
}

inline void Matrix1x4::zero() 
{ 
	memset(v, 0, sizeof(v)); 
}

inline void Matrix1x4::init(double m0, double m1, double m2, double m3)
{
	v[0] = m0; v[1] = m1; v[2] = m2; v[3] = m3;
}

inline Matrix1x4& Matrix1x4::operator=(const Matrix1x4& m)
{
	v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3];
	return *this;
}

// Matrix4x3 methods implement
inline Matrix4x3::Matrix4x3(double m00, double m01, double m02,
	double m10, double m11, double m12,
	double m20, double m21, double m22,
	double m30, double m31, double m32)
{
	v[0][0] = m00; v[0][1] = m01; v[0][2] = m02;
	v[1][0] = m00; v[1][1] = m01; v[1][2] = m02;
	v[2][0] = m00; v[2][1] = m01; v[2][2] = m02;
	v[3][0] = m00; v[3][1] = m01; v[3][2] = m02;
}

inline void Matrix4x3::zero() 
{ 
	memset(v, 0, sizeof(v)); 
}

inline void Matrix4x3::init(double m00, double m01, double m02,
	double m10, double m11, double m12,
	double m20, double m21, double m22,
	double m30, double m31, double m32)
{
	v[0][0] = m00; v[0][1] = m01; v[0][2] = m02;
	v[1][0] = m00; v[1][1] = m01; v[1][2] = m02;
	v[2][0] = m00; v[2][1] = m01; v[2][2] = m02;
	v[3][0] = m00; v[3][1] = m01; v[3][2] = m02;
}

inline void Matrix4x3::unit()
{ 
	memcpy((void*)v, (void*)&Unit_M4x3, sizeof(v)); 
}

inline Vector3D Matrix4x3::mul(Vector3D* vec)
{
	Vector3D tmp;
	tmp.x = v[0][0] * vec->x + v[1][0] * vec->y + v[2][0] * vec->z;
	tmp.y = v[0][1] * vec->x + v[1][1] * vec->y + v[2][1] * vec->z;
	tmp.z = v[0][2] * vec->x + v[1][2] * vec->y + v[2][2] * vec->z;
	return tmp;
}

inline Vector4D Matrix4x3::mul(Vector4D* vec)
{
	Vector4D tmp;
	tmp.x = v[0][0] * vec->x + v[1][0] * vec->y + v[2][0] * vec->z + v[3][0] * vec->w;
	tmp.y = v[0][1] * vec->x + v[1][1] * vec->y + v[2][1] * vec->z + v[3][1] * vec->w;
	tmp.z = v[0][2] * vec->x + v[1][2] * vec->y + v[2][2] * vec->z + v[3][2] * vec->w;
	tmp.w = vec->w;
	return tmp;
}

inline Matrix4x3& Matrix4x3::operator=(const Matrix4x3& m)
{
	v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; v[0][2] = m.v[0][2];
	v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; v[1][2] = m.v[1][2];
	v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; v[2][2] = m.v[2][2];
	v[3][0] = m.v[3][0]; v[3][1] = m.v[3][1]; v[3][2] = m.v[3][2];
	return *this;
}

inline void Matrix4x3::swap(Matrix1x4* m, int c)
{
	v[0][c] = m->v[0];
	v[1][c] = m->v[1];
	v[2][c] = m->v[2];
	v[3][c] = m->v[3];
}

// Matrix4x4 methods implement
inline Matrix4x4::Matrix4x4(double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
{
	v[0][0] = m00; v[0][1] = m01; v[0][2] = m02; v[0][3] = m03;
	v[1][0] = m10; v[1][1] = m11; v[1][2] = m12; v[1][3] = m13;
	v[2][0] = m20; v[2][1] = m21; v[2][2] = m22; v[2][3] = m23;
	v[3][0] = m30; v[3][1] = m31; v[3][2] = m32; v[3][3] = m33;
}

inline void Matrix4x4::init(double m00, double m01, double m02, double m03,
	double m10, double m11, double m12, double m13,
	double m20, double m21, double m22, double m23,
	double m30, double m31, double m32, double m33)
{
	v[0][0] = m00; v[0][1] = m01; v[0][2] = m02; v[0][3] = m03;
	v[1][0] = m10; v[1][1] = m11; v[1][2] = m12; v[1][3] = m13;
	v[2][0] = m20; v[2][1] = m21; v[2][2] = m22; v[2][3] = m23;
	v[3][0] = m30; v[3][1] = m31; v[3][2] = m32; v[3][3] = m33;
}

inline void Matrix4x4::zero()
{ 
	memset(v, 0, sizeof(v)); 
}

inline void Matrix4x4::unit() 
{
	memcpy((void*)v, (void*)&Unit_M4x4, sizeof(v)); 
}

inline void Matrix4x4::transpose()
{
	std::swap(v[0][1], v[1][0]); std::swap(v[0][2], v[2][0]); std::swap(v[0][3], v[3][0]);
	std::swap(v[1][2], v[2][1]); std::swap(v[1][3], v[3][1]);
	std::swap(v[2][3], v[3][2]);
}

inline void Matrix4x4::swap(Matrix1x4* m, int c)
{
	v[0][c] = m->v[0];
	v[1][c] = m->v[1];
	v[2][c] = m->v[2];
	v[3][c] = m->v[3];
}

inline double Matrix4x4::simple_det()
{
	return (v[0][0] * (v[1][1] * v[2][2] - v[1][2] * v[2][1])
		- v[0][1] * (v[1][0] * v[2][2] - v[1][2] * v[2][0])
		+ v[0][2] * (v[1][0] * v[2][1] - v[1][1] * v[2][0]));
}
inline Matrix4x4 Matrix4x4::inverse()
{
	Matrix4x4 tmp;
	tmp.zero();
	auto det = this->simple_det();
	if (abs(det) < EPSILON_E5)
		return tmp;
	auto det_inv = 1.0 / det;
	tmp.v[0][0] = det_inv * (v[1][1] * v[2][2] - v[1][2] * v[2][1]);
	tmp.v[0][1] = -det_inv * (v[0][1] * v[2][2] - v[2][1] * v[0][2]);
	tmp.v[0][2] = det_inv * (v[0][1] * v[1][2] - v[1][1] * v[0][2]);
	tmp.v[0][3] = 0.0f;

	tmp.v[1][0] = -det_inv * (v[1][0] * v[2][2] - v[1][2] * v[2][0]);
	tmp.v[1][1] = det_inv * (v[0][0] * v[2][2] - v[0][2] * v[2][0]);
	tmp.v[1][2] = -det_inv * (v[0][0] * v[1][1] - v[0][2] * v[1][0]);
	tmp.v[0][3] = 0.0f;

	tmp.v[2][0] = det_inv * (v[1][0] * v[2][1] - v[1][1] * v[2][0]);
	tmp.v[2][1] = -det_inv * (v[0][0] * v[2][1] - v[0][1] * v[2][0]);
	tmp.v[2][2] = det_inv * (v[0][0] * v[1][1] - v[0][1] * v[1][0]);
	tmp.v[2][3] = 0.0f;

	tmp.v[3][0] = -(v[3][0] * v[0][0] + v[3][1] * v[1][0] + v[3][2] * v[2][0]);
	tmp.v[3][1] = -(v[3][0] * v[0][1] + v[3][1] * v[1][1] + v[3][2] * v[2][1]);
	tmp.v[3][2] = -(v[3][0] * v[0][2] + v[3][1] * v[1][2] + v[3][2] * v[2][2]);
	tmp.v[3][3] = 1.0f;

	return tmp;
}

inline Matrix1x4 Matrix4x4::mul(Matrix1x4* m)
{
	Matrix1x4 tmp;
	tmp.v[0] = v[0][0] * m->v[0] + v[1][0] * m->v[1] + v[2][0] * m->v[2] + v[3][0] * m->v[3];
	tmp.v[1] = v[0][1] * m->v[0] + v[1][1] * m->v[1] + v[2][1] * m->v[2] + v[3][1] * m->v[3];
	tmp.v[2] = v[0][2] * m->v[0] + v[1][2] * m->v[1] + v[2][2] * m->v[2] + v[3][2] * m->v[3];
	tmp.v[3] = v[0][3] * m->v[0] + v[1][3] * m->v[1] + v[2][3] * m->v[2] + v[3][3] * m->v[3];
	return tmp;
}

inline Vector3D Matrix4x4::mul(Vector3D* vec)
{
	Vector3D tmp;
	tmp.x = v[0][0] * vec->x + v[1][0] * vec->y + v[2][0] * vec->z;
	tmp.y = v[0][1] * vec->x + v[1][1] * vec->y + v[2][1] * vec->z;
	tmp.z = v[0][2] * vec->x + v[1][2] * vec->y + v[2][2] * vec->z;
	return tmp;
}

inline Vector4D Matrix4x4::mul(Vector4D* vec)
{
	Vector4D tmp;
	tmp.x = v[0][0] * vec->x + v[1][0] * vec->y + v[2][0] * vec->z + v[3][0] * vec->w;
	tmp.y = v[0][1] * vec->x + v[1][1] * vec->y + v[2][1] * vec->z + v[3][1] * vec->w;
	tmp.z = v[0][2] * vec->x + v[1][2] * vec->y + v[2][2] * vec->z + v[3][2] * vec->w;
	tmp.w = v[0][3] * vec->x + v[1][3] * vec->y + v[2][3] * vec->z + v[3][3] * vec->w;
	return tmp;
}

inline Vertex4D Matrix4x4::mul(Vertex4D* vert)
{
	Vertex4D tmp(*vert);
	tmp.x = v[0][0] * vert->x + v[1][0] * vert->y + v[2][0] * vert->z + v[3][0] * vert->w;
	tmp.y = v[0][1] * vert->x + v[1][1] * vert->y + v[2][1] * vert->z + v[3][1] * vert->w;
	tmp.z = v[0][2] * vert->x + v[1][2] * vert->y + v[2][2] * vert->z + v[3][2] * vert->w;
	tmp.w = v[0][3] * vert->x + v[1][3] * vert->y + v[2][3] * vert->z + v[3][3] * vert->w;
	//tmp.color = vert->color;
	//tmp.normal = vert->normal;
	return tmp;
}

inline Matrix4x4& Matrix4x4::operator=(const Matrix4x4& m)
{
	v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; v[0][2] = m.v[0][2]; v[0][3] = m.v[0][3];
	v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; v[1][2] = m.v[1][2]; v[1][3] = m.v[1][3];
	v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; v[2][2] = m.v[2][2]; v[2][3] = m.v[2][3];
	v[3][0] = m.v[3][0]; v[3][1] = m.v[3][1]; v[3][2] = m.v[3][2]; v[3][3] = m.v[3][3];
	return *this;
}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m)
{
	Matrix4x4 tmp(*this);
	tmp += m;
	return tmp;
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& m)
{
	v[0][0] += m.v[0][0]; v[0][1] += m.v[0][1]; v[0][2] += m.v[0][2]; v[0][3] += m.v[0][3];
	v[1][0] += m.v[1][0]; v[1][1] += m.v[1][1]; v[1][2] += m.v[1][2]; v[1][3] += m.v[1][3];
	v[2][0] += m.v[2][0]; v[2][1] += m.v[2][1]; v[2][2] += m.v[2][2]; v[2][3] += m.v[2][3];
	v[3][0] += m.v[3][0]; v[3][1] += m.v[3][1]; v[3][2] += m.v[3][2]; v[3][3] += m.v[3][3];
	return *this;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m)
{
	Matrix4x4 tmp;
	for (int row = 0; row < 4; row++)
	{
		tmp.v[row][0] = v[row][0] * m.v[0][0] + v[row][1] * m.v[1][0] + v[row][2] * m.v[2][0] + v[row][3] * m.v[3][0];
		tmp.v[row][1] = v[row][0] * m.v[0][1] + v[row][1] * m.v[1][1] + v[row][2] * m.v[2][1] + v[row][3] * m.v[3][1];
		tmp.v[row][2] = v[row][0] * m.v[0][2] + v[row][1] * m.v[1][2] + v[row][2] * m.v[2][2] + v[row][3] * m.v[3][2];
		tmp.v[row][3] = v[row][0] * m.v[0][3] + v[row][1] * m.v[1][3] + v[row][2] * m.v[2][3] + v[row][3] * m.v[3][3];
	}
	return tmp;
}

inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& m)
{
	Matrix4x4 tmp;
	for (int row = 0; row < 4; row++)
	{
		tmp.v[row][0] = v[row][0] * m.v[0][0] + v[row][1] * m.v[1][0] + v[row][2] * m.v[2][0] + v[row][3] * m.v[3][0];
		tmp.v[row][1] = v[row][0] * m.v[0][1] + v[row][1] * m.v[1][1] + v[row][2] * m.v[2][1] + v[row][3] * m.v[3][1];
		tmp.v[row][2] = v[row][0] * m.v[0][2] + v[row][1] * m.v[1][2] + v[row][2] * m.v[2][2] + v[row][3] * m.v[3][2];
		tmp.v[row][3] = v[row][0] * m.v[0][3] + v[row][1] * m.v[1][3] + v[row][2] * m.v[2][3] + v[row][3] * m.v[3][3];
	}
	*this = tmp;
	return *this;
}

inline void Matrix4x4::build(double theta_x, double theta_y, double theta_z)
{
	Matrix4x4 mx, my, mz, mtmp;
	double sin_theta = 0, cos_theta = 0;
	int rot_seq = 0;

	this->unit();
	if (fabs(theta_x) > EPSILON_E5)
		rot_seq = rot_seq | 1;

	if (fabs(theta_y) > EPSILON_E5)
		rot_seq = rot_seq | 2;

	if (fabs(theta_z) > EPSILON_E5)
		rot_seq = rot_seq | 4;

	switch (rot_seq)
	{
	case 0:
		return;
		break;
	case 1:		// x rotation
		cos_theta = Fast_cos(theta_x);
		sin_theta = Fast_sin(theta_x);
		mx.init(1, 0, 0, 0,
			0, cos_theta, sin_theta, 0,
			0, -sin_theta, cos_theta, 0,
			0, 0, 0, 1);

		*this = mx;
		return;
		break;
	case 2:		// y rotation
		cos_theta = Fast_cos(theta_y);
		sin_theta = Fast_sin(theta_y);
		my.init(cos_theta, 0, -sin_theta, 0,
			0, 1, 0, 0,
			sin_theta, 0, cos_theta, 0,
			0, 0, 0, 1);

		*this = my;
		return;
		break;
	case 3:		// xy rotation
		cos_theta = Fast_cos(theta_x);
		sin_theta = Fast_sin(theta_x);
		mx.init(1, 0, 0, 0,
			0, cos_theta, sin_theta, 0,
			0, -sin_theta, cos_theta, 0,
			0, 0, 0, 1);

		cos_theta = Fast_cos(theta_y);
		sin_theta = Fast_sin(theta_y);
		my.init(cos_theta, 0, -sin_theta, 0,
			0, 1, 0, 0,
			sin_theta, 0, cos_theta, 0,
			0, 0, 0, 1);

		*this = mx * my;
		return;
		break;
	case 4: // z rotation
		cos_theta = Fast_cos(theta_z);
		sin_theta = Fast_sin(theta_z);
		mz.init(cos_theta, sin_theta, 0, 0,
			-sin_theta, cos_theta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		*this = mz;
	case 5: // xz rotation
		cos_theta = Fast_cos(theta_x);
		sin_theta = Fast_sin(theta_x);
		mx.init(1, 0, 0, 0,
			0, cos_theta, sin_theta, 0,
			0, -sin_theta, cos_theta, 0,
			0, 0, 0, 1);

		cos_theta = Fast_cos(theta_z);
		sin_theta = Fast_sin(theta_z);
		mz.init(cos_theta, sin_theta, 0, 0,
			-sin_theta, cos_theta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		*this = mx * mz;
	case  6: // yz rotation
		cos_theta = Fast_cos(theta_y);
		sin_theta = Fast_sin(theta_y);
		my.init(cos_theta, 0, -sin_theta, 0,
			0, 1, 0, 0,
			sin_theta, 0, cos_theta, 0,
			0, 0, 0, 1);

		cos_theta = Fast_cos(theta_z);
		sin_theta = Fast_sin(theta_z);
		mz.init(cos_theta, sin_theta, 0, 0,
			-sin_theta, cos_theta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		*this = my * mz;
	case 7:
		cos_theta = Fast_cos(theta_x);
		sin_theta = Fast_sin(theta_x);
		mx.init(1, 0, 0, 0,
			0, cos_theta, sin_theta, 0,
			0, -sin_theta, cos_theta, 0,
			0, 0, 0, 1);

		cos_theta = Fast_cos(theta_y);
		sin_theta = Fast_sin(theta_y);
		my.init(cos_theta, 0, -sin_theta, 0,
			0, 1, 0, 0,
			sin_theta, 0, cos_theta, 0,
			0, 0, 0, 1);

		cos_theta = Fast_cos(theta_z);
		sin_theta = Fast_sin(theta_z);
		mz.init(cos_theta, sin_theta, 0, 0,
			-sin_theta, cos_theta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		mtmp = mx * my;
		*this = mtmp * mz;
	default:
		break;
	}
}

// Matrix1x3 methods implement
inline Matrix1x3::Matrix1x3(double m0, double m1, double m2)
{
	v[0] = m0; v[1] = m1; v[2] = m2;
}

inline void Matrix1x3::zero() 
{ 
	memset(v, 0, sizeof(v)); 
}

inline void Matrix1x3::init(double m0, double m1, double m2)
{
	v[0] = m0; v[1] = m1; v[2] = m2;
}

inline Matrix1x3& Matrix1x3::operator=(const Matrix1x3& m)
{
	v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2];
	return *this;
}

// Matrix3x2 methods implement
inline Matrix3x2::Matrix3x2(double m00, double m01, double m10, double m11, double m20, double m21)
{
	v[0][0] = m00; v[0][1] = m01;
	v[1][0] = m10; v[1][1] = m11;
	v[2][0] = m20; v[2][1] = m21;
}

inline void Matrix3x2::zero() 
{ 
	memset(v, 0, sizeof(v)); 
}

inline void Matrix3x2::init(double m00, double m01, double m10, double m11, double m20, double m21)
{
	v[0][0] = m00; v[0][1] = m01;
	v[1][0] = m10; v[1][1] = m11;
	v[2][0] = m20; v[2][1] = m21;
}

inline Matrix3x2& Matrix3x2::operator=(const Matrix3x2& m)
{
	v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1];
	v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1];
	v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1];
	return *this;
}

// Matrix3x3 methods implement
inline Matrix3x3::Matrix3x3(double m00, double m01, double m02,
	double m10, double m11, double m12,
	double m20, double m21, double m22)
{
	v[0][0] = m00; v[0][1] = m01; v[0][2] = m02;
	v[1][0] = m10; v[1][1] = m11; v[1][2] = m12;
	v[2][0] = m20; v[2][1] = m21; v[2][2] = m22;
}

inline void Matrix3x3::zero() 
{
	memset(v, 0, sizeof(v)); 
}

inline void Matrix3x3::init(double m00, double m01, double m02,
	double m10, double m11, double m12,
	double m20, double m21, double m22)
{
	v[0][0] = m00; v[0][1] = m01; v[0][2] = m02;
	v[1][0] = m10; v[1][1] = m11; v[1][2] = m12;
	v[2][0] = m20; v[2][1] = m21; v[2][2] = m22;
}

inline void Matrix3x3::unit()	
{ 
	memcpy((void*)v, (void*)&Unit_M3x3, sizeof(v)); 
}

inline void Matrix3x3::transpose()
{
	std::swap(v[0][1], v[1][0]);
	std::swap(v[0][2], v[2][0]);
	std::swap(v[1][2], v[2][1]);
}

inline void Matrix3x3::swap(Matrix1x3* m, int c)
{
	v[0][c] = m->v[0]; v[1][c] = m->v[1]; v[2][c] = m->v[2];
}

inline double Matrix3x3::det()
{
	return (v[0][0] * (v[1][1] * v[2][2] - v[1][2] * v[2][1]) -
		v[0][1] * (v[1][0] * v[2][2] - v[1][2] * v[2][0]) +
		v[0][2] * (v[1][0] * v[2][1] - v[1][1] * v[2][0]));
}

inline Matrix3x3 Matrix3x3::inverse()
{
	Matrix3x3 m;
	m.zero();

	auto det = this->det();
	if (abs(det) < EPSILON_E5)
		return m;
	auto det_inv = 1.0 / det;
	m.v[0][0] = det_inv * (v[1][1] * v[2][2] - v[1][2] * v[2][1]);
	m.v[1][0] = -det_inv * (v[1][0] * v[2][2] - v[1][2] * v[2][0]);
	m.v[2][0] = det_inv * (v[1][0] * v[2][1] - v[1][1] * v[2][0]);

	m.v[0][1] = -det_inv * (v[0][1] * v[2][2] - v[0][2] * v[2][1]);
	m.v[1][1] = det_inv * (v[0][0] * v[2][2] - v[0][2] * v[2][0]);
	m.v[2][1] = -det_inv * (v[0][1] * v[2][1] - v[0][1] * v[2][0]);

	m.v[0][2] = det_inv * (v[0][1] * v[1][2] - v[1][1] * v[0][2]);
	m.v[1][2] = -det_inv * (v[0][0] * v[1][2] - v[0][2] * v[1][0]);
	m.v[2][2] = det_inv * (v[0][0] * v[1][1] - v[1][0] * v[0][1]);

	return m;
}

inline Matrix3x3& Matrix3x3::operator=(const Matrix3x3& m)
{
	v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; v[0][2] = m.v[0][2];
	v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; v[1][2] = m.v[1][2];
	v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; v[2][2] = m.v[2][2];
	return *this;
}

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& m)
{
	Matrix3x3 tmp(*this);
	tmp += m;
	return tmp;
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m)
{
	v[0][0] += m.v[0][0]; v[0][1] += m.v[0][1]; v[0][2] += m.v[0][2];
	v[1][0] += m.v[1][0]; v[1][1] += m.v[1][1]; v[1][2] += m.v[1][2];
	v[2][0] += m.v[2][0]; v[2][1] += m.v[2][1]; v[2][2] += m.v[2][2];
	return *this;
}

inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& m)
{
	Matrix3x3 tmp(*this);
	for (int row = 0; row < 4; row++)
	{
		tmp.v[row][0] = v[row][0] * m.v[0][0] + v[row][1] * m.v[1][0] + v[row][2] * m.v[2][0];
		tmp.v[row][1] = v[row][0] * m.v[0][1] + v[row][1] * m.v[1][1] + v[row][2] * m.v[2][1];
		tmp.v[row][2] = v[row][0] * m.v[0][2] + v[row][1] * m.v[1][2] + v[row][2] * m.v[2][2];
	}
	return tmp;
}

inline Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& m)
{
	Matrix3x3 tmp;
	for (int row = 0; row < 3; row++)
	{
		tmp.v[row][0] = v[row][0] * m.v[0][0] + v[row][1] * m.v[1][0] + v[row][2] * m.v[2][0];
		tmp.v[row][1] = v[row][0] * m.v[0][1] + v[row][1] * m.v[1][1] + v[row][2] * m.v[2][1];
		tmp.v[row][2] = v[row][0] * m.v[0][2] + v[row][1] * m.v[1][2] + v[row][2] * m.v[2][2];
	}
	*this = tmp;
	return *this;
}

// Matrix1x2 methods implement
inline Matrix1x2::Matrix1x2(double m0, double m1)
{
	v[0] = m0; v[1] = m1;
}

inline void Matrix1x2::zero() 
{ 
	memset(v, 0, sizeof(v)); 
}

inline void Matrix1x2::init(double m0, double m1)
{
	v[0] = m0; v[1] = m1;
}

inline void Matrix1x2::mul_3x2(const Matrix3x2* m)
{
	auto v1 = v[0] * m->v[0][0] + v[1] * m->v[1][0] + m->v[2][0];
	auto v2 = v[0] * m->v[0][1] + v[1] * m->v[1][1] + m->v[2][1];
	v[0] = v1; v[1] = v2;
}

inline Matrix1x2& Matrix1x2::operator=(const Matrix1x2& m)
{
	v[0] = m.v[0]; v[1] = m.v[1];
	return *this;
}

// Matrix2x2 methods implement
inline Matrix2x2::Matrix2x2(double m00, double m01, double m10, double m11)
{
	v[0][0] = m00; v[0][1] = m01; v[1][0] = m10; v[1][1] = m11;
}

inline void Matrix2x2::zero() 
{
	memset(v, 0, sizeof(v)); 
}

inline void Matrix2x2::init(double m00, double m01, double m10, double m11)
{
	v[0][0] = m00; v[0][1] = m01; v[1][0] = m10; v[1][1] = m11;
}

inline void Matrix2x2::unit() 
{ 
	memcpy((void*)v, (void*)&Unit_M2x2, sizeof(v)); 
}

inline void Matrix2x2::transpose()
{
	std::swap(v[0][1], v[1][0]);
}

inline void Matrix2x2::swap(Matrix1x2* m, int c)
{
	v[0][c] = m->v[0]; v[1][c] = m->v[1];
}

inline double Matrix2x2::det() 
{
	return v[0][0] * v[1][1] - v[1][0] * v[0][1]; 
}

inline Matrix2x2 Matrix2x2::inverse()
{
	Matrix2x2 m;
	m.zero();
	auto det = this->det();
	if (abs(det) < EPSILON_E5)
		return m;

	auto det_inv = 1.0 / det;
	m.v[0][0] = v[0][0] * det_inv;
	m.v[0][1] = v[0][1] * det_inv;
	m.v[1][0] = v[1][0] * det_inv;
	m.v[1][1] = v[1][1] * det_inv;

	return m;
}

inline Matrix2x2& Matrix2x2::operator=(const Matrix2x2& m)
{
	v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1];
	v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1];
	return *this;
}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& m)
{
	Matrix2x2 tmp(*this);
	tmp += m;
	return tmp;
}

inline Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& m)
{
	v[0][0] += m.v[0][0]; v[0][1] += m.v[0][1];
	v[1][0] += m.v[1][0]; v[1][1] += m.v[1][1];
	return *this;
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& m)
{
	Matrix2x2 tmp(*this);
	tmp -= m;
	return tmp;
}

inline Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& m)
{
	v[0][0] -= m.v[0][0]; v[0][1] -= m.v[0][1];
	v[1][0] -= m.v[1][0]; v[1][1] -= m.v[1][1];
	return *this;
}

inline Matrix2x2 Matrix2x2::operator*(const Matrix2x2& m)
{
	Matrix2x2 tmp(*this);
	tmp *= m;
	return tmp;
}

inline Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& m)
{
	Matrix2x2 tmp;
	tmp.v[0][0] = v[0][0] * m.v[0][0] + v[0][1] * m.v[1][0];
	tmp.v[0][1] = v[0][0] * m.v[0][1] + v[0][1] * m.v[1][1];
	tmp.v[1][0] = v[1][0] * m.v[0][0] + v[1][1] * m.v[1][0];
	tmp.v[1][1] = v[1][0] * m.v[0][1] + v[1][1] * m.v[1][1];
	*this = tmp;
	return *this;
}

#endif