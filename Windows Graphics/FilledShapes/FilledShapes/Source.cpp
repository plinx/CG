#include "win.h"

class ShapesWindow : public LWindow
{
	void OnDraw(HDC hdc);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	ShapesWindow win;
	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void ShapesWindow::OnDraw(HDC hdc)
{
	hdc = GetDC(m_hwnd);

	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
	Ellipse(hdc, 100, 0, 300, 200);

	SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
	Rectangle(hdc, 400, 100, 600, 400);

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	RoundRect(hdc, 100, 400, 200, 500, 10, 10);
}