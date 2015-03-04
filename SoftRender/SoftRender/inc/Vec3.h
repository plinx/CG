#ifndef Vec3_h
#define Vec3_h

#include <math.h>

class Vec3
{
private:
	double x, y, z;

public:
	Vec3() : x(0), y(0), z(0) {}
	Vec3(double fx, double fy, double fz) : x(fx), y(fy), z(fz) {}
	~Vec3() = default;

	Vec3 copy() { return Vec3(x, y, z); }
	double length() { return sqrt(x * x + y * y + z * z); }
	double sqrLength() { return x * x + y * y + z * z; }
	Vec3 normalize() {
		double inv = 1 / length();
		return Vec3(x * inv, y * inv, z * inv);
	}
	Vec3 negate() { return Vec3(-x, -y, -z); }
	Vec3 add(Vec3 v) { return Vec3(x + v.x, y + v.y, z + v.z); }
	Vec3 sub(Vec3 v) { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3 mul(double f) { return Vec3(x * f, y * f, z * f); }
	Vec3 divide(double f) {
		double invf = 1 / f;
		return Vec3(x * invf, y * invf, z * invf);
	}
	double dot(Vec3 v) { return x * v.x + y * v.y + z * v.z; }
	Vec3 cross(Vec3 v) {
		return Vec3(-z * v.y + y * v.z, z * v.x - x * v.z, -y * x + x * v.y);
	}
};

#endif
