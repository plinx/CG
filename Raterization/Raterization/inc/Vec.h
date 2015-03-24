#ifndef Vec_h
#define Vec_h

#include <algorithm>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define EPSILON_E3 (double)(1E-3)
#define EPSILON_E4 (double)(1E-4)
#define EPSILON_E5 (double)(1E-5)
#define EPSILON_E6 (double)(1E-6)

// Vector2D, PVector2D, Point2D, PPoint2D
struct Vector2D
{
	double x, y;

	Vector2D() = default;
	~Vector2D() = default;
	// Constructor
	Vector2D(double dx, double dy) : x(dx), y(dy) {}
	Vector2D(const Vector2D& v) { *this = v; }
	// Construct from Point2D
	Vector2D(const Vector2D* begin, const Vector2D* end)
	{
		x = end->x - begin->x; y = end->y - begin->y;
	}

	void zero() { x = y = 0.0; }
	void init(int ix, int iy) { x = ix; y = iy; }
	double length() const { return sqrt(x*x + y*y); }
	void normalize()
	{
		double length = this->length();
		if (length < EPSILON_E5) return;
		double length_inv = 1.0 / length;
		x = x * length_inv; y = y * length_inv;
	}
	double dot(const Vector2D* v) { return x * v->x + y * v->y; }
	double cos(const Vector2D* v) { return this->dot(v) / (this->length() * v->length()); }

	Vector2D& operator=(const Vector2D& v) { x = v.x; y = v.y; return *this; }
	Vector2D operator+(const Vector2D& v)
	{ 
		Vector2D tmp;
		tmp.x = x + v.x; tmp.y = y + v.y;
		return tmp;
	}
	Vector2D& operator+=(const Vector2D& v) { x += v.x; y += v.y; return *this; }
	Vector2D operator-(const Vector2D& v)
	{ 
		Vector2D tmp;
		tmp.x = x - v.x; tmp.y = y - v.y;
		return tmp;
	}
	Vector2D& operator-=(const Vector2D& v) { x -= v.x; y -= v.y; return *this; }
	Vector2D operator*(double k)
	{
		Vector2D tmp;
		tmp.x = x * k; tmp.y = y * k;
		return tmp;
	}
	Vector2D& operator*=(double k) { x *= k; y *= k; return *this; }
	
	bool operator==(const Vector2D& v)
	{
		if (x == v.x && y == v.y)
			return true;
		return false;
	}
	bool operator!=(const Vector2D& v)
	{
		if (*this == v)
			return false;
		return true;
	}
};
typedef Vector2D* PVector2D;
typedef Vector2D Point2D;
typedef Point2D* PPoint2D;

// Vector3D, PVector3D, Point3D, PPoint3D
struct Vector3D
{
	double x, y, z;

	Vector3D() = default;
	~Vector3D() = default;
	// Constructor
	Vector3D(double dx, double dy, double dz) : x(dx), y(dy), z(dz) {}
	Vector3D(const Vector3D& v) { *this = v; }
	// Build from Point3D
	Vector3D(const Vector3D* begin, const Vector3D* end)
	{
		x = end->x - begin->x; y = end->y - begin->y; z = end->z - begin->z;
	}

	void zero() { x = y = z = 0.0; }
	void init(double ix, double iy, double iz) { x = ix; y = iy; z = iz; }
	double length() const { return sqrt(x*x + y*y + z*z); }
	double Fast_length()
	{
		int ix, iy, iz;
		ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
		if (y < x) std::swap(ix, iy);
		if (z < y) std::swap(iy, iz);
		if (y < x) std::swap(ix, iy);
		auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
		return ((double)(dist >> 10));
	}
	void normalize()
	{
		auto length = this->length();
		if (length < EPSILON_E5)
			return;
		auto length_inv = 1.0 / length;
		x *= length_inv; y *= length_inv; z *= length_inv;
	}

	Vector3D& operator=(const Vector3D& v) { x = v.x; y = v.y; z = v.z; return *this; }
	Vector3D operator+(const Vector3D& v)
	{
		Vector3D tmp;
		tmp.x = x + v.x; tmp.y = y + v.y; tmp.z = z + v.z; 
		return tmp; 
	}
	Vector3D& operator+=(const Vector3D& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3D operator-(const Vector3D& v)
	{
		Vector3D tmp;
		tmp.x = x - v.x; tmp.y = y - v.y; tmp.z = z - v.z; 
		return tmp; 
	}
	Vector3D& operator-=(const Vector3D& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3D operator*(double k)
	{
		Vector3D tmp;
		tmp.x = x * k; tmp.y = y * k; tmp.z = z * k; 
		return tmp; 
	}
	Vector3D& operator*=(double k) { x *= k; y *= k; z *= k; return *this; }

	double dot(const Vector3D* v) { return x * v->x + y * v->y + z * v->z; }
	double cos(const Vector3D* v) { return this->dot(v) / (this->length() * v->length()); }
	Vector3D cross(Vector3D* v)
	{
		Vector3D tmp;
		tmp.x = (y * v->z) - (z * v->y); tmp.y = -((x * v->z) - (z * v->x)); tmp.z = (x * v->y) - (y * v->x);
		return tmp;
	}

	bool operator==(const Vector3D& v)
	{
		if (x == v.x && y == v.y && z == v.z)
			return true;
		return false;
	}
	bool operator!=(const Vector3D& v)
	{
		if (*this == v)
			return false;
		return true;
	}
};
typedef Vector3D* PVector3D;
typedef Vector3D Point3D;
typedef Point3D* PPoint3D;

// Vector4D, PVector4D, Point4D, PPoint4D
struct Vector4D
{
	double x, y, z, w;

	Vector4D(){}
	~Vector4D() = default;
	// Constructor
	Vector4D(double dx, double dy, double dz, double dw)
		: x(dx), y(dy), z(dz), w(dw) {}
	Vector4D(const Vector4D& v) { *this = v; }
	// Build from Point4D
	Vector4D(const Vector4D* begin, const Vector4D* end)
	{
		x = end->x - begin->x; y = end->y - begin->y;
		z = end->z - begin->z; w = 1.0;
	}

	void zero() { x = y = z = 0.0; w = 1.0; }
	void init(double dx, double dy, double dz) { x = dx; y = dy; z = dz; w = 1.0; }
	double length() const { return sqrt(x*x + y*y + z*z); }
	double Fast_length()
	{
		int ix, iy, iz;
		ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
		if (y < x) std::swap(ix, iy);
		if (z < y) std::swap(iy, iz);
		if (y < x) std::swap(ix, iy);
		auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
		return ((double)(dist >> 10));
	}
	void normalize()
	{
		auto length = this->length();
		if (length < EPSILON_E5)
			return;
		auto length_inv = 1.0 / length;
		x *= length_inv; y *= length_inv; z *= length_inv; w = 1.0;
	}

	Vector4D& operator=(const Vector4D& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
	Vector4D operator+(const Vector4D& v)
	{ 
		Vector4D tmp;
		tmp.x = x + v.x; tmp.y = y + v.y; tmp.z = z + v.z; tmp.w = 1.0; 
		return tmp; 
	}
	Vector4D& operator+=(const Vector4D& v) { x += v.x; y += v.y; z += v.z; w = 1.0; return *this; }
	Vector4D operator-(const Vector4D& v)
	{ 
		Vector4D tmp;
		tmp.x = x - v.x; tmp.y = y - v.y; tmp.z = z - v.z; tmp.w = 1.0; 
		return tmp; 
	}
	Vector4D& operator-=(const Vector4D& v) { x -= v.x; y -= v.y; z -= v.z; w = 1.0; return *this; }
	Vector4D operator*(const double k)
	{ 
		Vector4D tmp;
		tmp.x = x * k; tmp.y = y * k; tmp.z = z * k; tmp.w = 1.0;
		return tmp; 
	}
	Vector4D& operator*=(const double k) { x *= k; y *= k; z *= k; w = 1.0; return *this; }

	double dot(const Vector4D* v) { return (x * v->x) + (y * v->y) + (z * v->z); }
	double cos(const Vector4D* v) { return  this->dot(v) / (this->length() * v->length()); }
	Vector4D cross(const Vector4D* v)
	{
		Vector4D tmp;
		tmp.x = (y * v->z) - (z * v->y); tmp.y = -((x * v->z) - (z * v->x));
		tmp.y = (x * v->y) - (y * v->x); tmp.w = 1.0;
		return tmp;
	}

	bool operator==(const Vector4D& v)
	{
		if (x == v.x && y == v.y && z == v.z && w == v.w)
			return true;
		return false;
	}
	bool operator!=(const Vector4D& v)
	{
		if (*this == v)
			return false;
		return true;
	}
};
typedef Vector4D* PVector4D;
typedef Vector4D Point4D;
typedef Point4D* PPoint4D;

#endif