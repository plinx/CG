#include "win.h"

class RectWindow : public LWindow
{
	void OnDraw(HDC hdc);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	RectWindow win;

	win.Create(640, 480, hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void RectWindow::OnDraw(HDC hdc)
{
	static HDC hdcCompat;    // DC for copying bitmap  
	static POINT pt;         // x and y coordinates of cursor  
	static RECT rcBmp;       // rectangle that encloses bitmap  
	static RECT rcTarget;    // rectangle to receive bitmap  
	static RECT rcClient;    // client-area rectangle  
	static BOOL fDragRect;   // TRUE if bitmap rect. is dragged  
	static HBITMAP hbmp;     // handle of bitmap to display  
	static HBRUSH hbrBkgnd;  // handle of background-color brush  
	static COLORREF crBkgnd; // color of client-area background  
	static HPEN hpenDot;     // handle of dotted pen  

	hdcCompat = CreateCompatibleDC(hdc);
	SelectObject(hdcCompat, hbmp);

	// Create a brush of the same color as the background  
	// of the client area. The brush is used later to erase  
	// the old bitmap before copying the bitmap into the  
	// target rectangle.  

	crBkgnd = GetBkColor(hdc);
	hbrBkgnd = CreateSolidBrush(crBkgnd);

	// Create a dotted pen. The pen is used to draw the  
	// bitmap rectangle as the user drags it.  

	hpenDot = CreatePen(PS_DOT, 1, RGB(0, 0, 0));

	// Set the initial rectangle for the bitmap. Note that  
	// this application supports only a 32- by 32-pixel  
	// bitmap. The rectangle is slightly larger than the  
	// bitmap.  

	SetRect(&rcBmp, 1, 1, 34, 34);

	Rectangle(hdc, rcBmp.left, rcBmp.top,
		rcBmp.right, rcBmp.bottom);
	StretchBlt(hdc, rcBmp.left + 1, rcBmp.top + 1,
		(rcBmp.right - rcBmp.left) - 2,
		(rcBmp.bottom - rcBmp.top) - 2, hdcCompat,
		0, 0, 32, 32, SRCCOPY);

	ReleaseDC(m_hwnd, hdc);
}