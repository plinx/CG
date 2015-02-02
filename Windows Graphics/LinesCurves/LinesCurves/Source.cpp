#include "win.h"

class LCWindow : public LWindow
{
	void OnDraw(HDC hdc);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	LCWindow win;
	
	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}


void LCWindow::OnDraw(HDC hdc)
{
	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
	MoveToEx(hdc, 200, 200, (LPPOINT)NULL);
	AngleArc(hdc, 200, 200, 150, 90, 270);
	LineTo(hdc, 200, 200);
	StrokeAndFillPath(hdc);

	MoveToEx(hdc, 400, 400, (LPPOINT)NULL);
	LineTo(hdc, 420, 500);
	MoveToEx(hdc, 430, 500, (LPPOINT)NULL);
	LineTo(hdc, 410, 400);
}