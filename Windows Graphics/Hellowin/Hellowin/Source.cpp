#include "lwin.h"

int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR AppName[] = TEXT("HelloWin");
	LWindow win;

	win.InitWindow(AppName, 640, 480, hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}
