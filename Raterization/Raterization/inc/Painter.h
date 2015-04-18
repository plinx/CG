#ifndef Painter_h
#define Painter_h

class Painter
{
public:
	PBYTE _scanLine;

	// Constructor
	Painter() = default;

	void init(int width, int height);

	// basic methods
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
	void _drawFlatBottomTriangle(double x1, double y1,
		double x2, double y2, double x3, double y3, Color& color);
	void _drawFlatTopTriangle(double x1, double y1,
		double x2, double y2, double x3, double y3, Color& color);
	void _drawFlatBottomTriangle(double x1, double y1, Color& c1,
		double x2, double y2, Color& c2, double x3, double y3, Color& c3);
	void _drawFlatTopTriangle(double x1, double y1, Color& c1,
		double x2, double y2, Color& c2, double x3, double y3, Color& c3);

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
	int tmpA = color.A;
	_pixel = _scanLine + _bytePerLine * (y);
	_pixel += x1 * 4;
	for (int x = x1; x < x2; x++)
	{
		_setColor(_pixel, color);
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
		_pixel += 4;
	}
}

inline void Painter::drawTriangle(double x1, double y1,
	double x2, double y2, double x3, double y3, Color& color)
{
	double clip_x, clip_y;

	if (ceil(x1) == ceil(x2) && ceil(x2) == ceil(x3) 
		|| ceil(y1) == ceil(y2) && ceil(y2) == ceil(y3))
		return;

	if (y2 < y1)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	if (y3 < y1)
	{
		std::swap(x1, x3);
		std::swap(y1, y3);
	}

	if (y3 < y2)
	{
		std::swap(x2, x3);
		std::swap(y2, y3);
	}

	if (y1 > _height || y3 < 0 ||
		(x1 < 0 && x2 < 0 && x3 < 0) ||
		(x1 > _width && x2 > _width && x3 > _width))
		return;
	

	clip_y = y2;
	clip_x = x1 + (x3 - x1) * (clip_y - y1) / (y3 - y1);
	if (x1 < x2)
	{
		_drawFlatBottomTriangle(clip_x, clip_y, x2, y2, x3, y3, color);
		_drawFlatTopTriangle(x1, y1, clip_x, clip_y, x2, y2, color);
	}
	else
	{
		_drawFlatBottomTriangle(x2, y2, clip_x, clip_y, x3, y3, color);
		_drawFlatTopTriangle(x1, y1, x2, y2, clip_x, clip_y, color);
	}
}
	
inline void Painter::drawTriangle(double x1, double y1, Color& c1,
	double x2, double y2, Color& c2, double x3, double y3, Color& c3)
{
	Color clip_color;
	double clip_x, clip_y;

	if (ceil(x1) == ceil(x2) && ceil(x2) == ceil(x3)
		|| ceil(y1) == ceil(y2) && ceil(y2) == ceil(y3))
		return;

	if (y2 < y1)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	if (y3 < y1)
	{
		std::swap(x1, x3);
		std::swap(y1, y3);
	}

	if (y3 < y2)
	{
		std::swap(x2, x3);
		std::swap(y2, y3);
	}

	if (y1 > _height || y3 < 0 ||
		(x1 < 0 && x2 < 0 && x3 < 0) ||
		(x1 > _width && x2 > _width && x3 > _width))
		return;


	clip_y = y2;
	clip_x = x1 + (x3 - x1) * (clip_y - y1) / (y3 - y1);
	clip_color = c1 + (c3 - c1).mul((clip_y - y1) / (y3 - y1));
	if (x1 < x2)
	{
		_drawFlatBottomTriangle(clip_x, clip_y, clip_color, x2, y2, c2, x3, y3, c3);
		_drawFlatTopTriangle(x1, y1, c1, clip_x, clip_y, clip_color, x2, y2, c3);
	}
	else
	{
		_drawFlatBottomTriangle(x2, y2, c2, clip_x, clip_y, clip_color, x3, y3, c3);
		_drawFlatTopTriangle(x1, y1, c1, x2, y2, c2, clip_x, clip_y, clip_color);
	}
}

inline void Painter::_drawFlatBottomTriangle(double x1, double y1,
	double x2, double y2, double x3, double y3, Color& color)
{
	double delta_left, delta_right;
	double scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = _height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;
	
	delta_left = (x3 - x1) / (y3 - y1);
	delta_right = (x3 - x2) / (y3 - y2);

	for (double y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x2 + delta_right * (y - y2);
		if (scan_left < 0) 
			scan_left = 0;
		if (scan_right > _width)
			scan_right = _width;

		drawHorizonLine((int)ceil(scan_left), (int)ceil(scan_right), (int)ceil(y), color);
	}
}

inline void Painter::_drawFlatTopTriangle(double x1, double y1,
	double x2, double y2, double x3, double y3, Color& color)
{
	double delta_left, delta_right;
	double scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = _height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;

	delta_left = (x2 - x1) / (y2 - y1);
	delta_right = (x3 - x1) / (y3 - y1);

	for (double y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x1 + delta_right * (y - y1);
		if (scan_left < 0)
			scan_left = 0;
		if (scan_right > _width)
			scan_right = _width;

		drawHorizonLine((int)ceil(scan_left), (int)ceil(scan_right), (int)ceil(y), color);
	}
}

inline void Painter::_drawFlatBottomTriangle(double x1, double y1, Color& c1,
	double x2, double y2, Color& c2, double x3, double y3, Color& c3)
{
	Color delta_lcolor, delta_rcolor;
	double vertical_div, delta_left, delta_right;
	double scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = _height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;

	vertical_div = 1 / (y3 - y1);
	delta_left = (x3 - x1) * vertical_div;
	delta_right = (x3 - x2) * vertical_div;
	delta_lcolor = c3 - c1;
	delta_rcolor = c3 - c2;

	for (double y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x2 + delta_right * (y - y2);
		if (scan_left < 0)
			scan_left = 0;
		if (scan_right > _width)
			scan_right = _width;

		// Color operator* operator/ must put the double value on rhs
		drawHorizonLine((int)ceil(scan_left), (int)ceil(scan_right), 
			(int)ceil(y), c1 + delta_lcolor.mul((y - y1) * vertical_div), c2 + delta_rcolor.mul((y - y2) * vertical_div));
	}
}
inline void Painter::_drawFlatTopTriangle(double x1, double y1, Color& c1,
	double x2, double y2, Color& c2, double x3, double y3, Color& c3)
{
	Color delta_lcolor, delta_rcolor;
	double vertical_div, delta_left, delta_right;
	double scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = _height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;
	
	vertical_div = 1 / (y3 - y1);
	delta_left = (x2 - x1) / (y2 - y1);
	delta_right = (x3 - x1) / (y3 - y1);
	delta_lcolor = (c2 - c1);
	delta_rcolor = (c3 - c1);

	for (double y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x1 + delta_right * (y - y1);
		if (scan_left < 0)
			scan_left = 0;
		if (scan_right > _width)
			scan_right = _width;

		// Color operator* operator/ must put the double value on rhs
		drawHorizonLine((int)ceil(scan_left), (int)ceil(scan_right),
			(int)ceil(y), c1 + delta_lcolor.mul((y - y1) * vertical_div), c1 + delta_rcolor.mul((y - y1) * vertical_div));
	}
}

#endif