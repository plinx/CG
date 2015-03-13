#include "TestCase.h"

void AutoTest()
{
	std::ofstream testlog("log/TestLog.txt", std::ofstream::app);

	// AutoTest start
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::cout << "******* AutoTest start : ";
	std::cout << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	std::cout << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	std::cout << " *******" << std::endl;

	testlog << "******* AutoTest start : ";
	testlog << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	testlog << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	testlog << " *******" << std::endl;

	// Test Cases
	VectorTest(testlog);
	MatrixTest(testlog);

	// AutoTest end
	GetLocalTime(&time);
	std::cout << "******* AutoTest end   : ";
	std::cout << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	std::cout << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	std::cout << " *******" << std::endl;

	testlog << "******* AutoTest end   : ";
	testlog << time.wYear << "/" << time.wMonth << "/" << time.wDay << " ";
	testlog << time.wHour << ":" << time.wMinute << ":" << time.wSecond;
	testlog << " *******" << std::endl;

}

void VectorTest(std::ofstream& log)
{
	int total = 12, err = 0;

	// Vector2 test : 4
	Vector2 v21(1.0, 1.0);
	Vector2 v22(v21);
	Vector2 v23 = v21;

	if (v21.x != 1 || v21.y != 1)
	{
		std::cout << "Vector2 constructor error." << std::endl;
		log << "Vector2 constructor error." << std::endl;
		err++;
	}

	if (v22 != v21)
	{
		std::cout << "Vector2 constructor error." << std::endl;
		log << "Vector2 constructor error." << std::endl;
		err++;
	}

	if (v23 != v21)
	{
		std::cout << "Vector2 operator= error." << std::endl;
		log << "Vector2 operator= error." << std::endl;
		err++;
	}

	v21.Zero();
	if (v21.x != 0 || v21.y != 0)
	{
		std::cout << "Vector2 Zero() error." << std::endl;
		log << "Vector2 Zero() error." << std::endl;
		err++;
	}
	
	// Vector3 test : 4
	Vector3 v31(1.0, 1.0, 1.0);
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

	std::cout << "VectorTest => Total : " << total;
	std::cout << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	std::cout << " | Error : " << err << "(" << (float)err * 100 / total << "%)" << std::endl;

	log << "VectorTest => Total : " << total;
	log << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	log << " | Error : " << err << "(" << (float)err * 100 / total << "%)" << std::endl;
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
}
