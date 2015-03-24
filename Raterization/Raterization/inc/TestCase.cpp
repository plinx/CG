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
	//MatrixTest(testlog);

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
	UT_ASSERT(v21.length() < 4.98 || 5.01 < v21.length(), "Vector2D Length() error.");
	v21.normalize();
	UT_ASSERT(v21.x < 0.598 || 0.601 < v21.x, "Vector2D Normalize() error.");
	UT_ASSERT(v22.dot(&v21) < 1.398 || 1.401 < v22.dot(&v21), "Vector2D Dot() error.");
	UT_ASSERT(v22.cos(&v23) < 0.98 || 1.01 < v22.cos(&v23), "Vector2D Cos() error.");
	v22 = v22 + v23;
	UT_ASSERT(v22.x < 1.98 || 2.01 < v22.x  || v22.y < 1.98 || 2.01 < v22.y, "Vector2D operator+ error.");
	v22 += v23;
	UT_ASSERT(v22.x < 2.98 || 3.01 < v22.x || v22.y < 2.98 || 3.01 < v22.y, "Vector2D operator+= error.");
	v22 = v22 - v23;
	UT_ASSERT(v22.x < 1.98 || 2.01 < v22.x || v22.y < 1.98 || 2.01 < v22.y, "Vector2D operator- error.");
	v22 -= v23;
	UT_ASSERT(v22.x < 0.98 || 1.01 < v22.x || v22.y < 0.98 || 1.01 < v22.y, "Vector2D operator-= error.");
	v22 = v22 * 3;
	UT_ASSERT(v22.x < 2.98 || 3.01 < v22.x || v22.y < 2.98 || 3.01 < v22.y, "Vector2D operator* error.");
	v22 *= 3;
	UT_ASSERT(v22.x < 8.98 || 9.01 < v22.x || v22.y < 8.98 || 9.01 < v22.y, "Vector2D operator*= error.");

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
	UT_ASSERT(v31.length() < 2.98 || 3.01 < v31.length(), "Vector3D length() error.");

}

	/*
	// Vector4D test : 4
	Vector4D v41(1.0, 1.0, 1.0, 1.0);
	Vector4D v42(v41);
	Vector4D v43 = v41;

	if (v41.x != 1 || v41.y != 1 || v41.z != 1 || v41.w != 1)
	{
		std::cout << "Vector4D constructor error." << std::endl;
		log << "Vector4D constructor error." << std::endl;
		err++;
	}

	if (v42 != v41)
	{
		std::cout << "Vector4D copy constructor error." << std::endl;
		log << "Vector4D copy constructor error." << std::endl;
		err++;
	}

	if (v43 != v41)
	{
		std::cout << "Vector4D operator= error." << std::endl;
		log << "Vector4D operator= error." << std::endl;
		err++;
	}

	v41.Zero();
	if (v41.x != 0 || v41.y != 0 || v41.z != 0 || v41.w != 1)
	{
		std::cout << "Vector4D Zero error." << std::endl;
		log << "Vector4D Zero error." << std::endl;
		err++;
	}

	auto p1 = new Point2D(0.0, 0.0);
	auto p2 = new Point2D(1.0, 1.0);
	auto v2 = Vector2D(2.0, 2.0);
	Vector2D v1;
	v1 = Vector2D(p1, p2);
	std::cout << v1.x << " " << v1.x << std::endl;
	v1.Normalize();
	std::cout << v1.x << " " << v1.x << std::endl;
	v1 = v2;
	std::cout << v1.x << " " << v1.x << std::endl;
	v1 = v1 + v2;
	std::cout << v1.x << " " << v1.x << std::endl;
	v1 += v2;
	std::cout << v1.x << " " << v1.x << std::endl;
	v1 -= v2;
	std::cout << v1.x << " " << v1.x << std::endl;
	v1 *= 2.0;
	std::cout << v1.x << " " << v1.x << std::endl;
	std::cout << v1.Dot(&v2) << std::endl;
	std::cout << v1.Cos(&v2) << std::endl;
	

	log << "VectorTest => Total : " << total;
	log << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	log << " | Error : " << err << "(" << (float)err * 100 / total << "%)";
}

void MatrixTest(std::ofstream& log)
{
	int total = 7, err = 0;

	// Matrix1x4 test : 2
	Matrix1x4 M14;
	M14.Zero();
	Matrix1x4 M14c(M14);
	Matrix1x4 M14e = M14;

	if (M14c.v[0] != 0 || M14c.v[1] != 0 || M14c.v[2] != 0 || M14c.v[3] != 0)
	{
		std::cout << "Matrix1x4 copy constructor error." << std::endl;
		log << "Matrix1x4 copy constructor error." << std::endl;
		err++;
	}

	if (M14e.v[0] != 0 || M14e.v[1] != 0 || M14e.v[2] != 0 || M14e.v[3] != 0)
	{
		std::cout << "Matrix1x4 operator= error." << std::endl;
		log << "Matrix1x4 operator= error." << std::endl;
		err++;
	}

	// Matrix4x3 test : 4
	Matrix4x3 M43;
	M43.Init();
	Matrix4x3 M43c(M43);
	Matrix4x3 M43e = M43;

	if (M43c.v[0][0] != 1 || M43c.v[1][1] != 1 || M43c.v[2][2] != 1 || M43c.v[3][2] != 0)
	{
		std::cout << "Matrix4x3 copy constructor error." << std::endl;
		log << "Matrix4x3 copy constructor error." << std::endl;
		err++;
	}

	if (M43e.v[0][0] != 1 || M43e.v[1][1] != 1 || M43e.v[2][2] != 1 || M43e.v[3][2] != 0)
	{
		std::cout << "Matrix4x3 operator= error." << std::endl;
		log << "Matrix4x3 operator= error." << std::endl;
		err++;
	}

	M14.v[0] = 1; M14.v[1] = 1; M14.v[2] = 1; M14.v[3] = 1;
	M43.Swap(&M14, 2);
	if (M43.v[0][2] != 1 || M43.v[1][2] != 1 || M43.v[2][2] != 1 || M43.v[3][2] != 1)
	{
		std::cout << "Matrix4x3 Swap() error." << std::endl;
		log << "Matrix4x3 Swap() error." << std::endl;
		err++;
	}

	M43.Zero();
	if (M43.v[0][2] != 0 || M43.v[1][2] != 0 || M43.v[2][2] != 0 || M43.v[3][2] != 0)
	{
		std::cout << "Matrix4x3 Zero() error." << std::endl;
		log << "Matrix4x3 Zero() error." << std::endl;
		err++;
	}

	// Matrix4x4 test : 1
	Matrix4x4 M44;
	M44.Init();
	M44.Swap(&M14, 2);
	M44.Transpose();
	if (M44.v[2][0] != 1 || M44.v[2][1] != 1 || M44.v[2][2] != 1 || M44.v[2][3] != 1)
	{
		std::cout << "Matrix4x4 Transpose() error." << std::endl;
		log << "Matrix4x4 Transpose() error." << std::endl;
		err++;
	}

	// Other size Matrix test ...
	// ...

	std::cout << "MatrixTest => Total : " << total;
	std::cout << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	std::cout << " | Error : " << err << "(" << (float)err * 100 / total << "%)" << std::endl;

	log << "MatrixTest => Total : " << total;
	log << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	log << " | Error : " << err << "(" << (float)err * 100 / total << "%)" << std::endl;
}*/
