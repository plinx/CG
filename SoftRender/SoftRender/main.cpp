#include "stdafx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LWindow win;

	win.Create(480, 480, hInstance);
	win.MsgLoop();

	return 0;
}