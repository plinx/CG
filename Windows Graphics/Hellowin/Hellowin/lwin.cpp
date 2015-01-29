#include "lwin.h"

LRESULT CALLBACK LWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		OnDraw(ps.hdc);
		EndPaint(hwnd, &ps);
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK LWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LWindow *pWindow;

	if (message == WM_NCCALCSIZE)
	{
		MDICREATESTRUCT *pMDIC = (MDICREATESTRUCT *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		pWindow = (LWindow *)(pMDIC->lParam);
		SetWindowLong(hwnd, GWL_USERDATA, (LONG)pWindow);
	}
	else
		pWindow = (LWindow*)GetWindowLong(hwnd, GWL_USERDATA);

	if (pWindow)
		return pWindow->WndProc(hwnd, message, wParam, lParam);
	else
		return DefWindowProc(hwnd, message, wParam, lParam);
}

bool LWindow::InitWindow(LPCTSTR lpszClassName, int m_Width, int m_Height, HINSTANCE hInstance)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpszClassName;


	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Error with wc"),
			lpszClassName, MB_ICONERROR);
		return 0;
	}

	m_hwnd = CreateWindow(lpszClassName,
		TEXT("The hello window program."),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_Width, m_Height,
		NULL, NULL,
		hInstance, NULL);

	if (m_hwnd)
		return 1;

	return 0;
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
