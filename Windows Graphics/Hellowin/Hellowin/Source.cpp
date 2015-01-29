#include "lwin.h"

class HelloWindow : public LWindow
{
	void OnDraw(HDC hdc)
	{
		static TCHAR szHint[] = TEXT("Press ESC to quit.");
		TextOut(hdc, 0, 0, szHint, lstrlen(szHint));
	}
};

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
