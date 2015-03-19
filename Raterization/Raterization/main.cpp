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

	return 0;
}

#endif

