#include "stdafx.h"
std::ofstream RunLog("log/Runlog.txt", std::ofstream::app);

#define RUN_ASSERT(condition, output) if (condition) { \
	std::cout << output << std::endl; \
	RunLog << output << std::endl; \
}

#define UNITTEST_MODE

extern double sin_table[361];
extern double cos_table[361];

#ifndef UNITTEST_MODE
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LWindow win;

	win.Create(480, 480, hInstance);
	win.MsgLoop();

	return 0;
}

#else

int main()
{
	//AutoTest();

	double scale = 1.0;
	PVector4D pos = new Vector4D(0, 0, 0, 1);
	PVector4D rot = new Vector4D(0, 0, 0, 1);
	std::string path = "load/test.txt";
	PObject4DV1 obj;
	obj = (PObject4DV1)malloc(sizeof(Object4DV1));

	Load_Object4DV1_PLG(obj, path, scale, pos, rot);

	return 0;
}

#endif

