#ifndef LWin_h
#define LWin_h
//#include <Windows.h>
#include "../stdafx.h"

class LWindow
{
	friend class Painter;
protected:
	HWND _hwnd;
	HDC _hdc, _hdcMem;
	int _width, _height;
	Painter painter;

public:
	LWindow() { 
		_hwnd = NULL; 
		_hdc = _hdcMem = NULL;
		_width = _height = 0; 
		painter.init(_width, _height);
		//ScanLine = NULL;
	}
	//~LWindow() = default;

	BOOL Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwstyle,
		int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance);
	BOOL Create(int nWidth, int nHeight, HINSTANCE hInstance);
	BOOL Create(HINSTANCE hInstance);

	HBITMAP CreateDIB();
	WPARAM Render(void);

private:
	// Render demos
	void PixelDemo();
	void CircleDemo();
};

#endif