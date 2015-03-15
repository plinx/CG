#include "stdafx.h"

#define MATHTEST_MODE

extern double sin_table[361];
extern double cos_table[361];

#ifndef MATHTEST_MODE
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

	double x, y, z, zz;
	x = 5.0f;
	y = 1.0 / x;
	z = zz = 3;
	z *= y;
	zz /= x;
	std::cout.precision(25);
	std::cout << z << " " << zz << std::endl;
	if (z == zz)
		std::cout << "equal" << std::endl;
	else
		std::cout << "non-equal" << std::endl;

	return 0;
}

#endif

