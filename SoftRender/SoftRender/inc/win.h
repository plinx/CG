#ifndef win_h
#define win_h

#include <Windows.h>
/*#include "Sphere.h"
#include "Camera.h"
#include "Ray3.h"
#include "Vec3.h"
#include "IntersectResult.h"*/
#include "Vec3.h"
#include "Ray3.h"
#include "Camera.h"
#include "IntersectResult.h"
#include "Sphere.h"

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

	void Render();
};

#endif