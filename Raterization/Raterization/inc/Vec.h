#ifndef Vec_h
#define Vec_h

#include <algorithm>
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define EPSILON_E3 (double)(1E-3)
#define EPSILON_E4 (double)(1E-4)
#define EPSILON_E5 (double)(1E-5)
#define EPSILON_E6 (double)(1E-6)

// Vector2, PVector2, Point2D, PPoint2D
struct Vector2
{
	double x, y;

	Vector2() = default;
	~Vector2() = default;
	// Constructor
	Vector2(double dx, double dy) : x(dx), y(dy) {}
	Vector2(const Vector2& v) { *this = v; }
	// Build from Point2D
	void Vector2_Build(const Vector2* begin, const Vector2* end) {
		x = end->x - begin->x; y = end->y - begin->y;
	}


	void Zero() { x = y = 0.0; }
	double Length() const { return sqrt(x*x + y*y); }
	double Fast_Length() {
		auto dx = abs(x); auto dy = abs(y); auto m = (int)MIN(dx, dy);
		return (dx + dy - (m >> 1) - (m >> 2) + (m >> 4));
	}
	void Normalize() {
		auto length = this->Length();
		if (length < EPSILON_E5) return;
		auto length_inv = 1.0 / length;
		x = x * length_inv; y = y * length_inv;
	}

	Vector2& operator=(const Vector2& v) { x = v.x; y = v.y; return *this; }
	Vector2& operator+(const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator-(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator*(double k) { x *= k; y *= k; return *this; }
	double Dot(const Vector2* v) { return x * v->x + y * v->y; }
	double Cos(const Vector2* v) { return this->Dot(v) / (this->Length() * v->Length()); }
	
	bool operator==(const Vector2& v) {
		if (x == v.x && y == v.y)
			return true;
		return false;
	}
	bool operator!=(const Vector2& v) {
		if (*this == v)
			return false;
		return true;
	}
};
typedef Vector2* PVector2;
typedef Vector2 Point2D;
typedef Point2D* PPoint2D;

// Vector3, PVector3, Point3D, PPoint3D
struct Vector3
{
	double x, y, z;

	Vector3() = default;
	~Vector3() = default;
	// Constructor
	Vector3(double dx, double dy, double dz) : x(dx), y(dy), z(dz) {}
	Vector3(const Vector3& v) { *this = v; }
	// Build from Point3D
	Vector3(const Vector3* begin, const Vector3* end) {
		x = end->x - begin->x; y = end->y - begin->y; z = end->z - begin->z;
	}

	void Zero() { x = y = z = 0.0; }
	double Length() const { return sqrt(x*x + y*y + z*z); }
	double Fast_Length() {
		int ix, iy, iz;
		ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
		if (y < x) std::swap(ix, iy);
		if (z < y) std::swap(iy, iz);
		if (y < x) std::swap(ix, iy);
		auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
		return ((double)(dist >> 10));
	}
	void Normalize() {
		auto length = this->Length();
		if (length < EPSILON_E5)
			return;
		auto length_inv = 1.0 / length;
		x *= length_inv; y *= length_inv; z *= length_inv;
	}
	Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
	Vector3& operator+(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3& operator-(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3& operator*(double k) { x *= k; y *= k; z *= k; return *this; }
	double Dot(const Vector3* v) { return x * v->x + y * v->y + z * v->z; }
	double Cos(const Vector3* v) { return this->Dot(v) / (this->Length() * v->Length()); }
	void Cross(Vector3* v) {
		x = (y * v->z) - (z * v->y); y = -((x * v->z) - (z * v->x)); z = (x * v->y) - (y * v->x);
	}

	bool operator==(const Vector3& v) {
		if (x == v.x && y == v.y && z == v.z)
			return true;
		return false;
	}
	bool operator!=(const Vector3& v) {
		if (*this == v)
			return false;
		return true;
	}
};
typedef Vector3* PVector3;
typedef Vector3 Point3D;
typedef Point3D* PPoint3D;

// Vector4, PVector4, Point4D, PPoint4D
struct Vector4
{
	double x, y, z, w;

	Vector4(){}
	~Vector4() = default;
	// Constructor
	Vector4(double dx, double dy, double dz, double dw)
		: x(dx), y(dy), z(dz), w(dw) {}
	Vector4(const Vector4& v) { *this = v; }
	// Build from Point4D
	Vector4(const Vector4* begin, const Vector4* end) {
		x = end->x - begin->x; y = end->y - begin->y;
		z = end->z - begin->z; w = 1.0;
	}

	void Zero() { x = y = z = 0.0; w = 1.0; }
	double Length() const { return sqrt(x*x + y*y + z*z); }
	double Fast_length() {
		int ix, iy, iz;
		ix = (int)abs(x) * 1024; iy = (int)abs(y) * 1024; iz = (int)abs(z) * 1024;
		if (y < x) std::swap(ix, iy);
		if (z < y) std::swap(iy, iz);
		if (y < x) std::swap(ix, iy);
		auto dist = (iz + 11 * (iy >> 5) + (ix >> 2));
		return ((double)(dist >> 10));
	}
	void Normalize() {
		auto length = this->Length();
		if (length < EPSILON_E5)
			return;
		auto length_inv = 1.0 / length;
		x *= length_inv; y *= length_inv; z *= length_inv; w = 1.0;
	}
	Vector4& operator=(const Vector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
	Vector4& operator+(const Vector4& v) { x += v.x; y += v.y; z += v.z; w = 1.0; return *this; }
	Vector4& operator-(const Vector4& v) { x -= v.x; y -= v.y; z -= v.z; w = 1.0; return *this; }
	Vector4& operator*(const double k) { x *= k; y *= k; z *= k; w = 1.0; }
	double Dot(const Vector4* v) { return (x * v->x) + (y * v->y) + (z * v->z); }
	double Cos(const Vector4* v) { return  this->Dot(v) / (this->Length() * v->Length()); }
	void Cross(const Vector4* v) {
		x = (y * v->z) - (z * v->y); y = -((x * v->z) - (z * v->x));
		y = (x * v->y) - (y * v->x); w = 1.0;
	}

	bool operator==(const Vector4& v) {
		if (x == v.x && y == v.y && z == v.z && w == v.w)
			return true;
		return false;
	}
	bool operator!=(const Vector4& v) {
		if (*this == v)
			return false;
		return true;
	}
};
typedef Vector4* PVector4;
typedef Vector4 Point4D;
typedef Point4D* PPoint4D;

#endif