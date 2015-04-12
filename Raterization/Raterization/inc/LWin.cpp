#include <assert.h>
#include "LWin.h"

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

WPARAM LWindow::Render(void)
{
	// window init
	MSG msg;
	HBITMAP hBitmap;
	HPEN hPen;
	//HBRUSH hBrush;
	POINT apt[3];
	RECT rect;

	// render init
	int cam_dist = 300;
	Point4D cam_pos(cam_dist, 0, 0, 1);
	Point4D cam_target(0, 0, 0, 0);
	Vector4D cam_dir(0, 0, 0, 1);
	Vector4D vscale(0.5, 0.5, 0.5, 1), vpos(0, 0, 0, 1), vrot(0, 0, 0, 1);
	Camera camera;
	RenderList4D rlist;
	PolyFace4D poly1;
	Point4D poly_pos(0, 0, 100, 1);
	Object4D obj;
	Matrix4x4 mrot;

	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);
	
	m_hDC = GetDC(m_hwnd);
	m_hDCmem = CreateCompatibleDC(m_hDC);
	SetRect(&rect, 0, 0, m_width, m_height);
	hBitmap = CreateDIB();
	SelectObject(m_hDCmem, hBitmap);
	//FillRect(m_hDCmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(m_hDCmem, hPen);
	//hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 255));
	//SelectObject(m_hDCmem, hBrush);

	Build_SinCos_Tables();

	camera.init(0, cam_pos, cam_dir, cam_target, 10.0, 1200.0, 90.0, m_width, m_height);
	Load_Object4D_PLG(&obj, "resource/tank1.plg", &vscale, &vpos, &vrot);

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
			static int ang_y = 0;
			static int ang_z = 0;
			// Render
			if (GetKeyState(VK_LEFT) < 0)
			{
				if (ang_y++ > 360) ang_y = 0;
				camera.pos.x = cam_dist * Fast_cos(ang_y);
				camera.pos.z = cam_dist * Fast_sin(ang_y);
			}
			if (GetKeyState(VK_RIGHT) < 0)
			{
				if (ang_y-- < 0) ang_y = 360;
				camera.pos.x = cam_dist * Fast_cos(ang_y);
				camera.pos.z = cam_dist * Fast_sin(ang_y);
			}
			if (GetKeyState(VK_UP) < 0) {
				cam_dist += 5;
				camera.pos.x += 5;
			}
			if (GetKeyState(VK_DOWN) < 0)
			{
				cam_dist -= 5;
				camera.pos.x -= 5;
			}
			if (GetKeyState(VK_SPACE) < 0) camera.pos.y++;
			if (GetKeyState(VK_V) < 0) camera.pos.y--;
			//if (GetKeyState(VK_Q) < 0) ang_y++;
			//if (GetKeyState(VK_E) < 0) ang_y--;
			mrot.build(ang_x, ang_y, ang_z);

			rlist.reset();
			for (int x = -16; x < 16; x++)
			{
				for (int z = -16; z < 16; z++)
				{
					obj.reset();
					obj.world_pos = poly_pos;
					obj.world_pos.x = x * 100;
					obj.world_pos.z = z * 100;
					obj.to_World();
					camera.cull(&obj, CULL_OBJECT_XYZ_PLANE);
					rlist.insert(&obj);
				}
			}
			rlist.rotate(&mrot, TRANSFORM_LOCAL_TO_TRANS);
			rlist.to_World(&poly_pos, TRANSFORM_TRANS_ONLY);
			//camera.build_Euler(CAM_ROT_SEQ_ZYX);
			camera.build_UVN(UVN_MODE_SIMPLE);
			camera.remove_Backfaces(&rlist);
			camera.from_World(&rlist);
			camera.to_Perspective(&rlist);
			camera.to_Screen(&rlist);

			FillRect(m_hDCmem, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
			
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

				//Polyline(m_hDCmem, apt, 3);
				if (0 < apt[0].x && apt[0].x < m_width 
					&& 0 < apt[0].y && apt[0].y < m_width)
				{
					MoveToEx(m_hDCmem, apt[0].x, apt[0].y, NULL);
					LineTo(m_hDCmem, apt[1].x, apt[1].y);
				}
				if (0 < apt[0].x && apt[0].x < m_width 
					&& 0 < apt[0].y && apt[0].y < m_width)
				{
					MoveToEx(m_hDCmem, apt[1].x, apt[1].y, NULL);
					LineTo(m_hDCmem, apt[2].x, apt[2].y);
				}
				if (0 < apt[0].x && apt[0].x < m_width 
					&& 0 < apt[0].y && apt[0].y < m_width)
				{
					MoveToEx(m_hDCmem, apt[2].x, apt[2].y, NULL);
					LineTo(m_hDCmem, apt[0].x, apt[0].y);
				}
			}

			/*for (auto poly = 0; poly < obj.num_poly; poly++)
			{
				if (!(obj.plist[poly].state & POLY4D_STATE_ACTIVE) ||
					(obj.plist[poly].state & POLY4D_STATE_CLIPPED) ||
					(obj.plist[poly].state & POLY4D_STATE_BACKFACE))
					continue;

				apt[0].x = (LONG)obj.vlist_trans[obj.plist[poly].vert[0]].x;
				apt[0].y = (LONG)obj.vlist_trans[obj.plist[poly].vert[0]].y;
				apt[1].x = (LONG)obj.vlist_trans[obj.plist[poly].vert[1]].x;
				apt[1].y = (LONG)obj.vlist_trans[obj.plist[poly].vert[1]].y;
				apt[2].x = (LONG)obj.vlist_trans[obj.plist[poly].vert[2]].x;
				apt[2].y = (LONG)obj.vlist_trans[obj.plist[poly].vert[2]].y;

				//Polyline(m_hDCmem, apt, 3);
				MoveToEx(m_hDCmem, apt[0].x, apt[0].y, NULL);
				LineTo(m_hDCmem, apt[1].x, apt[1].y);
				MoveToEx(m_hDCmem, apt[1].x, apt[1].y, NULL);
				LineTo(m_hDCmem, apt[2].x, apt[2].y);
				MoveToEx(m_hDCmem, apt[2].x, apt[2].y, NULL);
				LineTo(m_hDCmem, apt[0].x, apt[0].y);
			}*/


			BitBlt(m_hDC,
				0, 0, m_width, m_height,
				m_hDCmem, 0, 0, SRCCOPY);

			Sleep(10);

		}
	}
#endif

	ReleaseDC(m_hwnd, m_hDC);
	DeleteDC(m_hDCmem);
	DeleteObject(hBitmap);

	return msg.wParam;
}



