#include <assert.h>
#include "LWin.h"

#pragma comment(lib, "Msimg32.lib")

#define VK_E 0x45
#define VK_Q 0x51
#define VK_V 0x56

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL LWindow::Create(LPCTSTR lpszClass, LPCTSTR lpszName, DWORD dwstyle,
	int x, int y, int nWidth, int nHeight, HWND hParent, HMENU hMenu, HINSTANCE hInst)
{
	WNDCLASS wc;
	RECT rect;

	wc.style = dwstyle;
	wc.lpfnWndProc = WndProc;
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
		MessageBox(NULL, TEXT("Register WNDCLASS error!"), 
			lpszClass, MB_ICONERROR);
		return FALSE;
	}

	SetRect(&rect, 0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	_hwnd = CreateWindow(lpszClass, lpszName,
		WS_OVERLAPPEDWINDOW,
		x, y, rect.right - rect.left, rect.bottom - rect.top, 
		hParent, hMenu, hInst, NULL);
	_width = nWidth;
	_height = nHeight;
	painter.init(nWidth, nHeight);

	MoveWindow(_hwnd, 
		GetSystemMetrics(SM_CXSCREEN) / 2 - nWidth / 2, 
		GetSystemMetrics(SM_CYSCREEN) / 2 - nHeight / 2, 
		rect.right - rect.left, rect.bottom - rect.top, FALSE);

	return _hwnd != NULL;
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

HBITMAP LWindow::CreateDIB()
{
	BITMAPINFO* Info = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + 2 * sizeof(RGBQUAD));
	BITMAPINFOHEADER* bmih = &Info->bmiHeader;
	HBITMAP hBitmap;

	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = _width;
	bmih->biHeight = _height;
	bmih->biPlanes = 1;
	bmih->biBitCount = 32;
	bmih->biCompression = BI_RGB;
	bmih->biSizeImage = 0;
	bmih->biXPelsPerMeter = 0;
	bmih->biYPelsPerMeter = 0;
	bmih->biClrUsed = 0;
	bmih->biClrImportant = 0;

	hBitmap = CreateDIBSection(NULL, Info, DIB_RGB_COLORS, (void**)&painter._scanLine, NULL, 0);
	
	return hBitmap;
}

WPARAM LWindow::Render(void)
{
	// window init
	MSG msg;
	HBITMAP hBitmap;
	BLENDFUNCTION blend;

	HPEN hPen;
	RECT rect;

	ShowWindow(_hwnd, SW_SHOWNORMAL);
	UpdateWindow(_hwnd);
	
	_hdc = GetDC(_hwnd);
	_hdcMem = CreateCompatibleDC(_hdc);
	SetRect(&rect, 0, 0, _width, _height);
	hBitmap = CreateDIB();
	SelectObject(_hdcMem, hBitmap);
	FillRect(_hdcMem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(_hdcMem, hPen);
	//FillRect(_hdcMem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = AC_SRC_ALPHA; // use source alpha
	blend.SourceConstantAlpha = 0xff; // opaque (disable constant alpha)

	/*for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			painter.drawPixel(x, y);
		}
	}*/
	//painter.drawLine(0, 0, _width, _height);
	/*for (int y = 0; y < _height; y++)
	{
		painter.drawHorizonLine(0, _width, y, Color(Red));
	}*/
	//painter.drawTriangle(10, -100, 200, 600, 300, -100, Color(Black));
	painter.drawTriangle(-100, 200, 500, 400, 550, 200, Color(Black));
	//painter.drawTriangle(100, 100, 200, 200, 300, 50, Color(Black));
	//painter.drawTriangle(200, -200, 100, 500, 300, 500, Color(Red));
	/*painter.drawTriangle(100, 200, 100, 300, 100, 400, Color(Red));
	painter.drawTriangle(100, 200, 200, 200, 300, 200, Color(Blue));
	painter.drawTriangle(100, 200, 200, 300, 300, 400, Color(Cyan));
	painter.drawTriangle(100, 200, 200, 250, 300, 300, Color(Yellow));
	painter.drawTriangle(100, 200, 200, 150, 300, 100, Color(Green));*/

		
	AlphaBlend(_hdc, 0, 0, _width, _height,
		_hdcMem, 0, 0, _width, _height, blend);

#if 1
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#else
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			//if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			FillRect(_hdcMem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
			
			BitBlt(_hdc,
				0, 0, _width, _height,
				_hdcMem, 0, 0, SRCCOPY);

			Sleep(10);

		}
	}
#endif

	ReleaseDC(_hwnd, _hdc);
	DeleteDC(_hdcMem);
	DeleteObject(hBitmap);

	return msg.wParam;
}



