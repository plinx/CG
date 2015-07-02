#ifndef Vector_h
#define Vector_h

#include <iostream>
#include <memory>

#define EPSILON_E5 (float)(1E-5)

// Vector2D, PVector2D, Point2D, PPoint2D
struct Vector2D
{
	float x, y;

	Vector2D() = default;
	~Vector2D() = default;
	// Constructor
	Vector2D(const Vector2D& v) { *this = v; }
	Vector2D(float dx, float dy) : x(dx), y(dy) {}
	Vector2D(const Vector2D* begin, const Vector2D* end)
		: x(end->x - begin->x), y(end->y - begin->y) {}

	// basic methods
	void zero();
	void init(float ix, float iy);
	void init(const Vector2D* begin, const Vector2D* end);
	float length() const;
	float dot(const Vector2D* v);
	float cos(const Vector2D* v);
	Vector2D reverse();
	Vector2D& normalize();

	// override operator
	Vector2D& operator=(const Vector2D& v);
	Vector2D operator+(const Vector2D& v);
	Vector2D& operator+=(const Vector2D& v);
	Vector2D operator-(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D operator*(float k);
	Vector2D& operator*=(float k);
	bool operator==(const Vector2D& v);
	bool operator!=(const Vector2D& v);
};
typedef Vector2D* PVector2D;
typedef Vector2D Point2D;
typedef Point2D* PPoint2D;

// Vector3D, PVector3D, Point3D, PPoint3D
struct Vector3D
{
	float x, y, z;

	Vector3D() = default;
	~Vector3D() = default;
	// Constructor
	Vector3D(const Vector3D& v) { *this = v; }
	Vector3D(float dx, float dy, float dz) : x(dx), y(dy), z(dz) {}
	Vector3D(const Vector3D* begin, const Vector3D* end);

	// basic methods
	void zero();
	void init(float ix, float iy, float iz);
	void init(const Vector3D* begin, const Vector3D* end);
	float length() const;
	float Fast_length();
	float dot(const Vector3D* v);
	float cos(const Vector3D* v);
	Vector3D cross(Vector3D* v);
	Vector3D reverse();
	Vector3D& normalize();

	// overrride operator
	Vector3D& operator=(const Vector3D& v);
	Vector3D operator+(const Vector3D& v);
	Vector3D& operator+=(const Vector3D& v);
	Vector3D operator-(const Vector3D& v);
	Vector3D& operator-=(const Vector3D& v);
	Vector3D operator*(float k);
	Vector3D& operator*=(float k);
	bool operator==(const Vector3D& v);
	bool operator!=(const Vector3D& v);
};
typedef Vector3D* PVector3D;
typedef Vector3D Point3D;
typedef Point3D* PPoint3D;

// Vector4D, PVector4D, Point4D, PPoint4D
struct Vector4D
{
	float x, y, z, w;

	Vector4D() = default;
	~Vector4D() = default;
	// Constructor
	Vector4D(const Vector4D& v) { *this = v; }
	Vector4D(float dx, float dy, float dz, float dw)
		: x(dx), y(dy), z(dz), w(dw) {}
	Vector4D(const Vector4D* begin, const Vector4D* end);

	// basic methods
	void print();
	void zero();
	void init(float dx, float dy, float dz);
	void init(const Vector4D* begin, const Vector4D* end);
	float length() const;
	float Fast_length();
	float dot(const Vector4D* v);
	float cos(const Vector4D* v);
	Vector4D cross(const Vector4D* v);
	Vector4D reverse();
	Vector4D& normalize();

	// override operator
	Vector4D& operator=(const Vector4D& v);
	Vector4D operator+(const Vector4D& v);
	Vector4D& operator+=(const Vector4D& v);
	Vector4D operator-(const Vector4D& v);
	Vector4D& operator-=(const Vector4D& v);
	Vector4D operator*(const float k);
	Vector4D& operator*=(const float k);
	Vector4D& operator/=(const float k);
	Vector4D operator/(const float k);
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

inline void Vector2D::init(float ix, float iy) 
{
	x = ix; y = iy; 
}

inline void Vector2D::init(const Vector2D* begin, const Vector2D* end)
{
	x = end->x - begin->x; y = end->y - begin->y;
}

inline float Vector2D::length() const 
{ 
	return sqrt(x * x + y * y); 
}

inline float Vector2D::dot(const Vector2D* v) 
{
	return x * v->x + y * v->y; 
}

inline float Vector2D::cos(const Vector2D* v) 
{ 
	return this->dot(v) / (this->length() * v->length()); 
}

inline Vector2D Vector2D::reverse()
{
	Vector2D tmp(*this);
	tmp.x = -tmp.x; tmp.y = -tmp.y;
	return tmp;
}

inline Vector2D& Vector2D::normalize()
{
	float length = this->length();
	if (length < EPSILON_E5) return *this;
	float length_inv = (float)(1.0 / length);
	x = x * length_inv; y = y * length_inv;
	return *this;
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

inline Vector2D Vector2D::operator*(float k)
{
	Vector2D tmp;
	tmp.x = x * k; tmp.y = y * k;
	return tmp;
}

inline Vector2D& Vector2D::operator*=(float k) 
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

inline void Vector3D::init(float ix, float iy, float iz) 
{ 
	x = ix; y = iy; z = iz; 
}

inline void Vector3D::init(const Vector3D* begin, const Vector3D* end)
{
	x = end->x - begin->x; y = end->y - begin->y; z = end->z - begin->z;
}

inline float Vector3D::length() const 
{ 
	return sqrt(x * x + y * y + z * z); 
}

inline float Vector3D::Fast_length()
{
	int ix, iy, iz;
	ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
	if (y < x) std::swap(ix, iy);
	if (z < y) std::swap(iy, iz);
	if (y < x) std::swap(ix, iy);
	auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
	return ((float)(dist >> 10));
}

inline float Vector3D::dot(const Vector3D* v) 
{ 
	return x * v->x + y * v->y + z * v->z; 
}

inline float Vector3D::cos(const Vector3D* v) 
{ 
	return this->dot(v) / (this->length() * v->length()); 
}

inline Vector3D Vector3D::cross(Vector3D* v)
{
	Vector3D tmp;
	tmp.x = (y * v->z) - (z * v->y); tmp.y = -((x * v->z) - (z * v->x)); tmp.z = (x * v->y) - (y * v->x);
	return tmp;
}

inline Vector3D Vector3D::reverse()
{
	Vector3D tmp(*this);
	tmp.x = -tmp.x; tmp.y = -tmp.y; tmp.z = -tmp.z;
	return *this;
}

inline Vector3D& Vector3D::normalize()
{
	float length = this->length();
	if (length < EPSILON_E5) return *this;
	float length_inv = (float)(1.0 / length);
	x *= length_inv; y *= length_inv; z *= length_inv;
	return *this;
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

inline Vector3D Vector3D::operator*(float k)
{
	Vector3D tmp;
	tmp.x = x * k; tmp.y = y * k; tmp.z = z * k;
	return tmp;
}

inline Vector3D& Vector3D::operator*=(float k) 
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

inline void Vector4D::init(float dx, float dy, float dz) 
{ 
	x = dx; y = dy; z = dz; w = 1.0; 
}

inline void Vector4D::init(const Vector4D* begin, const Vector4D* end)
{
	x = end->x - begin->x; y = end->y - begin->y;
	z = end->z - begin->z; w = 1.0;
}

inline float Vector4D::length() const 
{ 
	return sqrt(x * x + y * y + z * z); 
}

inline float Vector4D::Fast_length()
{
	int ix, iy, iz;
	ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
	if (y < x) std::swap(ix, iy);
	if (z < y) std::swap(iy, iz);
	if (y < x) std::swap(ix, iy);
	auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
	return ((float)(dist >> 10));
}

inline float Vector4D::dot(const Vector4D* v) 
{
	return x * v->x + y * v->y + z * v->z;  // right-handed coordinate
	//return x * v->x - y * v->y + z * v->z;	  // left-handed coordinate
}

inline float Vector4D::cos(const Vector4D* v) 
{
	return  this->dot(v) / (this->length() * v->length()); 
}

inline Vector4D Vector4D::cross(const Vector4D* v)
{
	Vector4D tmp;
	tmp.x = (y * v->z) - (z * v->y); 
	tmp.y = (z * v->x) - (x * v->z); // this is a right-handed coordinate
	//tmp.y = (x * v->z) - (z * v->x); // this is a left-handed coordinate
	tmp.z = (x * v->y) - (y * v->x); 
	tmp.w = 1.0;
	return tmp;
}

inline Vector4D Vector4D::reverse()
{
	Vector4D tmp(*this);
	tmp.x = -tmp.x; tmp.y = -tmp.y; tmp.z = -tmp.z; tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::normalize()
{
	float length = this->length();
	if (length < EPSILON_E5) return *this;
	float length_inv = (float)(1.0 / length);
	x *= length_inv; y *= length_inv; z *= length_inv; w = 1.0;
	return *this;
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

inline Vector4D Vector4D::operator*(const float k)
{
	Vector4D tmp;
	tmp.x = x * k; tmp.y = y * k; tmp.z = z * k; tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::operator/=(const float k) 
{ 
	x /= k; y /= k; z /= k; w = 1.0; return *this; 
}

inline Vector4D Vector4D::operator/(const float k)
{
	Vector4D tmp;
	tmp.x = x / k; tmp.y = y / k; tmp.z = z / k; tmp.w = 1.0;
	return tmp;
}

inline Vector4D& Vector4D::operator*=(const float k)
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