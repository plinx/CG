#ifndef win_h
#define win_h

#include <Windows.h>

class LWindow
{
protected:
	virtual void OnDraw(HDC hdc) {}
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) {}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	HWND m_hwnd;

	LWindow()
	{
		m_hwnd = NULL;
	}
	virtual ~LWindow() = default;

	BOOL Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwStyle,
		int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInst);
	BOOL Create(HINSTANCE hInst);
	BOOL Create(int nWidth, int nHeight, HINSTANCE hInst);
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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#endif