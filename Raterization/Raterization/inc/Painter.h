#ifndef Painter_h
#define Painter_h

class Painter
{
public:
	PBYTE _scanLine;

	Painter() = default;

	void init(int width, int height);

	// draw functions
	void drawPixel(int x, int y, Color& color = Color(0, 0, 0));
	void drawLine(int x1, int y1, int x2, int y2, Color& color = Color(0, 0, 0));
	void drawVerticalLine(int x, int y1, int y2, Color& color = Color(0, 0, 0));
	void drawHorizonLine(int x1, int x2, int y, Color& color);
	void drawHorizonLine(int x1, int x2, int y, Color& left, Color& right);
	void drawTriangle(double x1, double y1,
		double x2, double y2, double x3, double y3, Color& color);
	void drawTriangle(double x1, double y1, Color& c1, 
		double x2, double y2, Color& c2, double x3, double y3, Color& c3);

protected:
	void _setColor(PBYTE& pixel, Color& color);

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

inline void Painter::_setColor(PBYTE& pixel, Color& color)
{
	// 32 bit color format : Blue, Green, Red, Alpha
	pixel[0] = color.B;
	pixel[1] = color.G;
	pixel[2] = color.R;
	pixel[3] = color.A;
}

inline void Painter::drawPixel(int x, int y, Color& color)
{
	_pixel = _scanLine + _bytePerLine * (y);
	_pixel += x * 4;
	_setColor(_pixel, color);
	// 32 bit color format : Blue, Green, Red, Alpha
	/*_pixel[0] = color.B;
	_pixel[1] = color.G;
	_pixel[2] = color.R;
	_pixel[3] = color.A;*/
}
	
inline void Painter::drawLine(int x1, int y1, int x2, int y2, Color& color)
{
	float delta;
	if (x1 != x2)
		delta = (float)(y2 - y1) / (x2 - x1);
	else
		drawVerticalLine(x1, y1, y2, color);

	for (int x = 0, y = y1; x < abs(x2 - x1); x++)
	{
		drawPixel(x + x1, y, color);
		y = (int)(x * delta + y1);
	}
}

inline void Painter::drawVerticalLine(int x, int y1, int y2, Color& color)
{
	for (int y = y1; y < y2; y++)
	{
		drawPixel(x, y, color);
	}
}

inline void Painter::drawHorizonLine(int x1, int x2, int y, Color& color)
{
	_pixel = _scanLine + _bytePerLine * (y);
	_pixel += x1 * 4;
	for (int x = x1; x < x2; x++)
	{
		_setColor(_pixel, color);
		// 32 bit color format : Blue, Green, Red, Alpha
		/*_pixel[0] = (BYTE)(left.B + delta.B * x * len_div);
		_pixel[1] = (BYTE)(left.G + delta.G * x * len_div);
		_pixel[2] = (BYTE)(left.R + delta.R * x * len_div);
		_pixel[3] = (BYTE)(left.A + delta.A * x * len_div);*/
		_pixel += 4;
	}
}

inline void Painter::drawHorizonLine(int x1, int x2, int y, Color& left, Color& right)
{
	_pixel = _scanLine + _bytePerLine * (y);
	int len = abs(x2 - x1);
	double len_div = 1 / (double)len;
	Color delta(left, right);
	Color tmp;
	_pixel += x1 * 4;
	for (int x = 0; x < len; x++)
	{
		tmp.init((BYTE)(left.R + delta.R * x * len_div),
			(BYTE)(left.G + delta.G * x * len_div),
			(BYTE)(left.B + delta.B * x * len_div),
			(BYTE)(left.A + delta.A * x * len_div));
		_setColor(_pixel, tmp);
		// 32 bit color format : Blue, Green, Red, Alpha
		/*_pixel[0] = (BYTE)(left.B + delta.B * x * len_div);
		_pixel[1] = (BYTE)(left.G + delta.G * x * len_div);
		_pixel[2] = (BYTE)(left.R + delta.R * x * len_div);
		_pixel[3] = (BYTE)(left.A + delta.A * x * len_div);*/
		_pixel += 4;
	}
}

inline void Painter::drawTriangle(double x1, double y1,
	double x2, double y2, double x3, double y3, Color& color)
{
	if (ceil(x1) == ceil(x2) && ceil(x2) == ceil(x3))
	{
		drawVerticalLine((int)ceil(x1), (int)ceil(min(y1, min(y2, y3))), (int)ceil(max(y1, max(y2, y3))), color);
		return;
	}
	else if (ceil(y1) == ceil(y2) && ceil(y2) == ceil(y3))
	{
		drawHorizonLine((int)ceil(min(x1, min(x2, x3))), (int)ceil(max(x1, max(x2, x3))), (int)ceil(y1), color);
		return;
	}
	
	double delta_a = (y2 - y1) / (x2 - x1);
	double delta_b = (y3 - y2) / (x3 - x2);
	if (delta_a == delta_b || delta_a == -delta_b)
	{
		drawLine((int)ceil(min(x1, min(x2, x3))), (int)ceil(min(y1, min(y2, y3))),
			(int)ceil(max(x1, max(x2, x3))), (int)ceil(max(y1, max(y2, y3))), color);
	}
}
	
inline void Painter::drawTriangle(double x1, double y1, Color& c1,
	double x2, double y2, Color& c2, double x3, double y3, Color& c3)
{

}

#endif