#include "win.h"

class TriangleWindow : public LWindow
{
	void OnDraw(HDC);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	TriangleWindow win;
	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void TriangleWindow::OnDraw(HDC hdc)
{
	TRIVERTEX vertex[3];

	vertex[0].x = 0;
	vertex[0].y = 0;
	vertex[0].Red = 0xff00;
	vertex[0].Green = 0x8000;
	vertex[0].Blue = 0x0000;
	vertex[0].Alpha = 0x0000;

	vertex[1].x = 500;
	vertex[1].y = 0;
	vertex[1].Red = 0x9000;
	vertex[1].Green = 0x0000;
	vertex[1].Blue = 0x9000;
	vertex[1].Alpha = 0x0000;

	vertex[2].x = 300;
	vertex[2].y = 350;
	vertex[2].Red = 0x9000;
	vertex[2].Green = 0x0000;
	vertex[2].Blue = 0x9000;
	vertex[2].Alpha = 0x0000;

	GRADIENT_TRIANGLE gTriangle;
	gTriangle.Vertex1 = 0;
	gTriangle.Vertex2 = 1;
	gTriangle.Vertex3 = 2;

	GradientFill(hdc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
}