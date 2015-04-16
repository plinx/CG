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
	void _drawFlatBottomTriangle(double x1, double y1,
		double x2, double y2, double x3, double y3, Color& color);
	void _drawFlatTopTriangle(double x1, double y1,
		double x2, double y2, double x3, double y3, Color& color);

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
	double clip_x1, clip_x2, clip_y1, clip_y2;

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
	
	if (ceil(y1) == ceil(y2))
	{
		if (y3 > _height) // vertical top clip
		{
			clip_y1 = clip_y2 = _height;
			clip_x1 = x1 + (x3 - x1) * (clip_y1 - y1) / (y3 - y1);
			clip_x2 = x2 + (x3 - x2) * (clip_y2 - y2) / (y3 - y2);
			drawTriangle(x1, y1, clip_x1, clip_y1, x2, y2, color);
			drawTriangle(clip_x1, clip_y1, clip_x2, clip_y2, x2, y2, color);
		}
		else if (y1 < 0)
		{
			clip_y1 = clip_y2 = 0;
			clip_x1 = x1 + (x3 - x1) * (-y1) / (y3 - y1);
			clip_x2 = x2 + (x3 - x2) * (-y2) / (y3 - y2);
			drawTriangle(clip_x1, clip_y1, clip_x2, clip_y2, x3, y3, color);
		}
		else
		{
			_drawFlatBottomTriangle(x1, y2, x2, y2, x3, y3, color);
		}
	}
	else if (ceil(y2) == ceil(y3))
	{
		if (y1 < 0)
		{
			clip_y1 = clip_y2 = 0;
			clip_x1 = x1 + (x2 - x1) * (-y1) / (y2 - y1);
			clip_x2 = x1 + (x3 - x1) * (-y1) / (y3 - y1);
			drawTriangle(clip_x1, clip_y1, x2, y2, x3, y3, color);
			drawTriangle(clip_x1, clip_y1, x3, y3, clip_x2, clip_y2, color);
		}
		else if (y2 > _height)
		{
			clip_y1 = clip_y2 = _height;
			clip_x1 = x1 + (x2 - x1) * (clip_y1 - y1) / (y2 - y1);
			clip_x2 = x1 + (x3 - x1) * (clip_y2 - y1) / (y3 - y1);
			drawTriangle(x1, y1, clip_x1, clip_y1, clip_x2, clip_y2, color);
		}
		else
		{
			_drawFlatTopTriangle(x1, y1, x2, y2, x3, y3, color);
		}
	}
	else
	{

	}
}
	
inline void Painter::drawTriangle(double x1, double y1, Color& c1,
	double x2, double y2, Color& c2, double x3, double y3, Color& c3)
{

}

inline void Painter::_drawFlatBottomTriangle(double x1, double y1,
	double x2, double y2, double x3, double y3, Color& color)
{
	double delta_left, delta_right;
	double left_x, right_x, height;

	if (x2 < x1)
	{
		std::swap(x2, x1);
	}

	height = y3 - y1;
	delta_left = (x3 - x1) / height;
	delta_right = (x3 - x2) / height;

	for (double y = 0; y < height; y++)
	{
		left_x = x1 + delta_left * y;
		right_x = x2 + delta_right * y;
		drawHorizonLine((int)ceil(left_x), (int)ceil(right_x), (int)ceil(y + y1), color);
	}
}

inline void Painter::_drawFlatTopTriangle(double x1, double y1,
	double x2, double y2, double x3, double y3, Color& color)
{
	double delta_left, delta_right;
	double left_x, right_x, height;

	if (x3 < x2)
	{
		std::swap(x3, x2);
	}

	height = y3 - y1;
	delta_left = (x2 - x1) / height;
	delta_right = (x3 - x1) / height;

	for (double y = 0; y < height; y++)
	{
		left_x = x1 + delta_left * y;
		right_x = x1 + delta_right * y;
		drawHorizonLine((int)ceil(left_x), (int)ceil(right_x), (int)ceil(y + y1), color);
	}
}

#endif