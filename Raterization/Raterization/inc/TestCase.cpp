#include "TestCase.h"
#include <string>

std::ofstream TestLog("log/LMathlog.txt", std::ofstream::app);

#define UT_ASSERT(condition, output) if (condition) { \
	std::cout << output << std::endl; \
	TestLog << output << std::endl; \
}

void AutoTest()
{
	// AutoTest start
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::cout << "******* AutoTest start *******" << std::endl;
	TestLog << "******* AutoTest start : ";
	TestLog << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	TestLog << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	TestLog << " *******" << std::endl;

	// Test Cases
	VectorTest();
	MatrixTest();
	CoordinateTest();
	LineTest();

	// AutoTest end
	GetLocalTime(&time);
	std::cout << "*******  AutoTest end  *******" << std::endl;
	TestLog << "******* AutoTest start : ";
	TestLog << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	TestLog << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	TestLog << " *******" << std::endl;

	TestLog.close();
}

void VectorTest()
{
	// Vector2D unittest
	Vector2D v20;
	Vector2D v21(1.0, 1.0);
	Vector2D v22(v21);
	Vector2D v23 = v22;

	v20.init(0, 0);
	UT_ASSERT(v20.x != 0 || v20.y != 0, "Vector2D default constructor error.");
	UT_ASSERT(v21.x != 1 || v21.y != 1, "Vector2D assign constructor error.");
	UT_ASSERT(v22 != v21, "Vector2D constructor error.");
	UT_ASSERT(v23 != v21, "Vector2D operator= error.");
	v21.zero();
	UT_ASSERT(v21.x != 0 || v21.y != 0, "Vector2D zero() error.");
	v21.init(3, 4);
	UT_ASSERT(v21.length() < 4.99 || 5.01 < v21.length(), "Vector2D length() error.");
	v21.normalize();
	UT_ASSERT(v21.x < 0.599 || 0.601 < v21.x, "Vector2D normalize() error.");
	UT_ASSERT(v22.dot(&v21) < 1.399 || 1.401 < v22.dot(&v21), "Vector2D dot() error.");
	UT_ASSERT(v22.cos(&v23) < 0.99 || 1.01 < v22.cos(&v23), "Vector2D cos() error.");
	v22 = v22 + v23;
	UT_ASSERT(v22.x < 1.99 || 2.01 < v22.x  || v22.y < 1.99 || 2.01 < v22.y, "Vector2D operator+ error.");
	v22 += v23;
	UT_ASSERT(v22.x < 2.99 || 3.01 < v22.x || v22.y < 2.99 || 3.01 < v22.y, "Vector2D operator+= error.");
	v22 = v22 - v23;
	UT_ASSERT(v22.x < 1.99 || 2.01 < v22.x || v22.y < 1.99 || 2.01 < v22.y, "Vector2D operator- error.");
	v22 -= v23;
	UT_ASSERT(v22.x < 0.99 || 1.01 < v22.x || v22.y < 0.99 || 1.01 < v22.y, "Vector2D operator-= error.");
	v22 = v22 * 3;
	UT_ASSERT(v22.x < 2.99 || 3.01 < v22.x || v22.y < 2.99 || 3.01 < v22.y, "Vector2D operator* error.");
	v22 *= 3;
	UT_ASSERT(v22.x < 8.99 || 9.01 < v22.x || v22.y < 8.99 || 9.01 < v22.y, "Vector2D operator*= error.");

	// Vector3D test 
	Vector3D v30;
	Vector3D v31(1.0, 1.0, 1.0);
	Vector3D v32(v31);
	Vector3D v33 = v31;

	v30.init(0, 0, 0);
	UT_ASSERT(v30.x != 0 || v30.y != 0 || v30.z != 0, "Vector3D default constructor error.");
	UT_ASSERT(v31.x != 1 || v31.y != 1 || v31.z != 1, "Vector3D assign constructor error.");
	UT_ASSERT(v32 != v31, "Vector3D copy constructor error.");
	UT_ASSERT(v33 != v31, "Vector3D operator= error.");

	v31.zero();
	UT_ASSERT(v31.x != 0 || v31.y != 0 || v31.z != 0, "Vector3D zero() error.");
	v31.init(1.732, 1.732, 1.732);
	UT_ASSERT(v31.length() < 2.99 || 3.01 < v31.length(), "Vector3D length() error.");
	v31.normalize();
	UT_ASSERT(v31.x < 0.576 || 0.578 < v31.x, "Vector3D normalize() error.");
	UT_ASSERT(v31.dot(&v32) < 1.731 || 1.733 < v31.dot(&v32), "Vector3D dot() error.");
	UT_ASSERT(v31.cos(&v32) < 0.99 || 1.01 < v31.cos(&v32), "Vector3D cos() error.");
	v33 = v31.cross(&v32);
	UT_ASSERT(v33.x < -0.01 || 0.01 < v33.x, "Vector3D cross() error.");
	v31.init(1.0, 1.0, 1.0);
	v31 = v31 + v32;
	UT_ASSERT(v31.x < 1.99 || 2.01 < v31.x, "Vector3D operator+ error.");
	v31 += v32;
	UT_ASSERT(v31.x < 2.99 || 3.01 < v31.x, "Vector3D operator+= error.");
	v31 = v31 - v32;
	UT_ASSERT(v31.x < 1.99 || 2.01 < v31.x, "Vector3D operator- error.");
	v31 -= v32;
	UT_ASSERT(v31.x < 0.99 || 1.01 < v31.x, "Vector3D operator-= error.");
	v31 = v31 * 3;
	UT_ASSERT(v31.x < 2.99 || 3.01 < v31.x, "Vector3D operator* error.");
	v31 *= 3;
	UT_ASSERT(v31.x < 8.99 || 9.01 < v31.x, "Vector3D operator*= error.");

	// Vector4D test 
	Vector4D v40;
	Vector4D v41(1.0, 1.0, 1.0, 1.0);
	Vector4D v42(v41);
	Vector4D v43 = v41;

	v40.init(0, 0, 0);
	UT_ASSERT(v40.x != 0 || v40.y != 0 || v40.z != 0, "Vector4D default constructor error.");
	UT_ASSERT(v41.x != 1 || v41.y != 1 || v41.z != 1, "Vector4D assign constructor error.");
	UT_ASSERT(v42 != v41, "Vector4D copy constructor error.");
	UT_ASSERT(v43 != v41, "Vector4D operator= error.");

	v41.zero();
	UT_ASSERT(v41.x != 0 || v41.y != 0 || v41.z != 0, "Vector4D zero() error.");
	v41.init(1.742, 1.742, 1.742);
	UT_ASSERT(v41.length() < 2.99 || 4.01 < v41.length(), "Vector4D length() error.");
	v41.normalize();
	UT_ASSERT(v41.x < 0.576 || 0.578 < v41.x, "Vector4D normalize() error.");
	UT_ASSERT(v41.dot(&v42) < 1.731 || 1.733 < v41.dot(&v42), "Vector4D dot() error.");
	UT_ASSERT(v41.cos(&v42) < 0.99 || 1.01 < v41.cos(&v42), "Vector4D cos() error.");
	v43 = v41.cross(&v42);
	UT_ASSERT(v43.x < -0.01 || 0.01 < v43.x, "Vector4D cross() error.");
	v41.init(1.0, 1.0, 1.0);
	v41 = v41 + v42;
	UT_ASSERT(v41.x < 1.99 || 2.01 < v41.x, "Vector4D operator+ error.");
	v41 += v42;
	UT_ASSERT(v41.x < 2.99 || 4.01 < v41.x, "Vector4D operator+= error.");
	v41 = v41 - v42;
	UT_ASSERT(v41.x < 1.99 || 2.01 < v41.x, "Vector4D operator- error.");
	v41 -= v42;
	UT_ASSERT(v41.x < 0.99 || 1.01 < v41.x, "Vector4D operator-= error.");
	v41 = v41 * 3;
	UT_ASSERT(v41.x < 2.99 || 3.01 < v41.x, "Vector4D operator* error.");
	v41 *= 3;
	UT_ASSERT(v41.x < 8.99 || 9.01 < v41.x, "Vector4D operator*= error.");
}

void MatrixTest()
{
	// Matrix1x4 test 
	Matrix1x4 m140;
	Matrix1x4 m141(1.0, 1.0, 1.0, 1.0);
	Matrix1x4 m142(m141);
	Matrix1x4 m143 = m141;

	m140.init(1.0, 1.0, 1.0, 1.0);
	UT_ASSERT(m140.v[0] != 1.0, "Matrix1x4 default constructor error.");
	UT_ASSERT(m141.v[0] != 1.0, "Matrix1x4 assign constructor error.");
	UT_ASSERT(m142.v[0] != 1.0, "Matrix1x4 copy constructor error.");
	UT_ASSERT(m143.v[0] != 1.0, "Matrix1x4 operator= error.");
	m140.zero();
	UT_ASSERT(m140.v[0] != 0 || m140.v[1] != 0, "Matrix1x4 zero() error.");

	// Matrix4x3 test
	Matrix4x3 m430;
	Matrix4x3 m431(1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0);
	Matrix4x3 m432(m431);
	Matrix4x3 m433 = m431;

	m430.zero();
	UT_ASSERT(m430.v[0][0] != 0.0, "Matrix4x3 default constructor error.");
	UT_ASSERT(m431.v[0][0] != 1.0, "Matrix4x3 assign constructor erorr.");
	UT_ASSERT(m432.v[0][0] != 1.0, "Matrix4x3 copy constructor erorr.");
	UT_ASSERT(m433.v[0][0] != 1.0, "Matrix4x3 operator= erorr.");
	m430.init(2.0, 2.0, 2.0,
		2.0, 2.0, 2.0,
		2.0, 2.0, 2.0,
		2.0, 2.0, 2.0);
	UT_ASSERT(m430.v[0][0] != 2.0, "Matrix4x3 init() error.");
	m430.unit();
	UT_ASSERT(m430.v[0][0] != 1.0 || m430.v[1][0] != 0, "Matrix4x3 unit() error.");
	Vector3D tmp3D(1.0, 1.0, 1.0);
	tmp3D = m431.mul(&tmp3D);
	UT_ASSERT(tmp3D.x != 3.0 || tmp3D.y != 3.0, "Matrix4x3 mul() error.");
	Vector4D tmp4D;
	tmp4D.init(1.0, 1.0, 1.0);
	tmp4D = m431.mul(&tmp4D);
	UT_ASSERT(tmp4D.x != 4.0 || tmp4D.y != 4.0, "Matrix4x3 mul() error.");
	m430.swap(&m141, 0);
	UT_ASSERT(m430.v[1][0] != 1.0 || m430.v[2][0] != 1.0, "Matrix4x3 swap() error.");

	// Matrix4x4 test
	Matrix4x4 m440;
	Matrix4x4 m441(1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0);
	Matrix4x4 m442(m441);
	Matrix4x4 m443 = m441;

	m440.zero();
	UT_ASSERT(m440.v[0][0] != 0.0, "Matrix4x4 default constructor error.");
	UT_ASSERT(m441.v[0][0] != 1.0, "Matrix4x4 assign constructor erorr.");
	UT_ASSERT(m442.v[0][0] != 1.0, "Matrix4x4 copy constructor erorr.");
	UT_ASSERT(m443.v[0][0] != 1.0, "Matrix4x4 operator= erorr.");
	m440.init(2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0,
		2.0, 2.0, 2.0, 2.0);
	UT_ASSERT(m440.v[0][0] != 2.0, "Matrix4x4 init() error.");
	m440.unit();
	UT_ASSERT(m440.v[0][0] != 1.0 || m440.v[1][0] != 0, "Matrix4x4 unit() error.");
	m440.v[1][0] = 1.0;
	m440.transpose();
	UT_ASSERT(m440.v[0][1] != 1.0, "Matrix4x4 transpose() error.");
	m440.swap(&m141, 0);
	UT_ASSERT(m440.v[1][0] != 1.0 || m440.v[2][0] != 1.0, "Matrix4x3 swap() error.");
	Matrix1x4 tmp14;
	tmp14.init(1.0, 1.0, 1.0, 1.0);
	tmp14 = m442.mul(&tmp14);
	UT_ASSERT(tmp14.v[0] != 4.0 || tmp14.v[1] != 4.0, "Matrix4x4 mul() error.");
	tmp3D.init(1.0, 1.0, 1.0);
	tmp3D = m441.mul(&tmp3D);
	UT_ASSERT(tmp3D.x != 3.0 || tmp3D.y != 3.0, "Matrix4x4 mul() error.");
	tmp4D.init(1.0, 1.0, 1.0);
	m441 = m443; m441.v[1][1] = 2; m441.v[2][2] = 3;
	UT_ASSERT(m441.simple_det() != 2.0, "Matrix4x4 simple_det() error.");
	m441 = m441.inverse();
	UT_ASSERT(m441.v[0][0] < 2.499 || 2.501 < m441.v[1][1], "Matrix4x4 inverse() error.");
	tmp4D = m442.mul(&tmp4D);
	UT_ASSERT(tmp4D.x != 4.0 || tmp4D.y != 4.0, "Matrix4x4 mul() error.");
	m442 = m442 + m443;
	UT_ASSERT(m442.v[0][0] != 2.0 || m442.v[0][1] != 2.0, "Matrix4x4 operator+ error.");
	m442 += m443;
	UT_ASSERT(m442.v[0][0] != 3.0 || m442.v[0][1] != 3.0, "Matrix4x4 operator+= error.");
	m442 = m442 * m443;
	UT_ASSERT(m442.v[0][0] != 12.0 || m442.v[0][1] != 12.0, "Matrix4x4 operator* error.");
	m442 *= m443;
	UT_ASSERT(m442.v[0][0] != 48.0 || m442.v[0][1] != 48.0, "Matrix4x4 operator*= error.");

	// Matrix1x3 test
	Matrix1x3 m130;
	Matrix1x3 m131(1.0, 1.0, 1.0);
	Matrix1x3 m132(m131);
	Matrix1x3 m133 = m131;

	m130.init(1.0, 1.0, 1.0);
	UT_ASSERT(m130.v[0] != 1.0, "Matrix1x3 default constructor error.");
	UT_ASSERT(m131.v[0] != 1.0, "Matrix1x3 assign constructor error.");
	UT_ASSERT(m132.v[0] != 1.0, "Matrix1x3 copy constructor error.");
	UT_ASSERT(m133.v[0] != 1.0, "Matrix1x3 operator= error.");
	m130.zero();
	UT_ASSERT(m130.v[0] != 0 || m130.v[1] != 0, "Matrix1x3 zero() error.");

	// Matrix3x2 test
	Matrix3x2 m320;
	Matrix3x2 m321(1.0, 1.0, 1.0,
		1.0, 1.0, 1.0);
	Matrix3x2 m322(m321);
	Matrix3x2 m323 = m321;

	m320.init(1.0, 1.0, 1.0,
		1.0, 1.0, 1.0);
	UT_ASSERT(m320.v[0][0] != 1.0, "Matrix3x2 default constructor error.");
	UT_ASSERT(m321.v[0][0] != 1.0, "Matrix3x2 assign constructor error.");
	UT_ASSERT(m322.v[0][0] != 1.0, "Matrix3x2 copy constructor error.");
	UT_ASSERT(m323.v[0][0] != 1.0, "Matrix3x2 operator= error.");
	m320.zero();
	UT_ASSERT(m320.v[0][0] != 0 || m320.v[1][0] != 0, "Matrix3x2 zero() error.");

	// Matrix3x3 test
	Matrix3x3 m330;
	Matrix3x3 m331(1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0);
	Matrix3x3 m332(m331);
	Matrix3x3 m333 = m331;

	m330.init(1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0);
	UT_ASSERT(m330.v[0][0] != 1.0, "Matrix3x3 default constructor error.");
	UT_ASSERT(m331.v[0][0] != 1.0, "Matrix3x3 assign constructor error.");
	UT_ASSERT(m332.v[0][0] != 1.0, "Matrix3x3 copy constructor error.");
	UT_ASSERT(m333.v[0][0] != 1.0, "Matrix3x3 operator= error.");
	m330.zero();
	UT_ASSERT(m330.v[0][0] != 0.0, "Matrix3x3 zero() error.");
	m330.unit();
	UT_ASSERT(m330.v[0][0] != 1.0 || m330.v[1][1] != 1.0, "Matrix3x3 unit() error.");
	m330.v[0][1] = 2.0;
	m330.transpose();
	UT_ASSERT(m330.v[1][0] != 2.0, "Matrix3x3 transpose() error.");
	m330.swap(&m131, 0);
	UT_ASSERT(m330.v[1][0] != 1.0 || m330.v[2][0] != 1.0, "Matrix3x3 swap() error.");
	m331.v[1][1] = 2.0; m331.v[2][2] = 3.0;
	UT_ASSERT(m331.det() != 2.0, "Matrix3x3 det() error.");
	m331 = m331.inverse();
	UT_ASSERT(m331.v[0][0] < 2.499 || 2.501 < m331.v[0][0], "Matrix3x3 inverse() error.");
	m332 = m332 + m333;
	UT_ASSERT(m332.v[0][0] != 2.0, "Matrix3x3 operator+ error.");
	m332 += m333;
	UT_ASSERT(m332.v[0][0] != 3.0, "Matrix3x3 operator+= error.");
	m332 *= m333;
	UT_ASSERT(m332.v[0][0] < 8.99 || 9.01 < m332.v[0][0], m332.v[0][0]);
	m332 *= m333;
	UT_ASSERT(m332.v[0][0] < 26.99 || 27.01 < m332.v[0][0], "Matrix3x3 operator*= error.");

	// Matrix1x2 test
	Matrix1x2 m120;
	Matrix1x2 m121(1.0, 1.0);
	Matrix1x2 m122(m121);
	Matrix1x2 m123 = m121;

	m120.init(1.0, 1.0);
	UT_ASSERT(m120.v[0] != 1.0, "Matrix1x2 default constructor error.");
	UT_ASSERT(m121.v[0] != 1.0, "Matrix1x2 assign constructor error.");
	UT_ASSERT(m122.v[0] != 1.0, "Matrix1x2 copy constructor error.");
	UT_ASSERT(m123.v[0] != 1.0, "Matrix1x2 operator= error.");
	m120.zero();
	UT_ASSERT(m120.v[0] != 0 || m120.v[1] != 0, "Matrix1x2 zero() error.");

	// Matrix2x2 test
	Matrix2x2 m220;
	Matrix2x2 m221(1.0, 1.0, 1.0, 1.0);
	Matrix2x2 m222(m221);
	Matrix2x2 m223 = m221;

	m220.init(1.0, 1.0, 1.0, 1.0);
	UT_ASSERT(m220.v[0][0] != 1.0, "Matrix2x2 default constructor error.");
	UT_ASSERT(m221.v[0][0] != 1.0, "Matrix2x2 assign constructor error.");
	UT_ASSERT(m222.v[0][0] != 1.0, "Matrix2x2 copy constructor error.");
	UT_ASSERT(m223.v[0][0] != 1.0, "Matrix2x2 operator= error.");
	m220.zero();
	UT_ASSERT(m220.v[0][0] != 0 || m220.v[1][1] != 0, "Matrix2x2 zero() error.");
	m220.v[0][1] = 1.0; m220.v[1][0] = 2.0;
	m220.transpose();
	UT_ASSERT(m220.v[0][1] != 2.0 || m220.v[1][0] != 1.0, "Matrix2x2 transpose() error.");
	m220.swap(&m121, 0);
	UT_ASSERT(m220.v[0][0] != 1.0 || m220.v[1][0] != 1.0, "Matrix2x2 swap() error.");
	UT_ASSERT(m220.det() != -2.0, "Matrix2x2 det() error.");
	m220.zero(); m220.v[0][0] = 2.0; m220.v[1][1] = 2.0;
	m220 = m220.inverse();
	UT_ASSERT(m220.v[0][0] < 0.499 || 0.501 < m220.v[1][1], "Matrix2x2 inverse() error.");
	m221 = m221 + m222;
	UT_ASSERT(m221.v[0][0] != 2.0, "Matrix2x2 operator+ error.");
	m221 += m222; 
	UT_ASSERT(m221.v[0][0] != 3.0, "Matrix2x2 operator+= error.");
	m221 = m221 - m222;
	UT_ASSERT(m221.v[0][0] != 2.0, "Matrix2x2 operator- error.");
	m221 -= m222;
	UT_ASSERT(m221.v[0][0] != 1.0, "Matrix2x2 operator-= error.");
	m221 = m221 * m222;
	UT_ASSERT(m221.v[0][0] != 2.0, "Matrix2x2 operator* error.");
	m221 *= m222;
	UT_ASSERT(m221.v[0][0] != 4.0, "Matrix2x2 operator*= error.");
}

void CoordinateTest()
{
	// Polar2D test
	Polar2D polar0;
	Polar2D polar1(2.0, PI_DIV_4);
	Polar2D polar2(polar1);
	
	polar0.init(2.0, PI_DIV_4);
	UT_ASSERT(polar0.r != 2.0 || polar0.theta != PI_DIV_4, "Polar2D default constructor error.");
	UT_ASSERT(polar1.r != 2.0 || polar1.theta != PI_DIV_4, "Polar2D assign constructor error.");
	UT_ASSERT(polar2.r != 2.0 || polar2.theta != PI_DIV_4, "Polar2D copy constructor error.");
	Point2D tmp2D = polar0.toPoint2D();
	UT_ASSERT(tmp2D.x < 1.413 || 1.415 < tmp2D.x, "Polar2D toPoint() error.");
	polar0.init(&tmp2D);
	UT_ASSERT(polar0.r != 2.0 || polar0.theta != PI_DIV_4, "Polar2D init() error.");
	double tmpx, tmpy;
	polar0.toXY(&tmpx, &tmpy);
	UT_ASSERT(tmpx < 1.413 || 1.415 < tmpx, "Polar2D toXY() error.");
	polar0.init(0, PI);
	polar0 = polar2;
	UT_ASSERT(polar0.r != 2.0 || polar0.theta != PI_DIV_4, "Polar2D operator= error.");

	// Cylindrical3D test
	Cylindrical3D cy0;
	Cylindrical3D cy1(2.0, PI_DIV_4, 2.0);
	Cylindrical3D cy2(cy1);

	cy0.init(2.0, PI_DIV_4, 2.0);
	UT_ASSERT(cy0.r != 2.0 || cy0.z != 2.0, "Cylindrical3D default constructor error.");
	UT_ASSERT(cy1.r != 2.0 || cy1.z != 2.0, "Cylindrical3D assign constructor error.");
	UT_ASSERT(cy2.r != 2.0 || cy2.z != 2.0, "Cylindrical3D copy constructor error.");
	Point3D tmp3D = cy0.toPoint3D();
	UT_ASSERT(tmp3D.x < 1.413 || 1.415 < tmp3D.x || tmp3D.z != 2.0, "Cylindrical3D toPoint() error.");
	cy0.init(&tmp3D);
	UT_ASSERT(cy0.r != 2.0 || cy0.z != 2.0, "Cylindrical3D init() error.");
	double tmpz;
	cy0.toXYZ(&tmpx, &tmpy, &tmpz);
	UT_ASSERT(tmpx < 1.413 || 1.415 < tmpx || tmpz != 2.0, "Cylindrical3D toXYZ() error.");
	cy0.init(0.0, PI, 0.0);
	cy0 = cy1;
	UT_ASSERT(cy0.r != 2.0 || cy0.z != 2.0, "Cylindrical3D operator= error.");
	
	// Spherical3D test
	Spherical3D sp0;
	Spherical3D sp1(2.0, PI_DIV_4, PI_DIV_4);
	Spherical3D sp2(sp1);

	sp0.init(2.0, PI_DIV_4, PI_DIV_4);
	UT_ASSERT(sp0.pos != 2.0 || sp0.theta != PI_DIV_4, "Spherical3D default constructor error.");
	UT_ASSERT(sp1.pos != 2.0 || sp1.theta != PI_DIV_4, "Spherical3D assign constructor error.");
	UT_ASSERT(sp2.pos != 2.0 || sp2.theta != PI_DIV_4, "Spherical3D copy constructor error.");
	tmp3D = sp0.toPoint3D();
	UT_ASSERT(tmp3D.x < 0.99 || 1.01 < tmp3D.x, "Spherical3D toPoint() error.");
	sp0.init(&tmp3D);
	UT_ASSERT(sp0.pos < 1.99 || 2.01 < sp0.pos, "Spherical3D init() error.");
	sp0.toXYZ(&tmpx, &tmpy, &tmpz);
	UT_ASSERT(tmpx < 0.99 || 1.01 < tmpx, "Spherical3D toXYZ() error.");
	sp0.init(0.0, PI, PI);
	sp0 = sp1;
	UT_ASSERT(sp0.pos != 2.0 || sp0.theta != PI_DIV_4, "Spherical3D operator= error.");
}

void LineTest()
{
	// Line2D test
	Point2D pbegin1, pbegin2, pend1, pend2;
	pbegin1.init(0.0, 0.0); pend1.init(2.0, 2.0);
	pbegin2.init(0.0, 2.0); pend2.init(2.0, 0.0);

	Line2D line1;
	Line2D line2(pbegin2, pend2, pend2 - pbegin2);
	line1.init(pbegin1, pend1, pend1 - pbegin1);

	UT_ASSERT(line1.p0.x != 0.0 || line1.p1.x != 2.0, "Line2D default contructor error.");
	UT_ASSERT(line2.p0.x != 0.0 || line2.p1.x != 2.0, "Line2D assign constructor error.");
	Point2D tmp2D = line1.compute(0.5);
	UT_ASSERT(tmp2D.x != 1.0 || tmp2D.y != 1.0, "Line2D compute() error.");
	UT_ASSERT(line1.intersect(&line2, &tmp2D) != LINE_INTERSECT_IN_SEGMENT, "Line2D intersect() error.");
	UT_ASSERT(tmp2D.x != 1.0 || tmp2D.y != 1.0, "Line2D intersect() error.");

	// Line3D test
	Point3D pbegin3, pbegin4, pend3, pend4;
	pbegin3.init(0.0, 0.0, 0.0); pend3.init(2.0, 2.0, 2.0);
	pbegin4.init(0.0, 0.0, 2.0); pend4.init(2.0, 2.0, 0.0);
	Line3D line3;
	Line3D line4(pbegin4, pend4, pend4 - pbegin4);
	line3.init(pbegin3, pend3, pend3 - pbegin3);

	UT_ASSERT(line3.p0.x != 0.0 || line3.p1.x != 2.0, "Line3D default constructor error.");
	UT_ASSERT(line4.p0.x != 0.0 || line4.p1.x != 2.0, "Line3D assign constructor error.");
	Point3D tmp3D = line3.compute(0.5);
	UT_ASSERT(tmp3D.x != 1.0 || tmp3D.y != 1.0, "Line3D compute() error.");
}

