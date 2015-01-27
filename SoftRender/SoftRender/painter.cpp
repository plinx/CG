#include "painter.h"

Painter::Painter(void)
{
}

Painter::~Painter(void)
{
}

void Painter::ConnectHDC(HDC hdc)
{
	phdc = hdc;
}

void Painter::DrawPixel(int x, int y, COLORREF color)
{
	SetPixel(phdc, x, y, color);
}
