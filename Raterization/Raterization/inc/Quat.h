#ifndef Quat_h
#define Quat_h

struct Quat
{
	double real;
	double i, j, k;

	// Contructor
	Quat() = default;
	~Quat() = default;
	Quat(const Quat& q) { *this = q; }
	Quat(double r, Vector3D v) : real(r), i(v.x), j(v.y), k(v.z) {}
	Quat(double r, double di, double dj, double dk)
		: real(r), i(di), j(dj), k(dk) {}

	// basic methods
	void zero();
	void init(double r, Vector3D* v);
	void init(double r, double di, double dj, double dk);
	void from_Vector3DTheta(Vector3D* v, double theta);
	void to_Vector3DTheta(Vector3D* v, double* theta);
	void from_EulerXYZ(double thetax, double thetay, double thetaz);
	void conjugate(Quat* q);
	Quat conjugate();
	double norm();
	double norm2();
	void normalize();
	void unit_inverse();
	void inverse();
	void scale(const double s);
	void triple_product(const Quat& q1, const Quat& q2);

	// override operator
	Quat& operator=(const Quat& q);
	Quat operator+(const Quat& q);
	Quat& operator+=(const Quat& q);
	Quat operator-(const Quat& q);
	Quat& operator-=(const Quat& q);
	Quat& operator*(const double s);
	Quat& operator*=(const double s);
	Quat operator*(const Quat& q);
	Quat& operator*=(const Quat& q);
};

// Quat methods implement
inline void Quat::zero() 
{ 
	real = 0; i = 0; j = 0; k = 0; 
}

inline void Quat::init(double r, Vector3D* v)
{
	real = r; i = v->x; j = v->y; k = v->z;
}

inline void Quat::init(double r, double di, double dj, double dk)
{
	real = r; i = di; j = dj; k = dk;
}

inline void Quat::from_Vector3DTheta(Vector3D* v, double theta)
{
	auto theta_div2 = theta / 2;
	auto sin_theta = sin(theta_div2);
	i = sin_theta * v->x;
	j = sin_theta * v->y;
	k = sin_theta * v->z;
	real = cos(theta_div2);
}

inline void Quat::to_Vector3DTheta(Vector3D* v, double* theta)
{
	*theta = acos(real);
	auto theta_inv = 1.0 / sin(*theta);
	v->x = i * theta_inv;
	v->y = j * theta_inv;
	v->z = k * theta_inv;
	*theta *= 2;
}

inline void Quat::from_EulerXYZ(double thetax, double thetay, double thetaz)
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

inline void Quat::conjugate(Quat* q) 
{ 
	q->real = real; q->i = -i; q->j = -j; q->k = -k; 
}

inline Quat Quat::conjugate() 
{ 
	Quat q; q.real = real; q.i = -i; q.j = -j; q.k = -k; return q; 
}

inline double Quat::norm() 
{
	return sqrt(real * real + i * i + j * j + k * k); 
}

inline double Quat::norm2() 
{
	return (real * real + i * i + j * j + k * k); 
}

inline void Quat::normalize()
{
	auto norm_inv = 1.0 / this->norm();
	real *= norm_inv; i *= norm_inv; j *= norm_inv; k *= norm_inv;
}

inline void Quat::unit_inverse() 
{
	i = -i; j = -j; k = -k; 
}

inline void Quat::inverse()
{
	auto norm2_inv = 1.0 / this->norm2();
	real *= norm2_inv; i *= norm2_inv; j *= norm2_inv; k *= norm2_inv;
}

inline void Quat::scale(const double s) 
{ 
	real *= s; i *= s; j *= s; k *= s; 
}

inline void Quat::triple_product(const Quat& q1, const Quat& q2)
{
	*this *= q1; *this *= q2;
}

inline Quat& Quat::operator=(const Quat& q) 
{
	real = q.real; i = q.i; j = q.j; k = q.k; return *this; 
}

inline Quat Quat::operator+(const Quat& q)
{
	Quat tmp;
	tmp.real = real + q.real; tmp.i = i + q.i; tmp.j = j + q.j; tmp.k = k + q.k;
	return tmp;
}

inline Quat& Quat::operator+=(const Quat& q) 
{
	real += q.real; i += q.i; j += q.j; k += q.k; return *this; 
}

inline Quat Quat::operator-(const Quat& q)
{
	Quat tmp;
	tmp.real = real - q.real; tmp.i = i - q.i; tmp.j = j - q.j; tmp.k = k - q.k;
	return tmp;
}

inline Quat& Quat::operator-=(const Quat& q) 
{ 
	real -= q.real; i -= q.i; j -= q.j; k -= q.k; return *this; 
}

inline Quat& Quat::operator*(const double s) 
{
	*this *= s; return *this; 
}

inline Quat& Quat::operator*=(const double s) 
{
	real *= s; i *= s; j *= s; k *= s; return *this; 
}

inline Quat Quat::operator*(const Quat& q)
{
	Quat tmp;
	tmp.real = real * q.real - i * q.i - j * q.j - k * q.k;
	tmp.i = real * q.i + i * q.real + j * q.k - k * q.j;
	tmp.j = real * q.j - i * q.k + j * q.real - k * q.i;
	tmp.k = real * q.k + i * q.j - j * q.i + k * q.real;
	return tmp;
}

inline Quat& Quat::operator*=(const Quat& q)
{
	Quat tmp;
	tmp.real = real * q.real - i * q.i - j * q.j - k * q.k;
	tmp.i = real * q.i + i * q.real + j * q.k - k * q.j;
	tmp.j = real * q.j - i * q.k + j * q.real - k * q.i;
	tmp.k = real * q.k + i * q.j - j * q.i + k * q.real;
	*this = tmp;
	return *this;
}

#endif