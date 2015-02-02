#ifndef win_h
#define win_h

#include <Windows.h>

class LWindow
{
protected:
	HWND m_hwnd;

	virtual void OnDraw(HDC hdc) {}
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) {}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	LWindow() { m_hwnd = NULL; }
	virtual ~LWindow() = default;

	BOOL Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwstyle,
		int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInstance);
	BOOL Create(int nWidth, int nHeight, HINSTANCE hInstance);
	BOOL Create(HINSTANCE hInstance);
	WPARAM MessageLoop(void);

	BOOL ShowWindow(int iCmdShow) const
	{
		return ::ShowWindow(m_hwnd, iCmdShow);
	}

	BOOL UpdateWindow(void) const
	{
		return ::UpdateWindow(m_hwnd);
	}
};

#endif