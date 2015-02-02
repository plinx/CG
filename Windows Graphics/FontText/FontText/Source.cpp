#include <strsafe.h>
#include "win.h"


class FontWindow : public LWindow
{
	void OnDraw(HDC hdc);
	HFONT FAR PASCAL LogicalFont(void);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	FontWindow win;

	win.Create(640, 480, hInstance);
	win.ShowWindow(iCmdShow);
	win.UpdateWindow();

	return win.MessageLoop();
}

void FontWindow::OnDraw(HDC hdc)
{
	const TCHAR szTest[] = TEXT("ANSI_VAR_FONT text");
	HFONT hFont, hOldFont;

	hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
	hOldFont = (HFONT)SelectObject(hdc, hFont);
	TextOut(hdc, 10, 10, szTest, lstrlen(szTest));
	SelectObject(hdc, hOldFont);

	hFont = LogicalFont();
	hOldFont = (HFONT)SelectObject(hdc, hFont);
	TextOut(hdc, 10, 30, szTest, lstrlen(szTest));
	SelectObject(hdc, hOldFont);

	RECT rc;
	int angle;
	HGDIOBJ hfnt, hfntPrev;
	HRESULT hr;
	size_t pcch = 22;

	// Allocate memory for a LOGFONT structure. 

	PLOGFONT plf = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));


	// Specify a font typeface name and weight. 

	hr = StringCchCopy(plf->lfFaceName, 6, TEXT("Arial"));
	if (FAILED(hr))
	{
		// TODO: write error handler
	}

	plf->lfWeight = FW_NORMAL;

	// Retrieve the client-rectangle dimensions. 

	GetClientRect(m_hwnd, &rc);

	// Set the background mode to transparent for the 
	// text-output operation. 

	SetBkMode(hdc, TRANSPARENT);

	// Draw the string 36 times, rotating 10 degrees 
	// counter-clockwise each time. 

	for (angle = 0; angle < 3600; angle += 100)
	{
		plf->lfEscapement = angle;
		hfnt = CreateFontIndirect(plf);
		hfntPrev = SelectObject(hdc, hfnt);

		//
		// The StringCchLength call is fitted to the lpszRotate string
		//
		hr = StringCchLength(szTest, 22, &pcch);
		if (FAILED(hr))
		{
			// TODO: write error handler
		}
		TextOut(hdc, rc.right / 2, rc.bottom / 2,
			szTest, pcch);
		SelectObject(hdc, hfntPrev);
		DeleteObject(hfnt);
	}

	// Reset the background mode to its default. 

	SetBkMode(hdc, OPAQUE);

	// Free the memory allocated for the LOGFONT structure. 

	LocalFree((LOCALHANDLE)plf);
}

HFONT FAR PASCAL FontWindow::LogicalFont(void)
{
	CHOOSEFONT cFont;
	LOGFONT lFont;
	HFONT hFont;

	cFont.lStructSize = sizeof(CHOOSEFONT);
	cFont.hwndOwner = (HWND)NULL;
	cFont.hDC = (HDC)NULL;
	cFont.lpLogFont = &lFont;
	cFont.Flags = CF_SCREENFONTS;
	cFont.rgbColors = RGB(0, 0, 255);
	cFont.lCustData = 0L;
	cFont.lpfnHook = (LPCFHOOKPROC)NULL;
	cFont.lpTemplateName = (LPSTR)NULL;
	cFont.hInstance = (HINSTANCE)NULL;
	cFont.lpszStyle = (LPSTR)NULL;
	cFont.nFontType = SCREEN_FONTTYPE;
	cFont.nSizeMin = 0;
	cFont.nSizeMax = 0;

	ChooseFont(&cFont);
	hFont = CreateFontIndirect(cFont.lpLogFont);
	
	return hFont;
}
