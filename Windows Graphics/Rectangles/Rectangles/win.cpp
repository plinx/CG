#include <assert.h>
#include "win.h"

LRESULT CALLBACK LWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CREATE:
		OnKeyDown(wParam, lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(m_hwnd, &ps);
		OnDraw(ps.hdc);
		EndPaint(m_hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK LWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LWindow *pWindow;

	if (msg == WM_NCCREATE)
	{
		assert(!IsBadReadPtr((void *)lParam, sizeof(CREATESTRUCT)));
		MDICREATESTRUCT *pMDIC = (MDICREATESTRUCT *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		pWindow = (LWindow *)(pMDIC->lParam);
		assert(!IsBadReadPtr(pWindow, sizeof(LWindow)));
		SetWindowLong(hwnd, GWL_USERDATA, (LONG)pWindow);
	}
	else
	{
		pWindow = (LWindow *)GetWindowLong(hwnd, GWL_USERDATA);
	}

	if (pWindow)
		return pWindow->WndProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL LWindow::Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwstyle,
	int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInst)
{
	WNDCLASS wc;
	MDICREATESTRUCT mdic;

	wc.style = dwstyle;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = lpszClass;
	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Register class WNDCLASS error!"), lpszClass, MB_ICONERROR);
		return FALSE;
	}

	memset(&mdic, 0, sizeof(mdic));
	mdic.lParam = (LPARAM)this;

	m_hwnd = CreateWindow(lpszClass, lpszName, WS_OVERLAPPEDWINDOW,
		x, y, nWidth, nHeight, hParent, hMenu, hInst, &mdic);

	return m_hwnd != NULL;
}

BOOL LWindow::Create(int nWidth, int nHeight, HINSTANCE hInst)
{
	const TCHAR szClass[] = TEXT("LWindow Application");
	const TCHAR szName[] = TEXT("LWindow Title");
	return Create(szClass, szName, CS_HREDRAW | CS_VREDRAW,
		CW_USEDEFAULT, CW_USEDEFAULT, nWidth, nHeight, NULL, NULL, hInst);
}

BOOL LWindow::Create(HINSTANCE hInst)
{
	return Create(800, 600, hInst);
}

WPARAM LWindow::MessageLoop(void)
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
