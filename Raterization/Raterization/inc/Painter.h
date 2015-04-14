#ifndef Painter_h
#define Painter_h

struct Color
{
	int R, G, B, A;

	Color() = default;
	~Color() = default;
	Color(int r, int g, int b) : R(r), G(g), B(b), A(255) {}
	Color(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}

	void init(int r, int g, int b) { R = r; G = g; B = b; A = 255; }
	void init(int r, int g, int b, int a) { R = r; G = g; B = b; A = a; }
	void reset() { R = 0; G = 0; B = 0; A = 255; }
};

class Painter
{
public:
	PBYTE _scanLine;

	Painter() = default;

	void init(int width, int height);

	// Draw functions
	void DrawPixel(int x, int y, Color& color = Color(0, 0, 0));
	void DrawLine(int x1, int y1, int x2, int y2, Color& color = Color(0, 0, 0));

private:
	~Painter() = default;

	int _width, _height, _bytePerLine;
	PBYTE _pixel;
};

inline void Painter::init(int width, int height)
{
	_width = width;
	_height = height;
	_bytePerLine = _width * 4;
}

inline void Painter::DrawPixel(int x, int y, Color& color)
{
	_pixel = _scanLine + _bytePerLine * (_width - x - 1);
	_pixel += y * 4;
	_pixel[0] = color.R;
	_pixel[1] = color.G;
	_pixel[2] = color.B;
	_pixel[3] = color.A;
}

#endif