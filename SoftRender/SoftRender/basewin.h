#ifndef basewin_h
#define basewin_h

#include "painter.h"

LRESULT CALLBACK WdProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class WinApp
{
public:
	WinApp(void);
	~WinApp(void);
	void Create(int wd, int ht);
	bool Init(HINSTANCE, int);

private:
	HWND hwnd;
	MSG msg;
	WNDCLASS wc;

	int width;
	int height;
};

#endif