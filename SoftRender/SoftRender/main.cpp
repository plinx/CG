#include "basewin.h"

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	PSTR szCmdLine, 
	int iCmdShow)
{
	WinApp app;
	app.Create(640, 480);
	app.Init(hInstance, iCmdShow);

	return 0;
}
