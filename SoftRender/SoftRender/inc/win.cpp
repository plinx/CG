#include <assert.h>
#include "win.h"

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

	m_hwnd = CreateWindow(lpszClass, lpszName, 
		WS_OVERLAPPEDWINDOW,
		x, y, nWidth, nHeight, 
		hParent, hMenu, hInst, NULL);
	m_width = nWidth;
	m_height = nHeight;

	MoveWindow(m_hwnd, 
		GetSystemMetrics(SM_CXSCREEN) / 2 - nWidth / 2, 
		GetSystemMetrics(SM_CYSCREEN) / 2 - nHeight / 2, 
		nWidth, nHeight, FALSE);

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

HBITMAP LWindow::CreateDIB()
{
	BITMAPINFOHEADER bmih;
	BYTE *pBits;
	HBITMAP hBitmap;

	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = m_width;
	bmih.biHeight = m_height;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = 0;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;

	hBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);

	return hBitmap;
}

WPARAM LWindow::MsgLoop(void)
{
	MSG msg;
	HBITMAP hBitmap;
	RECT rect;

	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);
	
	m_hDC = GetDC(m_hwnd);
	m_hDCmem = CreateCompatibleDC(m_hDC);
	SetRect(&rect, 0, 0, m_width, m_height);
	hBitmap = CreateDIB();
	SelectObject(m_hDCmem, hBitmap);
	FillRect(m_hDCmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Render
			Render();
		}
	}

	ReleaseDC(m_hwnd, m_hDC);
	DeleteDC(m_hDCmem);
	DeleteObject(hBitmap);

	return msg.wParam;
}

void LWindow::Render(void)
{
	RECT rect;
	HBRUSH hBrush;
	HPEN hPen;
	POINT apt[2];

	if (m_width == 0 || m_height == 0)
		return;

	//SetRect(&rect, rand() % m_width, rand() % m_height,
	//	rand() % m_width, rand() % m_height);

	//hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
	//hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	//FillRect(m_hDCmem, &rect, hBrush);
	hPen = CreatePen(PS_SOLID, 0, RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(m_hDCmem, hPen);
	apt[0].x = rand() % m_width;
	apt[0].y = rand() % m_height;
	apt[1].x = rand() % m_width;
	apt[1].y = rand() % m_height;
	Polyline(m_hDCmem, apt, 2);
	BitBlt(m_hDC, 0, 0, m_width, m_height,
		m_hDCmem, 0, 0, SRCCOPY);
}