#include "stdafx.h"
#include "Demos.h"

//extern double sin_table[361];
//extern double cos_table[361];

//#define UNITTEST_MODE 
#undef UNITTEST_MODE 

#ifndef UNITTEST_MODE
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LWindow win;

	win.Create(480, 480, hInstance);
	win.Render();

	return 0;
}

#else

int main()
{
	//AutoTest();
	//TriangleDemo();
	//CubeDemo1();
	//CubeDemo2();
	TankDemo1();

	system("pause");

	return 0;
}

#endif

