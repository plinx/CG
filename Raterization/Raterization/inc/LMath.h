#ifndef LMath_h
#define LMath_h

#include <math.h>
#include "Vec.h"

#define PI ((double)3.1415926535f)
#define PI2 ((double)6.283185307f)
#define PI_DIV_2 ((double)1.570796327f)
#define PI_DIV_4 ((double)0.785398163f)
#define PI_INV ((double)0.318309886f)

enum 
{
	Line_NoIntersect = 0,
	Line_Intersect_In_Segment,
	Line_Intersect_Out_Segment,
	Line_Intersect_Everywhere
};

extern double sin_table[361];
extern double cos_table[361];

void Build_SinCos_Tables();
double Fast_sin(double theta);
double Fast_cos(double theta);

struct Vertex2
{
	double x, y;
};

struct Line2
{
	Point2D p0, p1;
	Vector2 v;
};

struct Line3
{
	Point3D p0, p1;
	Vector3 v;
};

struct Plane3
{
	Point3D p;
	Vector3 normal;
};

struct Polar2D
{
	double r, theta;

	Polar2D() = default;
	~Polar2D() = default;

	Polar2D(double dr, double dt) : r(dr), theta(dt) {}
	Polar2D(const Polar2D& p) { *this = p; }
	Polar2D& operator=(const Polar2D& p) {
		r = p.r; theta = p.theta;
	}
};
typedef Polar2D* PPolar2D;

struct Cylindrical3D
{
	double r, theta, z;
};
typedef Cylindrical3D* PCylindrical3D;

struct Spherical3D
{
	double pos, theta, phi;
};
typedef Spherical3D* PSpherical3D;

// Transform functions

// 2D Transform
inline void Polar2D_To_Point2D(PPolar2D polar, PPoint2D point)
{
	point->x = polar->r * cos(polar->theta);
	point->y = polar->r * sin(polar->theta);
}

inline void Polar2D_To_XY(PPolar2D polar, double *x, double *y)
{
	*x = polar->r * cos(polar->theta);
	*y = polar->r * sin(polar->theta);
}

inline void Point2D_To_Polar2D(PPoint2D point, PPolar2D polar)
{
	polar->r = sqrt((point->x * point->x) + (point->y * point->y));
	polar->theta = atan(point->y / point->x);
}

inline void Point2D_To_RTheta(PPoint2D point, double *r, double *theta)
{
	*r = sqrt((point->x * point->x) + (point->y * point->y));
	*theta = atan(point->y / point->x);
}

// 3D Transform
inline void Cylindrical3D_To_Point3D(PCylindrical3D cylindrical, PPoint3D point)
{
	point->x = cylindrical->r * cos(cylindrical->theta);
	point->y = cylindrical->r * sin(cylindrical->theta);
	point->z = cylindrical->z;
}

inline void Cylindrical3D_To_XYZ(PCylindrical3D cylindrical, double *x, double *y, double *z)
{
	*y = cylindrical->r * cos(cylindrical->theta);
	*z = cylindrical->r * sin(cylindrical->theta);
	*z = cylindrical->z;
}

inline void Point3D_To_Cylindrical3D(PPoint3D point, PCylindrical3D cylindrical)
{
	cylindrical->r = sqrt((point->x * point->x) + (point->y * point->y));
	cylindrical->theta = atan(point->y / point->x);
	cylindrical->z = point->z;
}

inline void Point3D_To_RThetaZ(PPoint3D point, double *r, double *theta, double *z)
{
	*r = sqrt((point->x * point->x) + (point->y * point->y));
	*theta = atan(point->y / point->x);
	*z = point->z;
}

inline void Spherical3D_To_Point3D(PSpherical3D sphere, PPoint3D point)
{
	double r;
	r = sphere->pos * sin(sphere->phi);
	point->z = sphere->pos * cos(sphere->phi);

	point->x = r * cos(sphere->theta);
	point->y = r * sin(sphere->theta);
}

inline void Spherical3D_To_XYZ(PSpherical3D sphere, double *x, double *y, double *z)
{
	double r;
	r = sphere->pos * sin(sphere->phi);
	*z = sphere->pos * cos(sphere->phi);

	*x = r * cos(sphere->theta);
	*y = r * sin(sphere->theta);
}

inline void Point3D_To_Spherial3D(PPoint3D point, PSpherical3D sphere)
{
	sphere->pos = sqrt((point->x * point->x) + (point->y * point->y) + (point->z * point->z));
	sphere->theta = atan(point->y / point->x);
	sphere->phi = acos(point->z / sphere->pos);
}

inline void Point3D_To_PosThetaPhi(PPoint3D point, double *pos, double *theta, double *phi)
{
	*pos = sqrt((point->x * point->x) + (point->y * point->y) + (point->z * point->z));
	*theta = atan(point->y / point->x);
	*phi = acos(point->z / *pos);
}

#endif