#include "basewin.h"

WinApp::WinApp(void)
{
}

WinApp::~WinApp(void)
{
}

void WinApp::Create(int wd, int ht)
{
	width = wd;
	height = ht;
}

bool WinApp::Init(HINSTANCE hInstance, int iCmdShow)
{
	static TCHAR AppName[] = TEXT("SoftRender");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WdProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = AppName;


	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Error with wndclass"),
			AppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(AppName,
		TEXT("SoftRender v0.1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WdProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	Painter painter;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		painter.ConnectHDC(hdc);
		for (int i = 100, j = 100; i < 300; i++, j++)
		{
			painter.DrawPixel(i, j, RGB(0, 0, 0));
		}
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}