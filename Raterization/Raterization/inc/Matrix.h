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

	Matrix1x4() = default;
	~Matrix1x4() = default;
	Matrix1x4(const Matrix1x4& m) { *this = m; }

	void Zero() { memset(v, 0, sizeof(v)); }

	Matrix1x4& operator=(const Matrix1x4& m) {
		v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; v[3] = m.v[3];
		return *this;
	}
};
typedef Matrix1x4* PMatrix1x4;

struct Matrix4x3
{
	double v[4][3];

	Matrix4x3() = default;
	~Matrix4x3() = default;
	Matrix4x3(const Matrix4x3& m) { *this = m; }

	void Zero() { memset(v, 0, sizeof(v)); }
	void Init()	{ memcpy((void*)v, (void*)&Unit_M4x3, sizeof(v)); }

	Matrix4x3& operator=(const Matrix4x3& m) {
		v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; v[0][2] = m.v[0][2];
		v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; v[1][2] = m.v[1][2];
		v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; v[2][2] = m.v[2][2];
		v[3][0] = m.v[3][0]; v[3][1] = m.v[3][1]; v[3][2] = m.v[3][2];
		return *this;
	}

	void Swap(Matrix1x4* m, int c) {
		v[0][c] = m->v[0]; v[1][c] = m->v[1];
		v[2][c] = m->v[2]; v[3][c] = m->v[3];
	}
};
typedef Matrix4x3* PMatrix4x3;

struct Matrix4x4
{
	double v[4][4];

	Matrix4x4() = default;
	~Matrix4x4() = default;
	Matrix4x4(const Matrix4x4& m) { *this = m; }

	void Zero() { memset(v, 0, sizeof(v)); }
	void Init() { memcpy((void*)v, (void*)&Unit_M4x4, sizeof(v)); }

	Matrix4x4& operator=(const Matrix4x4& m) {
		v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; v[0][2] = m.v[0][2]; v[0][3] = m.v[0][3];
		v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; v[1][2] = m.v[1][2]; v[1][3] = m.v[1][3];
		v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; v[2][2] = m.v[2][2]; v[2][3] = m.v[2][3];
		v[3][0] = m.v[3][0]; v[3][1] = m.v[3][1]; v[3][2] = m.v[3][2]; v[3][3] = m.v[3][3];
		return *this;
	}

	void Transpose() {
		std::swap(v[0][1], v[1][0]); std::swap(v[0][2], v[2][0]); std::swap(v[0][3], v[3][0]);
		std::swap(v[1][2], v[2][1]); std::swap(v[1][3], v[3][1]);
		std::swap(v[2][3], v[3][2]);
	}

	void Swap(Matrix1x4* m, int c) {
		v[0][c] = m->v[0]; v[1][c] = m->v[1];
		v[2][c] = m->v[2]; v[3][c] = m->v[3];
	}
};
typedef Matrix4x4* PMatrix4x4;

struct Matrix1x3
{
	double v[3];

	Matrix1x3() = default;
	~Matrix1x3() = default;
	Matrix1x3(const Matrix1x3& m) { *this = m; }

	void Zero() { memset(v, 0, sizeof(v)); }

	Matrix1x3& operator=(const Matrix1x3& m) {
		v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2];
		return *this;
	}
};
typedef Matrix1x3* PMatrix1x3;

struct Matrix3x2
{
	double v[3][2];

	Matrix3x2() = default;
	~Matrix3x2() = default;
	Matrix3x2(const Matrix3x2& m) { *this = m; }
	Matrix3x2(double m00, double m01, double m10, double m11, double m20, double m21) {
		v[0][0] = m00; v[0][1] = m01; 
		v[1][0] = m10; v[1][1] = m11;
		v[2][0] = m20; v[2][1] = m21;
	}

	void Zero() { memset(v, 0, sizeof(v)); }

	Matrix3x2& operator=(const Matrix3x2& m) {
		v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; 
		v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; 
		v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; 
		return *this;
	}
};
typedef Matrix3x2* PMatrix3x2;

struct Matrix3x3
{
	double v[3][3];

	Matrix3x3() = default;
	~Matrix3x3() = default;
	Matrix3x3(const Matrix3x3& m) { *this = m; }
	Matrix3x3(double m00, double m01, double m02,
		double m10, double m11, double m12,
		double m20, double m21, double m22) {
		v[0][0] = m00; v[0][1] = m01; v[0][2] = m02;
		v[1][0] = m10; v[1][1] = m11; v[1][2] = m12;
		v[2][0] = m20; v[2][1] = m21; v[2][2] = m22;
	}

	void Zero() { memset(v, 0, sizeof(v)); }
	void Init()	{ memcpy((void*)v, (void*)&Unit_M3x3, sizeof(v)); }

	Matrix3x3& operator=(const Matrix3x3& m) {
		v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1]; v[0][2] = m.v[0][2];
		v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1]; v[1][2] = m.v[1][2];
		v[2][0] = m.v[2][0]; v[2][1] = m.v[2][1]; v[2][2] = m.v[2][2];
		return *this;
	}
	Matrix3x3& operator+(const Matrix3x3& m) { return *this += m; }
	Matrix3x3& operator+=(const Matrix3x3& m) {
		v[0][0] += m.v[0][0]; v[0][1] += m.v[0][1]; v[0][2] += m.v[0][2];
		v[1][0] += m.v[1][0]; v[1][1] += m.v[1][1]; v[1][2] += m.v[1][2];
		v[2][0] += m.v[2][0]; v[2][1] += m.v[2][1]; v[2][2] += m.v[2][2];
	}
	Matrix3x3& operator*(const Matrix3x3& m) { return *this *= m; }
	Matrix3x3& operator*=(const Matrix3x3& m) {
		v[0][0] *= m.v[0][0]; v[0][1] *= m.v[0][1]; v[0][2] *= m.v[0][2];
		v[1][0] *= m.v[1][0]; v[1][1] *= m.v[1][1]; v[1][2] *= m.v[1][2];
		v[2][0] *= m.v[2][0]; v[2][1] *= m.v[2][1]; v[2][2] *= m.v[2][2];
	}

	void Transpose() {
		std::swap(v[0][1], v[1][0]);
		std::swap(v[0][2], v[2][0]);
		std::swap(v[1][2], v[2][1]);
	}

	void Swap(PMatrix1x3 m, int c) {
		v[0][c] = m->v[0]; v[1][c] = m->v[1]; v[2][c] = m->v[2];
	}
};
typedef Matrix3x3* PMatrix3x3;

struct Matrix1x2
{
	double v[2];

	Matrix1x2() = default;
	~Matrix1x2() = default;
	Matrix1x2(const Matrix1x2& m) { *this = m; }

	void Zero() { memset(v, 0, sizeof(v)); }
	void Mul_3x2(const Matrix3x2* m) {
		auto v1 = v[0] * m->v[0][0] + v[1] * m->v[1][0] + m->v[2][0];
		auto v2 = v[0] * m->v[0][1] + v[1] * m->v[1][1] + m->v[2][1];
		v[0] = v1; v[1] = v2;
	}

	Matrix1x2& operator=(const Matrix1x2& m) {
		v[0] = m.v[0]; v[1] = m.v[1];
		return *this;
	}
};
typedef Matrix1x2* PMatrix1x2;

struct Matrix2x2
{
	double v[2][2];

	Matrix2x2() = default;
	~Matrix2x2() = default;
	Matrix2x2(const Matrix2x2& m) { *this = m; }
	Matrix2x2(double m00, double m01, double m10, double m11) {
		v[0][0] = m00; v[0][1] = m01; v[1][0] = m10; v[1][1] = m11;
	}

	void Zero() { memset(v, 0, sizeof(v)); }
	void Init() { memcpy((void*)v, (void*)&Unit_M2x2, sizeof(v)); }
	void Transpose() {
		std::swap(v[0][1], v[1][0]);
	}
	void Swap(Matrix1x2* m, int c) {
		v[0][c] = m->v[0]; v[1][c] = m->v[1];
	}
	double Det() { return v[0][0] * v[1][1] - v[1][0] * v[0][1]; }
	int Inverse(Matrix2x2* m) {
		auto det = this->Det();
		if (abs(det) < EPSILON_E5)
			return 0;

		auto det_inv = 1.0 / det;
		m->v[0][0] = v[0][0] * det_inv;
		m->v[0][1] = v[0][1] * det_inv;
		m->v[1][0] = v[1][0] * det_inv;
		m->v[1][1] = v[1][1] * det_inv;

		return 1;
	}

	Matrix2x2& operator=(const Matrix2x2& m) {
		v[0][0] = m.v[0][0]; v[0][1] = m.v[0][1];
		v[1][0] = m.v[1][0]; v[1][1] = m.v[1][1];
		return *this;
	}
	Matrix2x2& operator+(const Matrix2x2& m) { return *this += m; }
	Matrix2x2& operator+=(const Matrix2x2& m) {
		v[0][0] += m.v[0][0]; v[0][1] += m.v[0][1];
		v[1][0] += m.v[1][0]; v[1][1] += m.v[1][1];
		return *this;
	}
	Matrix2x2& operator-(const Matrix2x2& m) { return *this -= m; }
	Matrix2x2& operator-=(const Matrix2x2& m) {
		v[0][0] -= m.v[0][0]; v[0][1] -= m.v[0][1];
		v[1][0] -= m.v[1][0]; v[1][1] -= m.v[1][1];
		return *this;
	}
	Matrix2x2& operator*(const Matrix2x2& m) { return *this *= m; }
	Matrix2x2& operator*=(const Matrix2x2& m) {
		v[0][0] *= m.v[0][0]; v[0][1] *= m.v[0][1];
		v[1][0] *= m.v[1][0]; v[1][1] *= m.v[1][1];
		return *this;
	}

};
typedef Matrix2x2* PMatrix2x2;

#endif