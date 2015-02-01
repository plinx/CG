#include "win.h"

typedef enum
{
	SCALE,
	TRANSLATE,
	ROTATE,
	SHEAR,
	REFLECT,
	NORMAL
};

class TransWindow : public LWindow
{
	void OnDraw(HDC hdc);
	XFORM GetXFORM(int iTransform);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	TransWindow win;
	win.Create(hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void TransWindow::OnDraw(HDC hdc)
{
	RECT rect;
	XFORM xForm;

	hdc = GetDC(m_hwnd);
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetMapMode(hdc, MM_LOENGLISH);

	xForm = GetXFORM(SHEAR);
	SetWorldTransform(hdc, &xForm);

	// Find the midpoint of the client area.  

	GetClientRect(m_hwnd, (LPRECT)&rect);
	DPtoLP(hdc, (LPPOINT)&rect, 2);

	// Select a hollow brush.  

	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

	// Draw the exterior circle.  

	Ellipse(hdc, (rect.right / 2 - 100), (rect.bottom / 2 + 100),
		(rect.right / 2 + 100), (rect.bottom / 2 - 100));

	// Draw the interior circle.  

	Ellipse(hdc, (rect.right / 2 - 94), (rect.bottom / 2 + 94),
		(rect.right / 2 + 94), (rect.bottom / 2 - 94));

	// Draw the key.  

	Rectangle(hdc, (rect.right / 2 - 13), (rect.bottom / 2 + 113),
		(rect.right / 2 + 13), (rect.bottom / 2 + 50));
	Rectangle(hdc, (rect.right / 2 - 13), (rect.bottom / 2 + 96),
		(rect.right / 2 + 13), (rect.bottom / 2 + 50));

	// Draw the horizontal lines.  

	MoveToEx(hdc, (rect.right / 2 - 150), (rect.bottom / 2 + 0), NULL);
	LineTo(hdc, (rect.right / 2 - 16), (rect.bottom / 2 + 0));

	MoveToEx(hdc, (rect.right / 2 - 13), (rect.bottom / 2 + 0), NULL);
	LineTo(hdc, (rect.right / 2 + 13), (rect.bottom / 2 + 0));

	MoveToEx(hdc, (rect.right / 2 + 16), (rect.bottom / 2 + 0), NULL);
	LineTo(hdc, (rect.right / 2 + 150), (rect.bottom / 2 + 0));

	// Draw the vertical lines.  

	MoveToEx(hdc, (rect.right / 2 + 0), (rect.bottom / 2 - 150), NULL);
	LineTo(hdc, (rect.right / 2 + 0), (rect.bottom / 2 - 16));

	MoveToEx(hdc, (rect.right / 2 + 0), (rect.bottom / 2 - 13), NULL);
	LineTo(hdc, (rect.right / 2 + 0), (rect.bottom / 2 + 13));

	MoveToEx(hdc, (rect.right / 2 + 0), (rect.bottom / 2 + 16), NULL);
	LineTo(hdc, (rect.right / 2 + 0), (rect.bottom / 2 + 150));

	ReleaseDC(m_hwnd, hdc);
}

XFORM TransWindow::GetXFORM(int iTransform)
{
	XFORM xForm;

	switch (iTransform)
	{
	case SCALE:        // Scale to 1/2 of the original size.  
		xForm.eM11 = (FLOAT) 0.5;
		xForm.eM12 = (FLOAT) 0.0;
		xForm.eM21 = (FLOAT) 0.0;
		xForm.eM22 = (FLOAT) 0.5;
		xForm.eDx = (FLOAT) 0.0;
		xForm.eDy = (FLOAT) 0.0;
		//SetWorldTransform(hdc, &xForm);
		break;

	case TRANSLATE:   // Translate right by 3/4 inch.  
		xForm.eM11 = (FLOAT) 1.0;
		xForm.eM12 = (FLOAT) 0.0;
		xForm.eM21 = (FLOAT) 0.0;
		xForm.eM22 = (FLOAT) 1.0;
		xForm.eDx = (FLOAT) 75.0;
		xForm.eDy = (FLOAT) 0.0;
		//SetWorldTransform(hdc, &xForm);
		break;

	case ROTATE:      // Rotate 30 degrees counterclockwise.  
		xForm.eM11 = (FLOAT) 0.8660;
		xForm.eM12 = (FLOAT) 0.5000;
		xForm.eM21 = (FLOAT)-0.5000;
		xForm.eM22 = (FLOAT) 0.8660;
		xForm.eDx = (FLOAT) 0.0;
		xForm.eDy = (FLOAT) 0.0;
		//SetWorldTransform(hdc, &xForm);
		break;

	case SHEAR:       // Shear along the x-axis with a  
		// proportionality constant of 1.0.  
		xForm.eM11 = (FLOAT) 1.0;
		xForm.eM12 = (FLOAT) 1.0;
		xForm.eM21 = (FLOAT) 0.0;
		xForm.eM22 = (FLOAT) 1.0;
		xForm.eDx = (FLOAT) 0.0;
		xForm.eDy = (FLOAT) 0.0;
		//SetWorldTransform(hdc, &xForm);
		break;

	case REFLECT:     // Reflect about a horizontal axis.  
		xForm.eM11 = (FLOAT) 1.0;
		xForm.eM12 = (FLOAT) 0.0;
		xForm.eM21 = (FLOAT) 0.0;
		xForm.eM22 = (FLOAT)-1.0;
		xForm.eDx = (FLOAT) 0.0;
		xForm.eDy = (FLOAT) 0.0;
		//SetWorldTransform(hdc, &xForm);
		break;

	case NORMAL:      // Set the unity transformation.  
		xForm.eM11 = (FLOAT) 1.0;
		xForm.eM12 = (FLOAT) 0.0;
		xForm.eM21 = (FLOAT) 0.0;
		xForm.eM22 = (FLOAT) 1.0;
		xForm.eDx = (FLOAT) 0.0;
		xForm.eDy = (FLOAT) 0.0;
		//SetWorldTransform(hdc, &xForm);
		break;
	}

	return xForm;
}
