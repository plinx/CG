#pragma once
#include <Windows.h>

class LWindow
{
public:
	LWindow() = default;
	~LWindow() = default;

	bool InitWindow(LPCTSTR lpClassName, int m_Width, int m_Height, HINSTANCE hInstance);
	WPARAM MessageLoop(void);

	BOOL ShowWindow(int iCmdShow) const
	{
		return ::ShowWindow(m_hwnd, iCmdShow);
	}

	BOOL UpdateWindow(void) const
	{
		return ::UpdateWindow(m_hwnd);
	}
	
private:
	HWND m_hwnd;
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
