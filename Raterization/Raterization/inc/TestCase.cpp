#include "TestCase.h"

void AutoTest()
{
	std::ofstream testlog("log/TestLog.txt", std::ofstream::app);
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
	VectorTest(testlog);


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
	int total, err;
	Vector2 v21(0.0, 0.0);
	Vector2 v22 = v21;
	Vector2 v23, v24;

	Vector3 v31(0.0, 0.0, 0.0);
	Vector3 v32 = v31;
	Vector3 v33, v34;

	Vector4 v41(0.0, 0.0, 0.0, 1.0);
	Vector4 v42 = v41;
	Vector4 v43, v44;

	total = 12;
	err = 0;

	v23.Zero();
	v24.x = v24.y = 1.0;
	v33.Zero();
	v34.x = v34.y = v34.z = 1.0;
	v43.Zero();
	v44.x = v44.y = v44.z = v44.w = 1.0;

	// Vector2 test : 4
	if (v21.x != 0 || v22.y != 0)
	{
		std::cout << "Vector2 constructor error." << std::endl;
		log << "Vector2 constructor error." << std::endl;
		err++;
	}

	//if (v22.x != 0 || v22.y != 0)
	if (v22 != v21)
	{
		std::cout << "Vector2 operator= error." << std::endl;
		log << "Vector2 operator= error." << std::endl;
		err++;
	}

	if (v23.x != 0 || v23.y != 0)
	{
		std::cout << "Vector2 Zero error." << std::endl;
		log << "Vector2 Zero error." << std::endl;
		err++;
	}

	if (v24.x != 1 || v24.y != 1)
	{
		std::cout << "Vector2 element assign error." << std::endl;
		log << "Vector2 element assign error." << std::endl;
		err++;
	}

	// Vector3 test : 4
	if (v31.x != 0 || v32.y != 0 || v32.z != 0)
	{
		std::cout << "Vector3 constructor error." << std::endl;
		log << "Vector3 constructor error." << std::endl;
		err++;
	}

	//if (v32.x != 0 || v32.y != 0 || v32.z != 0)
	if (v32 != v31)
	{
		std::cout << "Vector3 operator= error." << std::endl;
		log << "Vector3 operator= error." << std::endl;
		err++;
	}

	if (v33.x != 0 || v33.y != 0 || v33.z != 0)
	{
		std::cout << "Vector3 Zero error." << std::endl;
		log << "Vector3 Zero error." << std::endl;
		err++;
	}

	if (v34.x != 1 || v34.y != 1 || v34.z != 1)
	{
		std::cout << "Vector3 element assign error." << std::endl;
		log << "Vector3 element assign error." << std::endl;
		err++;
	}

	// Vector4 test : 4
	if (v41.x != 0 || v41.y != 0 || v41.z != 0 || v41.w != 1)
	{
		std::cout << "Vector4 constructor error." << std::endl;
		log << "Vector4 constructor error." << std::endl;
		err++;
	}

	//if (v42.x != 0 || v42.y != 0 || v42.z != 0 || v42.w != 1)
	if (v42 != v41)
	{
		std::cout << "Vector4 operator= error." << std::endl;
		log << "Vector4 operator= error." << std::endl;
		err++;
	}

	if (v43.x != 0 || v43.y != 0 || v43.z != 0 || v44.w != 1)
	{
		std::cout << "Vector4 Zero error." << std::endl;
		log << "Vector4 Zero error." << std::endl;
		err++;
	}

	if (v44.x != 1 || v44.y != 1 || v44.z != 1 || v44.w != 1)
	{
		std::cout << "Vector4 element assign error." << std::endl;
		log << "Vector4 element assign error." << std::endl;
		err++;
	}

	std::cout << "VectorTest => Total : " << total;
	std::cout << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	std::cout << " | Error : " << err << "(" << (float)err * 100 / total << "%)" << std::endl;

	log << "VectorTest => Total : " << total;
	log << " | Pass : " << std::setprecision(4) << total - err << "(" << (float)(total - err) * 100 / total << "%)";
	log << " | Error : " << err << "(" << (float)err * 100 / total << "%)" << std::endl;
}
