#ifndef painter_h
#define painter_h

#include <Windows.h>

class Painter
{
public:
	Painter(void);
	~Painter(void);
	void ConnectHDC(HDC hdc);
	void DrawPixel(int x, int y, COLORREF color);
private:
	HDC phdc;
};

#endif
