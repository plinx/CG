#ifndef win_h
#define win_h

#include <Windows.h>

class LWindow
{
protected:
	HWND m_hwnd;
	HDC m_hDC, m_hDCmem;
	int m_width, m_height;

public:
	LWindow() { 
		m_hwnd = NULL; 
		m_hDC = m_hDCmem = NULL;
		m_width = m_height = 0; 
	}
	virtual ~LWindow() = default;

	BOOL Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwstyle,
		int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance);
	BOOL Create(int nWidth, int nHeight, HINSTANCE hInstance);
	BOOL Create(HINSTANCE hInstance);

	HBITMAP CreateDIB();
	WPARAM MsgLoop(void);

	void Render();
};

#endif