#ifndef Vector_h
#define Vector_h

#include <iostream>
#include <memory>

#define EPSILON_E5 (double)(1E-5)

// Vector2D, PVector2D, Point2D, PPoint2D
struct Vector2D
{
	double x, y;

	Vector2D() = default;
	~Vector2D() = default;
	// Constructor
	Vector2D(const Vector2D& v) { *this = v; }
	Vector2D(double dx, double dy) : x(dx), y(dy) {}
	Vector2D(const Vector2D* begin, const Vector2D* end)
		: x(end->x - begin->x), y(end->y - begin->y) {}

	// basic methods
	void zero();
	void init(double ix, double iy);
	void init(const Vector2D* begin, const Vector2D* end);
	double length() const;
	void normalize();
	double dot(const Vector2D* v);
	double cos(const Vector2D* v);

	// override operator
	Vector2D& operator=(const Vector2D& v);
	Vector2D operator+(const Vector2D& v);
	Vector2D& operator+=(const Vector2D& v);
	Vector2D operator-(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D operator*(double k);
	Vector2D& operator*=(double k);
	bool operator==(const Vector2D& v);
	bool operator!=(const Vector2D& v);
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
	Vector3D(const Vector3D& v) { *this = v; }
	Vector3D(double dx, double dy, double dz) : x(dx), y(dy), z(dz) {}
	Vector3D(const Vector3D* begin, const Vector3D* end);

	// basic methods
	void zero();
	void init(double ix, double iy, double iz);
	void init(const Vector3D* begin, const Vector3D* end);
	double length() const;
	double Fast_length();
	void normalize();
	double dot(const Vector3D* v);
	double cos(const Vector3D* v);
	Vector3D cross(Vector3D* v);

	// overrride operator
	Vector3D& operator=(const Vector3D& v);
	Vector3D operator+(const Vector3D& v);
	Vector3D& operator+=(const Vector3D& v);
	Vector3D operator-(const Vector3D& v);
	Vector3D& operator-=(const Vector3D& v);
	Vector3D operator*(double k);
	Vector3D& operator*=(double k);
	bool operator==(const Vector3D& v);
	bool operator!=(const Vector3D& v);
};
typedef Vector3D* PVector3D;
typedef Vector3D Point3D;
typedef Point3D* PPoint3D;

// Vector4D, PVector4D, Point4D, PPoint4D
struct Vector4D
{
	double x, y, z, w;

	Vector4D() = default;
	~Vector4D() = default;
	// Constructor
	Vector4D(const Vector4D& v) { *this = v; }
	Vector4D(double dx, double dy, double dz, double dw)
		: x(dx), y(dy), z(dz), w(dw) {}
	Vector4D(const Vector4D* begin, const Vector4D* end);

	// basic methods
	void print();
	void zero();
	void init(double dx, double dy, double dz);
	void init(const Vector4D* begin, const Vector4D* end);
	double length() const;
	double Fast_length();
	void normalize();
	double dot(const Vector4D* v);
	double cos(const Vector4D* v);
	Vector4D cross(const Vector4D* v);

	// override operator
	Vector4D& operator=(const Vector4D& v);
	Vector4D operator+(const Vector4D& v);
	Vector4D& operator+=(const Vector4D& v);
	Vector4D operator-(const Vector4D& v);
	Vector4D& operator-=(const Vector4D& v);
	Vector4D operator*(const double k);
	Vector4D& operator*=(const double k);
	bool operator==(const Vector4D& v);
	bool operator!=(const Vector4D& v);
};
typedef Vector4D* PVector4D;
typedef Vector4D Point4D;
typedef Point4D* PPoint4D;


// Vector2D methods implement
inline void Vector2D::zero() 
{ 
	x = y = 0.0; 
}

inline void Vector2D::init(double ix, double iy) 
{
	x = ix; y = iy; 
}

inline void Vector2D::init(const Vector2D* begin, const Vector2D* end)
{
	x = end->x - begin->x; y = end->y - begin->y;
}

inline double Vector2D::length() const 
{ 
	return sqrt(x*x + y*y); 
}

inline void Vector2D::normalize()
{
	double length = this->length();
	if (length < EPSILON_E5) return;
	double length_inv = 1.0 / length;
	x = x * length_inv; y = y * length_inv;
}

inline double Vector2D::dot(const Vector2D* v) 
{
	return x * v->x + y * v->y; 
}

inline double Vector2D::cos(const Vector2D* v) 
{ 
	return this->dot(v) / (this->length() * v->length()); 
}

inline Vector2D& Vector2D::operator=(const Vector2D& v) 
{
	x = v.x; y = v.y; 
	return *this; 
}

inline Vector2D Vector2D::operator+(const Vector2D& v)
{
	Vector2D tmp;
	tmp.x = x + v.x; tmp.y = y + v.y;
	return tmp;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v) 
{
	x += v.x; y += v.y; 
	return *this; 
}

inline Vector2D Vector2D::operator-(const Vector2D& v)
{
	Vector2D tmp;
	tmp.x = x - v.x; tmp.y = y - v.y;
	return tmp;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v) 
{
	x -= v.x; y -= v.y; 
	return *this; 
}

inline Vector2D Vector2D::operator*(double k)
{
	Vector2D tmp;
	tmp.x = x * k; tmp.y = y * k;
	return tmp;
}

inline Vector2D& Vector2D::operator*=(double k) 
{
	x *= k; y *= k; 
	return *this; 
}

inline bool Vector2D::operator==(const Vector2D& v)
{
	if (x == v.x && y == v.y)
		return true;
	return false;
}

inline bool Vector2D::operator!=(const Vector2D& v)
{
	if (*this == v)
		return false;
	return true;
}

// Vector3D methods implement
inline Vector3D::Vector3D(const Vector3D* begin, const Vector3D* end)
{
	x = end->x - begin->x; y = end->y - begin->y; z = end->z - begin->z;
}

inline void Vector3D::zero() 
{ 
	x = y = z = 0.0; 
}

inline void Vector3D::init(double ix, double iy, double iz) 
{ 
	x = ix; y = iy; z = iz; 
}

inline void Vector3D::init(const Vector3D* begin, const Vector3D* end)
{
	x = end->x - begin->x; y = end->y - begin->y; z = end->z - begin->z;
}

inline double Vector3D::length() const 
{ 
	return sqrt(x*x + y*y + z*z); 
}

inline double Vector3D::Fast_length()
{
	int ix, iy, iz;
	ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
	if (y < x) std::swap(ix, iy);
	if (z < y) std::swap(iy, iz);
	if (y < x) std::swap(ix, iy);
	auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
	return ((double)(dist >> 10));
}

inline void Vector3D::normalize()
{
	auto length = this->length();
	if (length < EPSILON_E5)
		return;
	auto length_inv = 1.0 / length;
	x *= length_inv; y *= length_inv; z *= length_inv;
}

inline double Vector3D::dot(const Vector3D* v) 
{ 
	return x * v->x + y * v->y + z * v->z; 
}

inline double Vector3D::cos(const Vector3D* v) 
{ 
	return this->dot(v) / (this->length() * v->length()); 
}

inline Vector3D Vector3D::cross(Vector3D* v)
{
	Vector3D tmp;
	tmp.x = (y * v->z) - (z * v->y); tmp.y = -((x * v->z) - (z * v->x)); tmp.z = (x * v->y) - (y * v->x);
	return tmp;
}

inline Vector3D& Vector3D::operator=(const Vector3D& v)
{ 
	x = v.x; y = v.y; z = v.z; return *this; 
}

inline Vector3D Vector3D::operator+(const Vector3D& v)
{
	Vector3D tmp;
	tmp.x = x + v.x; tmp.y = y + v.y; tmp.z = z + v.z;
	return tmp;
}

inline Vector3D& Vector3D::operator+=(const Vector3D& v) 
{ 
	x += v.x; y += v.y; z += v.z; return *this; 
}

inline Vector3D Vector3D::operator-(const Vector3D& v)
{
	Vector3D tmp;
	tmp.x = x - v.x; tmp.y = y - v.y; tmp.z = z - v.z;
	return tmp;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& v) 
{
	x -= v.x; y -= v.y; z -= v.z; return *this; 
}

inline Vector3D Vector3D::operator*(double k)
{
	Vector3D tmp;
	tmp.x = x * k; tmp.y = y * k; tmp.z = z * k;
	return tmp;
}

inline Vector3D& Vector3D::operator*=(double k) 
{ 
	x *= k; y *= k; z *= k; return *this; 
}

inline bool Vector3D::operator==(const Vector3D& v)
{
	if (x == v.x && y == v.y && z == v.z)
		return true;
	return false;
}

inline bool Vector3D::operator!=(const Vector3D& v)
{
	if (*this == v)
		return false;
	return true;
}

// Vector4D methods implement
inline Vector4D::Vector4D(const Vector4D* begin, const Vector4D* end)
{
	x = end->x - begin->x; y = end->y - begin->y;
	z = end->z - begin->z; w = 1.0;
}

inline void Vector4D::print() 
{
	std::cout << "(" << x << ", " << y << ", " << z << ")"; 
}

inline void Vector4D::zero() 
{ 
	x = y = z = 0.0; w = 1.0; 
}

inline void Vector4D::init(double dx, double dy, double dz) 
{ 
	x = dx; y = dy; z = dz; w = 1.0; 
}

inline void Vector4D::init(const Vector4D* begin, const Vector4D* end)
{
	x = end->x - begin->x; y = end->y - begin->y;
	z = end->z - begin->z; w = 1.0;
}

inline double Vector4D::length() const 
{ 
	return sqrt(x*x + y*y + z*z); 
}

inline double Vector4D::Fast_length()
{
	int ix, iy, iz;
	ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
	if (y < x) std::swap(ix, iy);
	if (z < y) std::swap(iy, iz);
	if (y < x) std::swap(ix, iy);
	auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
	return ((double)(dist >> 10));
}

inline void Vector4D::normalize()
{
	auto length = this->length();
	if (length < EPSILON_E5)
		return;
	auto length_inv = 1.0 / length;
	x *= length_inv; y *= length_inv; z *= length_inv; w = 1.0;
}

inline double Vector4D::dot(const Vector4D* v) 
{
	return x * v->x + y * v->y + z * v->z; 
}

inline double Vector4D::cos(const Vector4D* v) 
{
	return  this->dot(v) / (this->length() * v->length()); 
}

inline Vector4D Vector4D::cross(const Vector4D* v)
{
	Vector4D tmp;
	tmp.x = (y * v->z) - (z * v->y); tmp.y = -((x * v->z) - (z * v->x));
	tmp.z = (x * v->y) - (y * v->x); tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::operator=(const Vector4D& v) 
{ 
	x = v.x; y = v.y; z = v.z; w = v.w; return *this; 
}

inline Vector4D Vector4D::operator+(const Vector4D& v)
{
	Vector4D tmp;
	tmp.x = x + v.x; tmp.y = y + v.y; tmp.z = z + v.z; tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::operator+=(const Vector4D& v) 
{
	x += v.x; y += v.y; z += v.z; w = 1.0; return *this; 
}

inline Vector4D Vector4D::operator-(const Vector4D& v)
{
	Vector4D tmp;
	tmp.x = x - v.x; tmp.y = y - v.y; tmp.z = z - v.z; tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::operator-=(const Vector4D& v) 
{ 
	x -= v.x; y -= v.y; z -= v.z; w = 1.0; return *this; 
}
inline Vector4D Vector4D::operator*(const double k)
{
	Vector4D tmp;
	tmp.x = x * k; tmp.y = y * k; tmp.z = z * k; tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::operator*=(const double k) 
{ 
	x *= k; y *= k; z *= k; w = 1.0; return *this; 
}

inline bool Vector4D::operator==(const Vector4D& v)
{
	if (x == v.x && y == v.y && z == v.z && w == v.w)
		return true;
	return false;
}

inline bool Vector4D::operator!=(const Vector4D& v)
{
	if (*this == v)
		return false;
	return true;
}

#endif