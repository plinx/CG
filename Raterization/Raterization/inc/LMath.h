#ifndef LMath_h
#define LMath_h

#define PI ((double)3.1415926535f)
#define PI2 ((double)6.283185307f)
#define PI_DIV_2 ((double)1.570796327f)
#define PI_DIV_4 ((double)0.785398163f)
#define PI_INV ((double)0.318309886f)

#define EPSILON_E3 (double)(1E-3)
#define EPSILON_E4 (double)(1E-4)
#define EPSILON_E5 (double)(1E-5)
#define EPSILON_E6 (double)(1E-6)

enum 
{
	Line_NoIntersect = 0,
	Line_Intersect_In_Segment,
	Line_Intersect_Out_Segment,
	Line_Intersect_Everywhere
};

typedef Vector2* PVector2;
typedef Vector3* PVector3;
typedef Vector4* PVector4;

struct Point2 { double x, y; };
struct Point3 { double x, y, z; };
struct Point4 { double x, y, z, w; };

struct Vector2
{
	double x, y;

	Vector2(){}
	Vector2(double dx, double dy) : x(dx), y(dy) {}
};

struct Vector3
{
	double x, y, z;

	Vector3(){}
	Vector3(double dx, double dy, double dz) : x(dx), y(dy), z(dz) {}
};

struct Vector4
{
	double x, y, z, w;

	Vector4(){}
	Vector4(double dx, double dy, double dz, double dw) : 
		x(dx), y(dy), z(dz), w(dw) {}
};

struct Vertex2
{
	double x, y;
};

struct Line2
{
	Point2 p0, p1;
	Vector2 v;
};

struct Line3
{
	Point3 p0, p1;
	Vector3 v;
};

struct Plane3
{
	Point3 p;
	Vector3 normal;
};

struct Matrix4x4
{
	double v[4][4];
};

struct Matrix4x3
{
	double v[4][3];
};

struct Matrix1x4
{
	double v[4];
};

struct Matrix3x3
{
	double v[3][3];
};

struct Matrix3x2
{
	double v[3][2];
};

struct Matrix1x3
{
	double v[3];
};

struct Matrix2x2
{
	double v[2][2];
};

struct Matrix1x2
{
	double v[2];
};

struct Quat
{
	double real;
	Vector3 imag;
};

struct Polar2
{
	double r, theta;
};

struct Cylindrical3
{
	double r, theta, z;
};

struct Spherical3
{
	double pos, theta, phi;
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
}


#endif