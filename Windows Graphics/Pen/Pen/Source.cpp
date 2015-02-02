#include "win.h"

class PenWindow : public LWindow
{
	void OnDraw(HDC hdc);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	PenWindow win;

	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void PenWindow::OnDraw(HDC hdc)
{
	LOGBRUSH lb; 
	RECT rc;
	int i;
	HGDIOBJ hPen = NULL;
	HGDIOBJ hPenOld;
	DWORD dwPenStyle[] = {
		PS_DASH,
		PS_DASHDOT,
		PS_DOT,
		PS_INSIDEFRAME,
		PS_NULL,
		PS_SOLID
	};
	UINT uHatch[] = {
		HS_BDIAGONAL,
		HS_CROSS,
		HS_DIAGCROSS,
		HS_FDIAGONAL,
		HS_HORIZONTAL,
		HS_VERTICAL
	};

	GetClientRect(m_hwnd, &rc);
	rc.left += 10;
	rc.top += 10;
	rc.bottom -= 10;

	// Initialize the pen's brush.
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(255, 0, 0);
	lb.lbHatch = 0;

	for (i = 0; i < 6; i++)
	{
		hPen = ExtCreatePen(PS_COSMETIC | dwPenStyle[i],
			1, &lb, 0, NULL);
		hPenOld = SelectObject(hdc, hPen);
		MoveToEx(hdc, rc.left + (i * 20), rc.top, NULL);
		LineTo(hdc, rc.left + (i * 20), rc.bottom);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
	}
	rc.left += 150;
	for (i = 0; i < 6; i++)
	{
		lb.lbStyle = BS_HATCHED;
		lb.lbColor = RGB(0, 0, 255);
		lb.lbHatch = uHatch[i];
		hPen = ExtCreatePen(PS_GEOMETRIC,
			5, &lb, 0, NULL);
		hPenOld = SelectObject(hdc, hPen);
		MoveToEx(hdc, rc.left + (i * 20), rc.top, NULL);
		LineTo(hdc, rc.left + (i * 20), rc.bottom);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
	}
}
