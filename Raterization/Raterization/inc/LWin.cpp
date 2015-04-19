#include <assert.h>
#include "LWin.h"

#pragma comment(lib, "Msimg32.lib")

extern double sin_table[361];
extern double cos_table[361];

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
	bmih->biBitCount = 24;
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

	//painter.drawLine(100, 200, 300, 100, Color(Black));
	//painter.drawTriangle(100, 300, 100, 200, 300, 200, Color(Black));

	Point4D cam_pos(0, 0, -10, 1);
	Point4D cam_target(0, 0, 0, 0);
	Vector4D cam_dir(0, 0, 0, 1);
	Vector4D vscale(0.5, 0.5, 0.5, 1), vpos(0, 0, 0, 1), vrot(0, 0, 0, 1);
	Point4D poly_pos(0, 0, 0, 1);
	Camera camera(0, cam_pos, cam_dir, cam_target, 50.0, 500.0, 90.0, 400, 400);
	RenderList4D rlist;
	Object4D obj;
	Matrix4x4 mrot;
	POINT apt[3];

	Build_SinCos_Tables();
	Load_Object4D_PLG(&obj, "resource/cube2.plg", &vscale, &vpos, &vrot);

	/*FillRect(_hdcMem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	for (auto poly = 0; poly < rlist.num_polys; poly++)
	{
		PPolyFace4D curr_poly = rlist.poly_ptrs[poly];
		if (!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		apt[0].x = (LONG)curr_poly->tvlist[0].x;
		apt[0].y = (LONG)curr_poly->tvlist[0].y;
		apt[1].x = (LONG)curr_poly->tvlist[1].x;
		apt[1].y = (LONG)curr_poly->tvlist[1].y;
		apt[2].x = (LONG)curr_poly->tvlist[2].x;
		apt[2].y = (LONG)curr_poly->tvlist[2].y;

		painter.drawTriangle(curr_poly->tvlist[0].x, curr_poly->tvlist[0].y,
			curr_poly->tvlist[1].x, curr_poly->tvlist[1].y,
			curr_poly->tvlist[2].x, curr_poly->tvlist[2].y, Color(Blue));
		painter.drawLine(apt[0].x, apt[0].y, apt[1].x, apt[1].y, Color(White));
		painter.drawLine(apt[1].x, apt[1].y, apt[2].x, apt[2].y, Color(White));
		painter.drawLine(apt[2].x, apt[2].y, apt[0].x, apt[0].y, Color(White));
		//MoveToEx(_hdcMem, apt[0].x, apt[0].y, NULL);
		//LineTo(_hdcMem, apt[1].x, apt[1].y);
		//MoveToEx(_hdcMem, apt[1].x, apt[1].y, NULL);
		//LineTo(_hdcMem, apt[2].x, apt[2].y);
		//MoveToEx(_hdcMem, apt[2].x, apt[2].y, NULL);
		//LineTo(_hdcMem, apt[0].x, apt[0].y);
	}

	BitBlt(_hdc,
		0, 0, _width, _height,
		_hdcMem, 0, 0, SRCCOPY);
	*/


	//AlphaBlend(_hdc, 0, 0, _width, _height,
	//	_hdcMem, 0, 0, _width, _height, blend);

#if 0
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
			static int ang_x = 0;
			static int ang_y = 5;
			static int ang_z = 0;

			if (GetKeyState(VK_LEFT) < 0) ang_y+=5;
			if (GetKeyState(VK_RIGHT) < 0) ang_y-=5;
			if (GetKeyState(VK_UP) < 0) ang_x+=5;
			if (GetKeyState(VK_DOWN) < 0) ang_x-=5;
			if (GetKeyState(VK_SPACE) < 0) camera.pos.y+=5;
			if (GetKeyState(0x56) < 0) camera.pos.y-=5;

			mrot.build(ang_x, ang_y, ang_z);

			//obj.rotate(&mrot, TRANSFORM_LOCAL_ONLY, 1);
			rlist.reset();
			rlist.insert(&obj);
			rlist.rotate(&mrot, TRANSFORM_LOCAL_TO_TRANS);
			obj.to_World(TRANSFORM_LOCAL_TO_TRANS);
			//obj.world_pos = poly_pos;
			//obj.world_pos.z += 0;
			obj.to_World(TRANSFORM_TRANS_ONLY);
			rlist.insert(&obj);
			rlist.rotate(&mrot, TRANSFORM_LOCAL_TO_TRANS);
			rlist.to_World(&poly_pos, TRANSFORM_TRANS_ONLY);
			camera.build_Euler(CAM_ROT_SEQ_ZYX);
			camera.remove_Backfaces(&rlist);
			camera.from_World(&rlist);
			camera.to_Perspective(&rlist);
			camera.to_Screen(&rlist);


			FillRect(_hdcMem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

			for (auto poly = 0; poly < rlist.num_polys; poly++)
			{
				PPolyFace4D curr_poly = rlist.poly_ptrs[poly];
				if (!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
					(curr_poly->state & POLY4D_STATE_CLIPPED) ||
					(curr_poly->state & POLY4D_STATE_BACKFACE))
					continue;

				apt[0].x = (LONG)curr_poly->tvlist[0].x;
				apt[0].y = (LONG)curr_poly->tvlist[0].y;
				apt[1].x = (LONG)curr_poly->tvlist[1].x;
				apt[1].y = (LONG)curr_poly->tvlist[1].y;
				apt[2].x = (LONG)curr_poly->tvlist[2].x;
				apt[2].y = (LONG)curr_poly->tvlist[2].y;

				painter.drawTriangle(curr_poly->tvlist[0].x, curr_poly->tvlist[0].y, 
					curr_poly->tvlist[1].x, curr_poly->tvlist[1].y,
					curr_poly->tvlist[2].x, curr_poly->tvlist[2].y, Color(Blue));
				//painter.drawLine(apt[0].x, apt[0].y, apt[1].x, apt[1].y, Color(White));
				//painter.drawLine(apt[1].x, apt[1].y, apt[2].x, apt[2].y, Color(White));
				//painter.drawLine(apt[2].x, apt[2].y, apt[0].x, apt[0].y, Color(White));
				//MoveToEx(_hdcMem, apt[0].x, apt[0].y, NULL);
				//LineTo(_hdcMem, apt[1].x, apt[1].y);
				//MoveToEx(_hdcMem, apt[1].x, apt[1].y, NULL);
				//LineTo(_hdcMem, apt[2].x, apt[2].y);
				//MoveToEx(_hdcMem, apt[2].x, apt[2].y, NULL);
				//LineTo(_hdcMem, apt[0].x, apt[0].y);
			}

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

// Window demos
void LWindow::CircleDemo()
{
	for (int theta = 0; theta < 361; theta++)
	{
		painter.drawLine(200, 200, ceil(200 + 100 * sin(theta)), ceil(200 + 100 * cos(theta)));
	}
}

