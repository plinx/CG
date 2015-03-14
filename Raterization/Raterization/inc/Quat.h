#ifndef Quat_h
#define Quat_h

struct Quat
{
	double real;
	double x, y, z;

	Quat(double r, Vector3 i) : real(r), x(i.x), y(i.y), z(i.z) {}
	Quat(double r, double dx, double dy, double dz)
		: real(r), x(dx), y(dy), z(dz) {}

	Quat(const Quat& q) { *this = q; }
	void Zero() { real = 0; x = 0; y = 0; z = 0; }
	Quat& operator=(const Quat& q) {
		real = q.real; x = q.x; y = q.y; z = q.z;
	}

};

#endif