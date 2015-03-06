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
	BITMAPINFO* Info = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + 2 * sizeof(RGBQUAD));
	BITMAPINFOHEADER* bmih = &Info->bmiHeader;
	BYTE *pBits;
	HBITMAP hBitmap;

	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = m_width;
	bmih->biHeight = m_height;
	bmih->biPlanes = 1;
	bmih->biBitCount = 24;
	bmih->biCompression = BI_RGB;
	bmih->biSizeImage = 0;
	bmih->biXPelsPerMeter = 0;
	bmih->biYPelsPerMeter = 0;
	bmih->biClrUsed = 0;
	bmih->biClrImportant = 0;

	hBitmap = CreateDIBSection(NULL, Info, DIB_RGB_COLORS, (void **)&pBits, NULL, 0);
	
	int BytesPerLine = m_width * 3;
	if (BytesPerLine % 4 != 0)
		BytesPerLine += 4 - BytesPerLine % 4;

	ScanLine = new PBYTE[m_height];
	for (int i = 0; i < m_height; i++)
	{
		ScanLine[m_height - i] = pBits + BytesPerLine * i;
	}

	return hBitmap;
}

WPARAM LWindow::MsgLoop(void)
{
	MSG msg;
	HBITMAP hBitmap;

	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);
	
	m_hDC = GetDC(m_hwnd);
	m_hDCmem = CreateCompatibleDC(m_hDC);
	//SetRect(&rect, 0, 0, m_width, m_height);
	hBitmap = CreateDIB();
	SelectObject(m_hDCmem, hBitmap);
	//FillRect(m_hDCmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	Render();
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

#if 0
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
#endif

	ReleaseDC(m_hwnd, m_hDC);
	DeleteDC(m_hDCmem);
	DeleteObject(hBitmap);

	return msg.wParam;
}

void LWindow::Render(void)
{
	if (m_width == 0 || m_height == 0)
		return;

	Pixel pixel;
	Color color(0.5, 0.5, 0.5);
	Ray3 ray;
	IntersectResult result1, result2;
	double sx, sy;
	int f = 0;

	auto sphere = Sphere(Vec3(0, 10, -10), 10);
	auto plane = Plane(Vec3(0, 1, 0), 0);
	auto camera = Camera(Vec3(0, 10, 20), Vec3(0, 0, -1), Vec3(0, 1, 0), 90);
	auto material1 = PhongMaterial(getColor(Color_RED), getColor(Color_WHITE), 26);
	auto material2 = CheckerMaterial(0.1);
	sphere.initialize();
	camera.initialize();

	for (int y = 0; y < m_height; y++)
	{
		//Line = ScanLine[y];
		pixel.setPoint(ScanLine[y]);
		sy = 1 - (double)y / m_height;
		for (double x = 0; x < m_width; x++)
		{
			sx = x / m_width;
			ray = camera.generateRay(sx, sy);
			result1 = sphere.intersect(ray);
			result2 = plane.intersect(ray);
			if (result1.geometry && result2.geometry) 
			{
				if (result1.distance < result2.distance)
				{
					color = material1.sample(ray, result1.position, result1.normal);
					pixel.setR(color.getR() * 255);
					pixel.setG(color.getG() * 255);
					pixel.setB(color.getB() * 255);
				}
				else
				{
					color = material2.sample(ray, result2.position, result2.normal);
					pixel.setR(color.getR() * 255);
					pixel.setG(color.getG() * 255);
					pixel.setB(color.getB() * 255);
				}
			}
			else if (result1.geometry)
			{
				color = material1.sample(ray, result1.position, result1.normal);
				pixel.setR(color.getR() * 255);
				pixel.setG(color.getG() * 255);
				pixel.setB(color.getB() * 255);
			}
			else if (result2.geometry)
			{
				color = material2.sample(ray, result2.position, result2.normal);
				pixel.setR(color.getR() * 255);
				pixel.setG(color.getG() * 255);
				pixel.setB(color.getB() * 255);
			}

			/*if (result.geometry) {
				color = material.sample(ray, result.position, result.normal);
				pixel.setR(color.getR() * 255);
				pixel.setG(color.getG() * 255);
				pixel.setB(color.getB() * 255);
				//pixel.setR(getColor(Color_RED).getB() * 255);
				//pixel.setG(0);
				//pixel.setB(0);
			}*/
			pixel.Next();
		}
	}

	BitBlt(m_hDC, 0, 0, m_width, m_height,
		m_hDCmem, 0, 0, SRCCOPY);
}