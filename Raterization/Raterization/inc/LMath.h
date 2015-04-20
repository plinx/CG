#ifndef LMath_h
#define LMath_h

#include <math.h>
#include "Vector.h"

const double PI = ((double)3.1415926535f);
const double PI2 = ((double)6.283185307f);
const double PI_DIV_2 = ((double)1.570796327f);
const double PI_DIV_4 = ((double)0.785398163f);
const double PI_INV = ((double)0.318309886f);

inline double Angle_to_Radian(double angle)
{
	return (angle * PI / 180.0);
}

inline double Radian_to_Angle(double radian)
{
	return (radian * 180.0 / PI);
}

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

struct Line2D
{
	Point2D p0, p1;
	Vector2D vec;

	// Constructor
	Line2D() = default;
	~Line2D() = default;
	Line2D(const Line2D& l) { *this = l; }
	Line2D(Point2D pb, Point2D pe, Vector2D v) : p0(pb), p1(pe), vec(v) {}

	// basic methods
	void init(Point2D pb, Point2D pe, Vector2D v);
	Point2D compute(double t);
	int intersect(Line2D* line, double *t1, double *t2);
	int intersect(Line2D* line, Point2D* point);
};
typedef Line2D* PLine2D;

struct Line3D
{
	Point3D p0, p1;
	Vector3D vec;

	// Constructor
	Line3D() = default;
	~Line3D() = default;
	Line3D(const Line3D& l) { *this = l; }
	Line3D(Point3D pb, Point3D pe, Vector3D v) : p0(pb), p1(pe), vec(v) {}

	// basic methods
	void init(Point3D pb, Point3D pe, Vector3D v);
	Point3D compute(double t);
};
typedef Line3D* PLine3D;

struct Plane3D
{
	Point3D pos;
	Vector3D normal;

	// Contructor
	Plane3D() = default;
	~Plane3D() = default;
	Plane3D(const Plane3D& p) { *this = p; }
	Plane3D(Point3D point, Vector3D n, int normalize) : pos(point), normal(n)
	{
		if (normalize) normal.normalize();
	}

	// basic methods
	void zero();
	void init(Point3D point, Vector3D n, int normalize);
	double compute(Point3D* point);
	int intersect(Line3D* line, double* t, Point3D* point);

	// override operator
	Plane3D& operator=(const Plane3D& p);
};

struct Polar2D
{
	double r, theta;
	
	// Constructor
	Polar2D() = default;
	~Polar2D() = default;
	Polar2D(const Polar2D& p) { *this = p; }
	Polar2D(double dr, double dt) : r(dr), theta(dt) {}
	
	// basic methods
	void init(double dr, double dt);
	void init(Point2D* point);
	Point2D toPoint2D();
	void toXY(double *dx, double *dy);

	// override operator
	Polar2D& operator=(const Polar2D& p);
};
typedef Polar2D* PPolar2D;

struct Cylindrical3D
{
	double r, theta, z;

	// Constructor
	Cylindrical3D() = default;
	~Cylindrical3D() = default;
	Cylindrical3D(const Cylindrical3D& c) { *this = c; }
	Cylindrical3D(double dr, double dt, double dz) : r(dr), theta(dt), z(dz) {}

	// basic methods
	void init(double dr, double dt, double dz);
	void init(Point3D* point);
	Point3D toPoint3D();
	void toXYZ(double *dx, double *dy, double *dz);

	// override operator
	Cylindrical3D& operator=(const Cylindrical3D& c);
};
typedef Cylindrical3D* PCylindrical3D;

struct Spherical3D
{
	double pos, theta, phi;

	// Contructor
	Spherical3D() = default;
	~Spherical3D() = default;
	Spherical3D(const Spherical3D& s) { *this = s; }
	Spherical3D(double dpos, double dt, double dphi) : pos(dpos), theta(dt), phi(dphi) {}

	// basic methods
	void init(double dpos, double dt, double dphi);
	void init(Point3D* point);
	Point3D toPoint3D();
	void toXYZ(double *dx, double *dy, double *dz);

	// override operator
	Spherical3D& operator=(const Spherical3D& s);
};
typedef Spherical3D* PSpherical3D;

// Line2D methods implement
inline void Line2D::init(Point2D pb, Point2D pe, Vector2D v)
{
	p0 = pb; p1 = pe; vec = v;
}

inline Point2D Line2D::compute(double t)
{
	Point2D tmp;
	tmp.x = p0.x + vec.x * t;
	tmp.y = p0.y + vec.y * t;
	return tmp;
}

inline int Line2D::intersect(Line2D* line, double *t1, double *t2)
{
	auto det_line = (vec.x * line->vec.y - vec.y * line->vec.x);
	if (abs(det_line) <= EPSILON_E5)
		return LINE_NO_INTERSECT;
	auto det_line_inv = 1 / det_line;

	*t1 = (line->vec.x * (p0.y - line->p0.y) - line->vec.y * (p0.x - line->p0.x)) * det_line_inv;
	*t2 = (line->vec.x * (p0.y - line->p0.y) - line->vec.y * (p0.x - line->p0.x)) * det_line_inv;

	if ((0 <= *t1) && (*t1 <= 1) && (0 <= *t2) && (*t2 <= 1))
		return LINE_INTERSECT_IN_SEGMENT;
	else
		return LINE_INTERSECT_OUT_SEGMENT;
}

inline int Line2D::intersect(Line2D* line, Point2D* point)
{
	auto det_line = (vec.x * line->vec.y - vec.y * line->vec.x);
	if (abs(det_line) <= EPSILON_E5)
		return LINE_NO_INTERSECT;
	auto det_line_inv = 1 / det_line;

	auto t1 = (line->vec.x * (p0.y - line->p0.y) - line->vec.y * (p0.x - line->p0.x)) * det_line_inv;
	auto t2 = (line->vec.x * (p0.y - line->p0.y) - line->vec.y * (p0.x - line->p0.x)) * det_line_inv;
	point->x = p0.x + vec.x * t1;
	point->y = p0.y + vec.y * t2;

	if ((0 <= t1) && (t1 <= 1) && (0 <= t2) && (t2 <= 1))
		return LINE_INTERSECT_IN_SEGMENT;
	else
		return LINE_INTERSECT_OUT_SEGMENT;
}

// Line3D methods implement
inline void Line3D::init(Point3D pb, Point3D pe, Vector3D v)
{
	p0 = pb; p1 = pe; vec = v;
}

inline Point3D Line3D::compute(double t)
{
	Point3D tmp;
	tmp.x = p0.x + vec.x * t;
	tmp.y = p0.y + vec.y * t;
	tmp.z = p0.z + vec.z * t;
	return tmp;
}

// Plan3D methods implement
inline void Plane3D::zero() 
{
	pos.zero(); normal.zero(); 
}

inline void Plane3D::init(Point3D point, Vector3D n, int normalize)
{
	pos = point; normal = n;
	if (normalize) normal.normalize();
}

inline double Plane3D::compute(Point3D* point)
{
	return (normal.x * (point->x - pos.x) +
		normal.y * (point->y - pos.y) +
		normal.z * (point->z - pos.z));
}

inline int Plane3D::intersect(Line3D* line, double* t, Point3D* point)
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
		- normal.x * pos.x - normal.y * pos.y - normal.z * pos.z) / dot;
	point->x = line->p0.x + line->vec.x * (*t);
	point->y = line->p0.y + line->vec.y * (*t);
	point->z = line->p0.z + line->vec.z * (*t);

	if (0.0 <= *t && *t <= 1.0)
		return LINE_INTERSECT_IN_SEGMENT;
	else
		return LINE_INTERSECT_OUT_SEGMENT;
}

inline Plane3D& Plane3D::operator=(const Plane3D& p)
{
	pos = p.pos; normal = p.normal;
	return *this;
}

// Polar2D methods implement
inline void Polar2D::init(double dr, double dt)
{
	r = dr; theta = dt;
}

inline void Polar2D::init(Point2D* point)
{
	r = sqrt((point->x * point->x) + (point->y * point->y));
	theta = atan(point->y / point->x);
}

inline Point2D Polar2D::toPoint2D()
{
	Point2D tmp;
	tmp.x = r * cos(theta);
	tmp.y = r * sin(theta);
	return tmp;
}

inline void Polar2D::toXY(double *dx, double *dy)
{
	*dx = r * cos(theta);
	*dy = r * sin(theta);
}

inline Polar2D& Polar2D::operator=(const Polar2D& p)
{
	r = p.r; theta = p.theta;
	return *this;
}

// Cylindrical3D methods implement
inline void Cylindrical3D::init(double dr, double dt, double dz)
{
	r = dr; theta = dt; z = dz;
}

inline void Cylindrical3D::init(Point3D* point)
{
	r = sqrt((point->x * point->x) + (point->y * point->y));
	theta = atan(point->y / point->x);
	z = point->z;
}

inline Point3D Cylindrical3D::toPoint3D()
{
	Point3D tmp;
	tmp.x = r * cos(theta);
	tmp.y = r * sin(theta);
	tmp.z = z;
	return tmp;
}

inline void Cylindrical3D::toXYZ(double *dx, double *dy, double *dz)
{
	*dy = r * cos(theta);
	*dz = r * sin(theta);
	*dz = z;
}

inline Cylindrical3D& Cylindrical3D::operator=(const Cylindrical3D& c)
{
	r = c.r; theta = c.theta; z = c.z;
	return *this;
}

// Spherical3D methods implement
inline void Spherical3D::init(double dpos, double dt, double dphi)
{
	pos = dpos; theta = dt; phi = dphi;
}

inline void Spherical3D::init(Point3D* point)
{
	pos = sqrt((point->x * point->x) + (point->y * point->y) + (point->z * point->z));
	theta = atan(point->y / point->x);
	phi = acos(point->z / pos);
}

inline Point3D Spherical3D::toPoint3D()
{
	Point3D tmp;
	double r;
	r = pos * sin(phi);
	tmp.z = pos * cos(phi);

	tmp.x = r * cos(theta);
	tmp.y = r * sin(theta);

	return tmp;
}

inline void Spherical3D::toXYZ(double *dx, double *dy, double *dz)
{
	double r;
	r = pos * sin(phi);
	*dz = pos * cos(phi);

	*dx = r * cos(theta);
	*dy = r * sin(theta);
}

inline Spherical3D& Spherical3D::operator=(const Spherical3D& s)
{
	pos = s.pos; theta = s.theta; phi = s.phi;
	return *this;
}

// Transform functions
// 2 Transform
inline void Point2D_To_RTheta(PPoint2D point, double *r, double *theta)
{
	*r = sqrt((point->x * point->x) + (point->y * point->y));
	*theta = atan(point->y / point->x);
}

inline void Point3D_To_RThetaZ(PPoint3D point, double *r, double *theta, double *z)
{
	*r = sqrt((point->x * point->x) + (point->y * point->y));
	*theta = atan(point->y / point->x);
	*z = point->z;
}

inline void Point3D_To_PosThetaPhi(PPoint3D point, double *pos, double *theta, double *phi)
{
	*pos = sqrt((point->x * point->x) + (point->y * point->y) + (point->z * point->z));
	*theta = atan(point->y / point->x);
	*phi = acos(point->z / *pos);
}

#endif