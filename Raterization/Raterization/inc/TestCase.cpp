#include "TestCase.h"
#include <string>

std::ofstream TestLog("log/LMathlog.txt", std::ofstream::app);

#define LMATH_Debug(judge, output) if (judge) { \
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
	TestLog << " *******\n";

	// Test Cases
	VectorTest();
	//MatrixTest(testlog);

	// AutoTest end
	GetLocalTime(&time);
	std::cout << "*******  AutoTest end  *******" << std::endl;
	TestLog << "******* AutoTest start : ";
	TestLog << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	TestLog << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	TestLog << " *******\n";

	TestLog.close();
}

void VectorTest()
{
	// Vector2 test : 4
	Vector2 v20;
	Vector2 v21(1.0, 1.0);
	Vector2 v22(v21);
	Vector2 v23 = v22;

	v20.Zero();
	LMATH_Debug(v20.x != 0 || v20.y != 0, "Vector2 default constructor error.\n");
	LMATH_Debug(v21.x != 1 || v21.y != 1, "Vector2 assign constructor error.\n");
	LMATH_Debug(v22 != v21, "Vector2 constructor error.");
	LMATH_Debug(v23 != v21, "Vector2 operator= error.");
	v21.x = 3; v21.y = 4;
	LMATH_Debug(v21.Length() < 4.98, "Vector2 Length() error.\n");
	v21.Normalize();
	LMATH_Debug(v21.x < 0.598, "Vector2 Normalize() error.\n");
	LMATH_Debug(v22.Dot(&v21) < 1.398, "Vector2 Dot() error.\n");
	LMATH_Debug(v22.Cos(&v23) < 0.98, "Vector2 Cos() error.\n");
	v22 = v22 + v23;
	LMATH_Debug(v22.x < 1.98 || v22.y < 1.98, "Vector2 operator+/+= error.\n");
	v22 = v22 - v23;
	LMATH_Debug(v22.x < 0.98 || v22.y < 0.98, "Vector2 operator-/-= error.\n");
	v22 = v22 * 3;
	LMATH_Debug(v22.x < 2.98 || v22.y < 2.98, "Vector2 operator*/*= error.\n");
}

	
	// Vector3 test : 4
	/*Vector3 v31(1.0, 1.0, 1.0);
	Vector3 v32(v31);
	Vector3 v33 = v31;
	
	if (v31.x != 1 || v32.y != 1 || v32.z != 1)
	{
		std::cout << "Vector3 constructor error." << std::endl;
		log << "Vector3 constructor error." << std::endl;
		err++;
	}

	if (v32 != v31)
	{
		std::cout << "Vector3 copy constructor error." << std::endl;
		log << "Vector3 copy constructor error." << std::endl;
		err++;
	}

	if (v33 != v31)
	{
		std::cout << "Vector3 operator= error." << std::endl;
		log << "Vector3 operator= error." << std::endl;
		err++;
		
	}

	v31.Zero();
	if (v31.x != 0 || v31.y != 0 || v31.z != 0)
	{
		std::cout << "Vector3 Zero error." << std::endl;
		log << "Vector3 Zero error." << std::endl;
		err++;
	}

	// Vector4 test : 4
	Vector4 v41(1.0, 1.0, 1.0, 1.0);
	Vector4 v42(v41);
	Vector4 v43 = v41;

	if (v41.x != 1 || v41.y != 1 || v41.z != 1 || v41.w != 1)
	{
		std::cout << "Vector4 constructor error." << std::endl;
		log << "Vector4 constructor error." << std::endl;
		err++;
	}

	if (v42 != v41)
	{
		std::cout << "Vector4 copy constructor error." << std::endl;
		log << "Vector4 copy constructor error." << std::endl;
		err++;
	}

	if (v43 != v41)
	{
		std::cout << "Vector4 operator= error." << std::endl;
		log << "Vector4 operator= error." << std::endl;
		err++;
	}

	v41.Zero();
	if (v41.x != 0 || v41.y != 0 || v41.z != 0 || v41.w != 1)
	{
		std::cout << "Vector4 Zero error." << std::endl;
		log << "Vector4 Zero error." << std::endl;
		err++;
	}

	auto p1 = new Point2D(0.0, 0.0);
	auto p2 = new Point2D(1.0, 1.0);
	auto v2 = Vector2(2.0, 2.0);
	Vector2 v1;
	v1 = Vector2(p1, p2);
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
	log << " | Error : " << err << "(" << (float)err * 100 / total << "%)\n";
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
