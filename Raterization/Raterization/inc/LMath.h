#ifndef LMath_h
#define LMath_h

#include <math.h>
#include "Vec.h"

#define PI ((double)3.1415926535f)
#define PI2 ((double)6.283185307f)
#define PI_DIV_2 ((double)1.570796327f)
#define PI_DIV_4 ((double)0.785398163f)
#define PI_INV ((double)0.318309886f)

#define DEG_TO_RAD(ang) ((ang) * PI / 180.0)
#define RAD_TO_DEG(rads) ((rads) * 180.0 / PI)

enum 
{
	LINE_NO_INTERSECT,
	LINE_INTERSECT_IN_SEGMENT,
	LINE_INTERSECT_OUT_SEGMENT,
	LINE_INTERSECT_EVERYWHERE
};

extern double sin_table[361];
extern double cos_table[361];

void Build_SinCos_Tables();
double Fast_sin(double theta);
double Fast_cos(double theta);

struct Vertex2D
{
	double x, y;
};

struct Line2D
{
	Point2D p0, p1;
	Vector2D vec;

	Line2D() = default;
	~Line2D() = default;
	Line2D(Point2D pb, Point2D pe, Vector2D v) : p0(pb), p1(pe), vec(v) {}
	void compute(double t, Point2D* point) 
	{
		point->x = p0.x + vec.x * t;
		point->y = p0.y + vec.y * t;
	}
	int intersect(Line2D* line, double *t1, double *t2)
	{
		auto det_line = (vec.x * line->vec.y - vec.y * line->vec.x);
		if (abs(det_line) <= EPSILON_E5)
			return LINE_NO_INTERSECT;

		*t1 = (vec.x * (p0.y - line->p0.y) - vec.y * (p0.x - line->p0.x)) / det_line;
		*t2 = (vec.x * (p1.y - line->p1.y) - vec.y * (p1.x - line->p1.x)) / det_line;

		if ((0 <= *t1) && (*t1 <= 1) && (0 <= *t2) && (*t2 <= 0))
			return LINE_INTERSECT_IN_SEGMENT;
		else
			return LINE_INTERSECT_OUT_SEGMENT;
	}
	int intersect(Line2D* line, Point2D* point)
	{
		auto det_line = (vec.x * line->vec.y - vec.y * line->vec.x);
		if (abs(det_line) <= EPSILON_E5)
			return LINE_NO_INTERSECT;

		auto t1 = (vec.x * (p0.y - line->p0.y) - vec.y * (p0.x - line->p0.x)) / det_line;
		auto t2 = (vec.x * (p1.y - line->p1.y) - vec.y * (p1.x - line->p1.x)) / det_line;
		point->x = p0.x + vec.x * t1;
		point->y = p0.y + vec.y * t1;

		if ((0 <= t1) && (t1 <= 1) && (0 <= t2) && (t2 <= 0))
			return LINE_INTERSECT_IN_SEGMENT;
		else
			return LINE_INTERSECT_OUT_SEGMENT;
	}
};
typedef Line2D* PLine2D;

struct Line3D
{
	Point3D p0, p1;
	Vector3D vec;

	Line3D() = default;
	~Line3D() = default;
	Line3D(Point3D pb, Point3D pe, Vector3D v) : p0(pb), p1(pe), vec(v) {}
	void init(Point3D pb, Point3D pe, Vector3D v)
	{
		p0 = pb; p1 = pe; vec = v;
	}
	void compute(double t, Point3D* point)
	{
		point->x = p0.x + vec.x * t;
		point->y = p0.y + vec.y * t;
		point->z = p0.z + vec.z * t;
	}
};
typedef Line3D* PLine3D;

struct Plane3D
{
	Point3D p;
	Vector3D normal;

	Plane3D() = default;
	~Plane3D() = default;
	Plane3D(Point3D point, Vector3D n, int normalize) : p(point), normal(n)
	{
		if (normalize) normal.normalize();
	}
	void init(Point3D point, Vector3D n, int normalize)
	{
		p = point; normal = n; 
		if (normalize) normal.normalize();
	}
	double compute(Point3D* point)
	{
		return (normal.x * (point->x - p.x) + 
			normal.y * (point->y - p.y) + 
			normal.z * (point->z - p.z));
	}
	int intersect(Line3D* line, double* t, Point3D* point)
	{
		auto dot = normal.dot(&line->vec);
		if (abs(dot) <= EPSILON_E5)
		{
			if (abs(this->compute(&line->p0)) <= EPSILON_E5)
				return LINE_INTERSECT_EVERYWHERE;
			else
				return LINE_NO_INTERSECT;
		}

		*t = -(normal.x * line->p0.x + normal.y * line->p0.y + normal.z * line->p0.z
			- normal.x * p.x - normal.y * p.y - normal.z * p.z) / dot;
		point->x = line->p0.x + line->vec.x * (*t);
		point->y = line->p0.y + line->vec.y * (*t);
		point->z = line->p0.z + line->vec.z * (*t);

		if (0.0 <= *t && *t <= 1.0)
			return LINE_INTERSECT_IN_SEGMENT;
		else
			return LINE_INTERSECT_OUT_SEGMENT;
	}
};

struct Polar2D
{
	double r, theta;

	Polar2D() = default;
	~Polar2D() = default;

	Polar2D(double dr, double dt) : r(dr), theta(dt) {}
	Polar2D(const Polar2D& p) { *this = p; }
	Polar2D& operator=(const Polar2D& p)
	{
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

// 2 Transform
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

// 3 Transform
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

inline void Point3D_To_Spherical3(PPoint3D point, PSpherical3D sphere)
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