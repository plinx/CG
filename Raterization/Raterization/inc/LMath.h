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

/*struct Point2 { double x, y; };
struct Point3 { double x, y, z; };
struct Point4 { double x, y, z, w; };
*/
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




#endif