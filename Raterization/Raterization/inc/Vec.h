#ifndef Vec_h
#define Vec_h

// Vector2, PVector2, Point2D
struct Vector2
{
	double x, y;

	Vector2() = default;
	~Vector2() = default;
	Vector2(double dx, double dy) : x(dx), y(dy) {}
	Vector2(const Vector2& v) { *this = v; }

	void Zero() { x = y = 0.0; }

	Vector2& operator=(const Vector2& v) { 
		x = v.x; y = v.y; 
		return *this; 
	}

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
typedef Vector2 Point2D;
typedef Vector2* PVector2;

// Vector3, PVector3, Point3D
struct Vector3
{
	double x, y, z;

	Vector3(){}
	~Vector3() = default;
	Vector3(double dx, double dy, double dz) : x(dx), y(dy), z(dz) {}
	Vector3(const Vector3& v) { *this = v; }

	void Zero() { x = y = z = 0.0; }
	Vector3& operator=(const Vector3& v) {
		x = v.x; y = v.y; z = v.z;
		return *this;
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
typedef Vector3 Point3D;
typedef Vector3* PVector3;

// Vector4, PVector4, Point4D
struct Vector4
{
	double x, y, z, w;

	Vector4(){}
	~Vector4() = default;
	Vector4(double dx, double dy, double dz, double dw) 
		: x(dx), y(dy), z(dz), w(dw) {}
	Vector4(const Vector4& v) { *this = v; }

	void Zero() { x = y = z = 0.0; w = 1.0; }
	Vector4& operator=(const Vector4& v) {
		x = v.x; y = v.y; z = v.z; w = v.w;
		return *this;
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
typedef Vector4 Point4D;
typedef Vector4* PVector4;

struct Vertex2
{
	double x, y;
};

#endif