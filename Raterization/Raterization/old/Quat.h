#ifndef Quat_h
#define Quat_h

struct Quat
{
	double real;
	double i, j, k;

	Quat() = default;
	~Quat() = default;

	Quat(const Quat& q) { *this = q; }
	Quat(double r, Vector3D v) : real(r), i(v.x), j(v.y), k(v.z) {}
	Quat(double r, double di, double dj, double dk)
		: real(r), i(di), j(dj), k(dk) {}

	void zero() { real = 0; i = 0; j = 0; k = 0; }
	void init(double r, Vector3D* v)
	{
		real = r; i = v->x; j = v->y; k = v->z;
	}
	void init(double r, double di, double dj, double dk)
	{
		real = r; i = di; j = dj; k = dk;
	}
	//void From_Vector3DTheta(Vector3D* v, double theta)
	void from_Vector3DTheta(Vector3D* v, double theta)
	{
		auto theta_div2 = theta / 2;
		auto sin_theta = sin(theta_div2);
		i = sin_theta * v->x;
		j = sin_theta * v->y;
		k = sin_theta * v->z;
		real = cos(theta_div2);
	}
	//void To_Vector3DTheta(Vector3D* v, double* theta)
	void to_Vector3DTheta(Vector3D* v, double* theta)
	{
		*theta = acos(real);
		auto theta_inv = 1.0 / sin(*theta);
		v->x = i * theta_inv;
		v->y = j * theta_inv;
		v->z = k * theta_inv;
		*theta *= 2;
	}
	//void From_ThetaXYZ(double thetax, double thetay, double thetaz)
	void from_EulerXYZ(double thetax, double thetay, double thetaz)
	{
		auto cosx_div2 = 0.5 * cos(thetax);
		auto cosy_div2 = 0.5 * cos(thetay);
		auto cosz_div2 = 0.5 * cos(thetaz);

		auto sinx_div2 = 0.5 * sin(thetax);
		auto siny_div2 = 0.5 * sin(thetay);
		auto sinz_div2 = 0.5 * sin(thetaz);

		real = cosx_div2 * cosy_div2 * cosz_div2 + sinx_div2 * siny_div2 * sinz_div2;
		i = sinx_div2 * cosy_div2 * cosz_div2 - cosx_div2 * siny_div2 * sinz_div2;
		j = cosx_div2 * siny_div2 * cosz_div2 + sinx_div2 * cosy_div2 * sinz_div2;
		k = cosx_div2 * cosy_div2 * sinz_div2 - sinx_div2 * siny_div2 * cosz_div2;
	}
	void conjugate(Quat* q) { q->real = real; q->i = -i; q->j = -j; q->k = -k; }
	Quat conjugate() { Quat q; q.real = real; q.i = -i; q.j = -j; q.k = -k; return q; }
	double norm() { return sqrt(real * real + i * i + j * j + k * k); }
	double norm2() { return (real * real + i * i + j * j + k * k); }
	void normalize()
	{
		auto norm_inv = 1.0 / this->norm();
		real *= norm_inv; i *= norm_inv; j *= norm_inv; k *= norm_inv;
	}
	void unit_inverse() { i = -i; j = -j; k = -k; }
	void inverse()
	{
		auto norm2_inv = 1.0 / this->norm2();
		real *= norm2_inv; i *= norm2_inv; j *= norm2_inv; k *= norm2_inv;
	}
	void scale(const double s) { real *= s; i *= s; j *= s; k *= s; }
	void triple_product(const Quat& q1, const Quat& q2)
	{
		*this *= q1; *this *= q2;
	}

	Quat& operator=(const Quat& q) { real = q.real; i = q.i; j = q.j; k = q.k; return *this; }
	Quat operator+(const Quat& q) 
	{
		Quat tmp;
		tmp.real = real + q.real; tmp.i = i + q.i; tmp.j = j + q.j; tmp.k = k + q.k;
		return tmp;
	}
	Quat& operator+=(const Quat& q) { real += q.real; i += q.i; j += q.j; k += q.k; return *this; }
	Quat operator-(const Quat& q) 
	{
		Quat tmp;
		tmp.real = real - q.real; tmp.i = i - q.i; tmp.j = j - q.j; tmp.k = k - q.k;
		return tmp;
	}
	Quat& operator-=(const Quat& q) { real -= q.real; i -= q.i; j -= q.j; k -= q.k; return *this; }
	Quat& operator*(const double s) { *this *= s; return *this; }
	Quat& operator*=(const double s) { real *= s; i *= s; j *= s; k *= s; return *this; }
	Quat operator*(const Quat& q) 
	{
		Quat tmp;
		tmp.real = real * q.real - i * q.i - j * q.j - k * q.k;
		tmp.i = real * q.i + i * q.real + j * q.k - k * q.j;
		tmp.j = real * q.j - i * q.k + j * q.real - k * q.i;
		tmp.k = real * q.k + i * q.j - j * q.i + k * q.real;
		return tmp;
	}
	Quat& operator*=(const Quat& q) 
	{ 
		Quat tmp;
		tmp.real = real * q.real - i * q.i - j * q.j - k * q.k;
		tmp.i = real * q.i + i * q.real + j * q.k - k * q.j;
		tmp.j = real * q.j - i * q.k + j * q.real - k * q.i;
		tmp.k = real * q.k + i * q.j - j * q.i + k * q.real;
		*this = tmp;
		return *this;
	}
};

#endif