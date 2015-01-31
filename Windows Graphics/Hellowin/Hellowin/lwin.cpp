#include "lwin.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR szHint[] = TEXT("Press ESC to quit!");

	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 0, 0, szHint, lstrlen(szHint));
		EndPaint(hwnd, &ps);
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool LWindow::InitWindow(LPCTSTR lpszClassName, int m_Width, int m_Height, HINSTANCE hInstance)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
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
