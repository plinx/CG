#include "win.h"

class RectangleWindow : public LWindow
{
	void OnDraw(HDC hdc);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	RectangleWindow win;
	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void RectangleWindow::OnDraw(HDC hdc)
{
	TRIVERTEX vertex[2];

	vertex[0].x = 0;
	vertex[0].y = 0;
	vertex[0].Red = 0x0000;
	vertex[0].Green = 0x8000;
	vertex[0].Blue = 0x8000;
	vertex[0].Alpha = 0x0000;

	vertex[1].x = 300;
	vertex[1].y = 80;
	vertex[1].Red = 0x0000;
	vertex[1].Green = 0xd000;
	vertex[1].Blue = 0xd000;
	vertex[1].Alpha = 0x0000;

	// Create a GRADIENT_RECT structure that 
	// references the TRIVERTEX vertices. 
	GRADIENT_RECT gRect;
	gRect.UpperLeft = 0;
	gRect.LowerRight = 1;

	// Draw a shaded rectangle. 
	GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
}