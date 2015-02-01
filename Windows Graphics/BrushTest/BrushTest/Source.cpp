#include <assert.h>
#include "win.h"

class BrushWindow : public LWindow
{
	void OnDraw(HDC hdc);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	BrushWindow win;
	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void BrushWindow::OnDraw(HDC hdc)
{
	RECT clientRect;
	RECT textRect;
	HRGN bgRgn;
	HBRUSH hBrush;
	HPEN hPen;

	GetClientRect(m_hwnd, &clientRect);
	bgRgn = CreateRectRgnIndirect(&clientRect);
	hBrush = CreateSolidBrush(RGB(200, 200, 200));
	FillRgn(hdc, bgRgn, hBrush);

	hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	SetBkColor(hdc, RGB(0, 0, 0));
	Rectangle(hdc, 10, 10, 200, 200);

	// Text caption
	SetBkColor(hdc, RGB(255, 255, 255));
	SetRect(&textRect, 10, 210, 200, 200);
	DrawText(hdc, TEXT("PS_DOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);


	hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 255, 255));
	SelectObject(hdc, hPen);
	SetBkColor(hdc, RGB(255, 0, 0));
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
	Rectangle(hdc, 210, 10, 400, 200);

	// Text caption
	SetBkColor(hdc, RGB(255, 200, 200));
	SetRect(&textRect, 210, 210, 400, 200);
	DrawText(hdc, TEXT("PS_DASHDOTDOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);


	hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
	SelectObject(hdc, hPen);
	SetBkColor(hdc, RGB(255, 255, 0));
	SelectObject(hdc, CreateSolidBrush(RGB(100, 200, 255)));
	Rectangle(hdc, 410, 10, 600, 200);

	// Text caption
	SetBkColor(hdc, RGB(200, 255, 200));
	SetRect(&textRect, 410, 210, 600, 200);
	DrawText(hdc, TEXT("PS_DASHDOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);


	// When fnPenStyle is PS_SOLID, nWidth may be more than 1.
	// Also, if you set the width of any pen to be greater than 1, 
	// then it will draw a solid line, even if you try to select another style.
	hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	SelectObject(hdc, hPen);
	// Setting the background color doesn't matter 
	// when the style is PS_SOLID
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, CreateSolidBrush(RGB(200, 100, 50)));
	Rectangle(hdc, 10, 300, 200, 500);

	// Text caption
	SetBkColor(hdc, RGB(200, 200, 255));
	SetRect(&textRect, 10, 510, 200, 500);
	DrawText(hdc, TEXT("PS_SOLID"), -1, &textRect, DT_CENTER | DT_NOCLIP);

	hPen = CreatePen(PS_DASH, 1, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	SetBkColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, CreateSolidBrush(RGB(200, 200, 255)));
	Rectangle(hdc, 210, 300, 400, 500);

	// Text caption
	SetBkColor(hdc, RGB(255, 255, 200));
	SetRect(&textRect, 210, 510, 400, 200);
	DrawText(hdc, TEXT("PS_DASH"), -1, &textRect, DT_CENTER | DT_NOCLIP);

	hPen = CreatePen(PS_NULL, 1, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	// Setting the background color doesn't matter 
	// when the style is PS_NULL
	SetBkColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
	Rectangle(hdc, 410, 300, 600, 500);

	// Text caption
	SetBkColor(hdc, RGB(200, 255, 255));
	SetRect(&textRect, 410, 510, 600, 500);
	DrawText(hdc, TEXT("PS_NULL"), -1, &textRect, DT_CENTER | DT_NOCLIP);


	// Clean up
	DeleteObject(bgRgn);
	DeleteObject(hBrush);
	DeleteObject(hPen);

	GetStockObject(WHITE_BRUSH);
	GetStockObject(DC_PEN);

}