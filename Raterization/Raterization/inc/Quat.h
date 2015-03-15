#ifndef Quat_h
#define Quat_h

struct Quat
{
	double real;
	double x, y, z;

	Quat() = default;
	~Quat() = default;
	Quat(double r, Vector3 i) : real(r), x(i.x), y(i.y), z(i.z) {}
	Quat(double r, double dx, double dy, double dz)
		: real(r), x(dx), y(dy), z(dz) {}

	Quat(const Quat& q) { *this = q; }
	void Zero() { real = 0; x = 0; y = 0; z = 0; }
	void From_Vector3Theta(Vector3* v, double theta) {
		auto theta_div2 = theta / 2;
		auto sin_theta = sin(theta_div2);
		x = sin_theta * v->x;
		y = sin_theta * v->y;
		z = sin_theta * v->z;
		real = cos(theta_div2);
	}
	void To_Vector3Theta(Vector3* v, double* theta) {
		*theta = acos(real);
		auto theta_inv = 1.0 / sin(*theta);
		v->x = x * theta_inv;
		v->y = y * theta_inv;
		v->z = z * theta_inv;
		*theta *= 2;
	}
	void From_ThetaXYZ(double thetax, double thetay, double thetaz) {
		auto cosx_div2 = 0.5 * cos(thetax);
		auto cosy_div2 = 0.5 * cos(thetay);
		auto cosz_div2 = 0.5 * cos(thetaz);

		auto sinx_div2 = 0.5 * sin(thetax);
		auto siny_div2 = 0.5 * sin(thetay);
		auto sinz_div2 = 0.5 * sin(thetaz);

		real = cosx_div2 * cosy_div2 * cosz_div2 + sinx_div2 * siny_div2 * sinz_div2;
		x = sinx_div2 * cosy_div2 * cosz_div2 - cosx_div2 * siny_div2 * sinz_div2;
		y = cosx_div2 * siny_div2 * cosz_div2 + sinx_div2 * cosy_div2 * sinz_div2;
		z = cosx_div2 * cosy_div2 * sinz_div2 - sinx_div2 * siny_div2 * cosz_div2;
	}
	void Conjugate(Quat* q) { q->real = real; q->x = -x; q->y = -y; q->z = -z; }
	Quat Conjugate() { Quat q; q.real = real; q.x = -x; q.y = -y; q.z = -z; return q; }
	double Norm() { return sqrt(real * real + x * x + y * y + z * z); }
	double Norm2() { return (real * real + x * x + y * y + z * z); }
	void Normalize() {
		auto norm_inv = 1.0 / this->Norm();
		real *= norm_inv; x *= norm_inv; y *= norm_inv; z *= norm_inv;
	}
	void Unit_Inverse() { x = -x; y = -y; z = -z; }
	void Inverse() {
		auto norm2_inv = 1.0 / this->Norm2();
		real *= norm2_inv; x *= norm2_inv; y *= norm2_inv; z *= norm2_inv;
	}
	void Scale(const double k) { real *= k; x *= k; y *= k; z *= k; }
	void Triple_Product(const Quat& q1, const Quat& q2) {
		*this *= q1; *this *= q2;
	}

	Quat& operator=(const Quat& q) { real = q.real; x = q.x; y = q.y; z = q.z; }
	Quat& operator+(const Quat& q) { *this += q; }
	Quat& operator+=(const Quat& q) { real += q.real; x += q.x; y += q.y; z += q.z; }
	Quat& operator-(const Quat& q) { *this -= q; }
	Quat& operator-=(const Quat& q) { real -= q.real; x -= q.x; y -= q.y; z -= q.z; }
	Quat& operator*(const Quat& q) { *this *= q; }
	Quat& operator*(const double k) { *this *= k; }
	Quat& operator*=(const double k) { real *= k; x *= x; y *= y; z *= z; }
	Quat& operator*=(const Quat& q) { 
		Quat tmp;
		tmp.real = real * q.real - x * q.x - y * q.y - z * q.z;
		tmp.x = real * q.x + x * q.real + y * q.z - z * q.y;
		tmp.y = real * q.y - x * q.z + y * q.real - z * q.x;
		tmp.z = real * q.z + x * q.y - y * q.x + z * q.real;
	}
};

#endif