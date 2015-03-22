#ifndef LWin_h
#define LWin_h
//#include <Windows.h>
#include "../stdafx.h"

class LWindow
{
protected:
	HWND m_hwnd;
	HDC m_hDC, m_hDCmem;
	int m_width, m_height;
	PBYTE* ScanLine;

public:
	LWindow() { 
		m_hwnd = NULL; 
		m_hDC = m_hDCmem = NULL;
		m_width = m_height = 0; 
		//ScanLine = NULL;
	}
	virtual ~LWindow() = default;

	BOOL Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwstyle,
		int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance);
	BOOL Create(int nWidth, int nHeight, HINSTANCE hInstance);
	BOOL Create(HINSTANCE hInstance);

	HBITMAP CreateDIB();
	WPARAM MsgLoop(void);

	void Init();
	void Render(HBITMAP& hBitmap);
};

#endif