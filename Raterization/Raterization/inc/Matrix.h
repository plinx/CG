#ifndef Matrix_h
#define Matrix_h

struct Matrix4x4
{
	double v[4][4];

	void Zero() { memset(v, 0, sizeof(v)); }
	void Init() { memcpy((void*)v, (void*)&Unit_M4x4, sizeof(v)); }
};

struct Matrix4x3
{
	double v[4][3];

	void Zero() { memset(v, 0, sizeof(v)); }
};

struct Matrix1x4
{
	double v[4];

	void Zero() { memset(v, 0, sizeof(v)); }
};

struct Matrix3x3
{
	double v[3][3];

	void Zero() { memset(v, 0, sizeof(v)); }
};

struct Matrix3x2
{
	double v[3][2];

	void Zero() { memset(v, 0, sizeof(v)); }
};

struct Matrix1x3
{
	double v[3];

	void Zero() { memset(v, 0, sizeof(v)); }
};

struct Matrix2x2
{
	double v[2][2];

	void Zero() { memset(v, 0, sizeof(v)); }
};

struct Matrix1x2
{
	double v[2];

	void Zero() { memset(v, 0, sizeof(v)); }
};

// Unit Matrix
const Matrix4x4 Unit_M4x4 = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

const Matrix4x3 Unit_M4x3 = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	0, 0, 0
};

const Matrix3x3 Unit_M3x3 = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
};

const Matrix2x2 Unit_M2x2 = {
	1, 0,
	0, 1
};

#endif