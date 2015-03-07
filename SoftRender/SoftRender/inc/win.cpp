#include <assert.h>
#include "win.h"

template <typename T>
inline IntersectResult getGeometriesResult(const Ray3 ray, std::vector<T>& geometries);
template <typename T>
inline IntersectResult getGeometriesResult(const Ray3 ray, T& tail);
template <typename T, typename... Args>
inline IntersectResult getGeometriesResult(const Ray3 ray, T& head, Args&... rest);
template <typename T>
inline Color rayTraceReflection(Ray3 ray, int maxReflect, T& tail);
template <typename T, typename... Args>
inline Color rayTraceReflection(Ray3 ray, int maxReflect, T& head, Args&... rest);
template <typename T>
inline Color rayTraceReflection(Ray3 ray, int maxReflect, std::vector<T>& geometries);
//inline Color rayTraceReflection(Ray3 ray, int maxReflect, Sphere sphere, Plane plane);

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
		ScanLine[m_height - i - 1] = pBits + BytesPerLine * i;
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
	Color color;
	Ray3 ray;
	IntersectResult result, result1, result2;
	double sx, sy;
	int f = 0;

	std::vector<Model*> geometries;
	auto sphere1 = Sphere(Vec3(-15, 10, -10), 10);
	auto sphere2 = Sphere(Vec3(15, 10, -10), 10);
	auto sphere3 = Sphere(Vec3(-10, 10, -30), 10);
	auto sphere4 = Sphere(Vec3(10, 10, -30), 10);
	auto plane = Plane(Vec3(0, 1, 0), 0);
	auto camera = Camera(Vec3(0, 10, 20), Vec3(0, 0, -1), Vec3(0, 1, 0), 90);

	sphere1.initialize();
	sphere2.initialize();
	sphere3.initialize();
	sphere4.initialize();
	plane.initialize();
	camera.initialize();

	sphere1.material = new PhongMaterial(getColor(Color_RED), getColor(Color_WHITE), 26, 0.25);
	sphere2.material = new PhongMaterial(getColor(Color_GREEN), getColor(Color_WHITE), 26, 0.25);
	sphere3.material = new PhongMaterial(getColor(Color_BLUE), getColor(Color_WHITE), 26, 0.25);
	sphere4.material = new PhongMaterial(getColor(Color_YELLOW), getColor(Color_WHITE), 26, 0.25);
	plane.material = new CheckerMaterial(0.1, 0.25);

	//auto material1 = new PhongMaterial(getColor(Color_RED), getColor(Color_WHITE), 26, 0.25);
	TCHAR test[100];
	//sprintf_s(test, "%lf", sphere1.material->getReflect());
	//MessageBox(NULL, test, TEXT("T"), 0);

	geometries.push_back(&sphere1);
	geometries.push_back(&sphere2);
	geometries.push_back(&sphere3);
	geometries.push_back(&sphere4);
	geometries.push_back(&plane);

	auto start = clock();
	for (int y = 0; y < m_height; y++)
	{
		//auto Line = ScanLine[y];
		pixel.setPoint(ScanLine[y]);
		sy = 1 - (double)y / m_height;
		for (double x = 0; x < m_width; x++)
		{
			sx = x / m_width;
			ray = camera.generateRay(sx, sy);
			// vector version : 2.7s/3.4s
			//result = getGeometriesResult(ray, geometries);
			// template version : 1.3s
			//result = getGeometriesResult(ray, 
			//	sphere1, sphere2, sphere3, sphere4, plane);


			// template version : 3.1s
			color = rayTraceReflection(ray, 2,
				sphere1, sphere2, sphere3, sphere4, plane);
			// vector vestion : 5.2s
			//color = rayTraceReflection(ray, 2, geometries);

			//if (result.geometry)
			//{ 
				//color = result.material->sample(ray, result.position, result.normal);
				pixel.setR(color.getR() * 255);
				pixel.setG(color.getG() * 255);
				pixel.setB(color.getB() * 255);
			//}
			
			pixel.Next();
		}
	}

	BitBlt(m_hDC, 0, 0, m_width, m_height,
		m_hDCmem, 0, 0, SRCCOPY);
	sprintf_s(test, "render time : %1.1f s", (float)(clock() - start) / 1000);
	MessageBox(NULL, test, TEXT("test"), 0);
}

// template version recursive
template <typename T>
inline IntersectResult getGeometriesResult(const Ray3 ray, T& tail)
{
	return tail.intersect(ray);
	//return IntersectResult();
}

template <typename T, typename... Args>
inline IntersectResult getGeometriesResult(const Ray3 ray, T& head, Args&... rest)
{
	auto result = head.intersect(ray);
	auto tail = getGeometriesResult(ray, rest...);

	if (result.geometry)
	{
		if (result.distance < tail.distance)
			return result;
	}

	return tail;
}

// vector version
template <typename T>
inline IntersectResult getGeometriesResult(const Ray3 ray, std::vector<T>& geometries)
{
	auto result = geometries[0]->intersect(ray);
	// operator[] access faster, still slower than template version
	for (size_t i = 0; i < geometries.size(); i++)	
	{
		result = result.distance < geometries[i]->intersect(ray).distance ? result : geometries[i]->intersect(ray);
	}
	/*for (auto &g : geometries)
	{
		result = result.distance < g->intersect(ray).distance ? result : g->intersect(ray);
	}*/

	return result;
}

template <typename T>
inline Color rayTraceReflection(Ray3 ray, int maxReflect, T& tail)
{
	auto result = getGeometriesResult(ray, tail);

	if (result.geometry)
	{
		auto reflect = result.material->getReflect();
		auto color = result.material->sample(ray, result.position, result.normal);
		color = color.mul(1 - reflect);

		if (reflect > 0 && maxReflect > 0)
		{
			auto r = result.normal.mul(-2 * result.normal.dot(ray.direction)).add(ray.direction);
			ray = Ray3(result.position, r);
			auto reflectedColor = rayTraceReflection(ray, maxReflect - 1, tail);
			color = color.add(reflectedColor.mul(reflect));
		}
		return color;
	}
	return getColor(Color_BLACK);
}

template <typename T, typename... Args>
inline Color rayTraceReflection(Ray3 ray, int maxReflect, T& head, Args&... rest)
{
	auto result = getGeometriesResult(ray, head, rest...);

	if (result.geometry)
	{
		auto reflect = result.material->getReflect();
		auto color = result.material->sample(ray, result.position, result.normal);
		color = color.mul(1 - reflect);

		if (reflect > 0 && maxReflect > 0)
		{
			auto r = result.normal.mul(-2 * result.normal.dot(ray.direction)).add(ray.direction);
			ray = Ray3(result.position, r);
			auto reflectedColor = rayTraceReflection(ray, maxReflect - 1, head, rest...);
			color = color.add(reflectedColor.mul(reflect));
		}
		return color;
	}
	return getColor(Color_BLACK);
}

template <typename T>
inline Color rayTraceReflection(Ray3 ray, int maxReflect, std::vector<T>& geometries)
{
	auto result = getGeometriesResult(ray, geometries);

	if (result.geometry)
	{
		auto reflect = result.material->getReflect();
		auto color = result.material->sample(ray, result.position, result.normal);
		color = color.mul(1 - reflect);

		if (reflect > 0 && maxReflect > 0)
		{
			auto r = result.normal.mul(-2 * result.normal.dot(ray.direction)).add(ray.direction);
			ray = Ray3(result.position, r);
			auto reflectedColor = rayTraceReflection(ray, maxReflect - 1, geometries);
			color = color.add(reflectedColor.mul(reflect));
		}
		return color;
	}
	return getColor(Color_BLACK);
}

/*inline Color rayTraceReflection(Ray3 ray, int maxReflect, Sphere sphere, Plane plane)
{
	auto result = getGeometriesResult(ray, sphere, plane);
	//auto result = plane.intersect(ray);

	if (result.geometry)
	{
		auto reflect = result.material->getReflect();
		auto color = result.material->sample(ray, result.position, result.normal);
		color = color.mul(1 - reflect);

		if (reflect > 0 && maxReflect > 0)
		{
			auto r = result.normal.mul(-2 * result.normal.dot(ray.direction)).add(ray.direction);
			ray = Ray3(result.position, r);
			auto reflectedColor = rayTraceReflection(ray, maxReflect - 1, sphere, plane);
			color = color.add(reflectedColor.mul(reflect));
		}
		return color;
	}
	return getColor(Color_BLACK);
}*/
