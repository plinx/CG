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

	void drawTriangle(float x1, float y1,
		float x2, float y2, float x3, float y3, Color& color);
	void drawTriangle(float x1, float y1, Color& c1, 
		float x2, float y2, Color& c2, float x3, float y3, Color& c3);

protected:
	void _drawFlatBottomTriangle(float x1, float y1,
		float x2, float y2, float x3, float y3, Color& color);
	void _drawFlatTopTriangle(float x1, float y1,
		float x2, float y2, float x3, float y3, Color& color);
	void _drawFlatBottomTriangle(float x1, float y1, Color& c1,
		float x2, float y2, Color& c2, float x3, float y3, Color& c3);
	void _drawFlatTopTriangle(float x1, float y1, Color& c1,
		float x2, float y2, Color& c2, float x3, float y3, Color& c3);

	void _setColor(PBYTE& pixel, Color& color);

private:
	~Painter() = default;

	int _width, _height, _bytesPerLine;
	PBYTE _pixel;
};

inline void Painter::init(int width, int height)
{
	_width = width;
	_height = height;
	_bytesPerLine = _width * 3;
	if (_bytesPerLine % 4 != 0)
		_bytesPerLine += 4 - _bytesPerLine % 4;
}

inline void Painter::_setColor(PBYTE& pixel, Color& color)
{
	// 32 bit color format : Blue, Green, Red, Alpha
	pixel[0] = color.B;
	pixel[1] = color.G;
	pixel[2] = color.R;
	//pixel[3] = color.A;
}

inline void Painter::drawPixel(int x, int y, Color& color)
{
	if (y < 0 || y > _height) return;
	if (x < 0 || x > _width) return;
	_pixel = _scanLine + _bytesPerLine * (y);
	_pixel += x * 3;
	_setColor(_pixel, color);
}

inline void Painter::drawLine(int x1, int y1, int x2, int y2, Color& color)
{
	float delta;
	if (y1 == y2)
	{
		if (x2 < x1) std::swap(x1, x2);
		if (x1 > _width || x2 < 0) return;
		drawHorizonLine(x1, x2, y1, color);
	}
	else if (x1 == x2)
	{
		drawVerticalLine(x1, y1, y2, color);
	}
	else
	{
		if (y2 < y1)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			if (x1 > _width || x2 < 0) return;
		}
		if (abs(y2 - y1) > abs(x2 - x1))
		{
			delta = (float)(x2 - x1) / (y2 - y1);
			for (int y = 0; y < (y2 - y1); y++)
			{
				drawPixel((int)(x1 + delta * y), y + y1, color);
			}
		}
		else
		{
			float left = 0;
			float right = (float)abs(x1 - x2);
			if (x2 < x1)
			{
				delta = (float)(y1 - y2) / (x1 - x2);
				if (y1 < 0)
					right = (float)(-y2) * (x1 - x2) / (y1 - y2);
				if (y2 > _height)
					left = (float)(_height - y2) * (x1 - x2) / (y1 - y2);
				
				for (int x = (int)left; x < (int)right; x++)
				{
					drawPixel(x + x2, (int)(y2 + delta * x), color);
				}
			}
			else
			{
				delta = (float)(y2 - y1) / (x2 - x1);
				if (y1 < 0)
					left = (float)(-y1) * (x2 - x1) / (y2 - y1);
				if (y2 > _height)
					right = (float)(_height - y1) * (x2 - x1) / (y2 - y1);

				for (int x = (int)left; x < (int)right; x++)
				{
					drawPixel(x + x1, (int)(y1 + delta * x), color);
				}
			}
		}
	}
	
}

inline void Painter::drawVerticalLine(int x, int y1, int y2, Color& color)
{
	if (x < 0 || x > _width) return;
	if (y2 < y1) std::swap(y1, y2);
	if (y1 < 0) y1 = 0;
	if (y2 > _height) y2 = _height;
	for (int y = y1; y < y2; y++)
	{
		drawPixel(x, y, color);
	}
}

inline void Painter::drawHorizonLine(int x1, int x2, int y, Color& color)
{
	if (y < 0 || y > _height) return;
	// the judge put in _drawFlatBottomTriangle and _drawFlatTopTriangle
	if (x2 < x1)
		std::swap(x1, x2);
	if (x1 < 0) x1 = 0;
	if (x2 > _width) x2 = _width;
	int tmpA = color.A;
	_pixel = _scanLine + _bytesPerLine * (y);
	_pixel += x1 * 3;
	for (int x = x1; x < x2; x++)
	{
		_setColor(_pixel, color);
		_pixel += 3;
	}
}

inline void Painter::drawHorizonLine(int x1, int x2, int y, Color& left, Color& right)
{
	if (y < 0 || y > _height) return;
	if (x1 < 0) x1 = 0;
	if (x2 > _width) x2 = _width;

	_pixel = _scanLine + _bytesPerLine * (y);
	int len = abs(x2 - x1);
	float len_div = 1 / (float)len;
	Color delta(left, right);
	Color tmp;
	// the judge put in _drawFlatBottomTriangle and _drawFlatTopTriangle
	/*if (x2 < x1)
	{
		std::swap(x1, x2);
		std::swap(left, right);
	}*/
	_pixel += x1 * 3;
	for (int x = 0; x < len; x++)
	{
		tmp.init((BYTE)(left.R + delta.R * x * len_div),
			(BYTE)(left.G + delta.G * x * len_div),
			(BYTE)(left.B + delta.B * x * len_div),
			(BYTE)(left.A + delta.A * x * len_div));
		_setColor(_pixel, tmp);
		_pixel += 3;
	}
}

inline void Painter::drawTriangle(float x1, float y1,
	float x2, float y2, float x3, float y3, Color& color)
{
	float clip_x, clip_y;

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
	
inline void Painter::drawTriangle(float x1, float y1, Color& c1,
	float x2, float y2, Color& c2, float x3, float y3, Color& c3)
{
	Color clip_color;
	float clip_x, clip_y;

	if (ceil(x1) == ceil(x2) && ceil(x2) == ceil(x3)
		|| ceil(y1) == ceil(y2) && ceil(y2) == ceil(y3))
		return;

	if (y2 < y1)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
		std::swap(c1, c2);
	}

	if (y3 < y1)
	{
		std::swap(x1, x3);
		std::swap(y1, y3);
		std::swap(c1, c3);
	}

	if (y3 < y2)
	{
		std::swap(x2, x3);
		std::swap(y2, y3);
		std::swap(c2, c3);
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
		_drawFlatTopTriangle(x1, y1, c1, clip_x, clip_y, clip_color, x2, y2, c2);
	}
	else
	{
		_drawFlatBottomTriangle(x2, y2, c2, clip_x, clip_y, clip_color, x3, y3, c3);
		_drawFlatTopTriangle(x1, y1, c1, x2, y2, c2, clip_x, clip_y, clip_color);
	}
}

inline void Painter::_drawFlatBottomTriangle(float x1, float y1,
	float x2, float y2, float x3, float y3, Color& color)
{
	float delta_left, delta_right;
	float scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = (float)_height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;

	if (x2 < x1)
		std::swap(x1, x2);
	
	delta_left = (x3 - x1) / (y3 - y1);
	delta_right = (x3 - x2) / (y3 - y2);

	for (float y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x2 + delta_right * (y - y2);
		if (scan_left < 1) 
			scan_left = 1;
		if (scan_right > _width - 1)
			scan_right = (float)(_width - 1);

		//drawHorizonLine((int)ceil(scan_left), (int)ceil(scan_right), (int)ceil(y), color);
		drawHorizonLine((int)(scan_left - 1), (int)(scan_right + 1), (int)(y), color);
	}
}

inline void Painter::_drawFlatTopTriangle(float x1, float y1,
	float x2, float y2, float x3, float y3, Color& color)
{
	float delta_left, delta_right;
	float scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = (float)_height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;

	if (x3 < x2)
		std::swap(x2, x3);

	delta_left = (x2 - x1) / (y2 - y1);
	delta_right = (x3 - x1) / (y3 - y1);

	for (float y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x1 + delta_right * (y - y1);
		if (scan_left < 1)
			scan_left = 1;
		if (scan_right > _width - 1)
			scan_right = (float)(_width - 1);

		//drawHorizonLine((int)ceil(scan_left), (int)ceil(scan_right), (int)ceil(y), color);
		drawHorizonLine((int)(scan_left - 1), (int)(scan_right + 1), (int)(y), color);
	}
}

inline void Painter::_drawFlatBottomTriangle(float x1, float y1, Color& c1,
	float x2, float y2, Color& c2, float x3, float y3, Color& c3)
{
	Color lcolor, rcolor, delta_lcolor, delta_rcolor;
	float vertical_div, delta_left, delta_right;
	float scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = (float)_height;
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;

	if (x2 < x1)
	{
		std::swap(x1, x2);
		lcolor = c2;
		rcolor = c1;
	}
	else
	{
		lcolor = c1;
		rcolor = c2;
	}

	vertical_div = 1 / (y3 - y1);
	delta_left = (x3 - x1) * vertical_div;
	delta_right = (x3 - x2) * vertical_div;
	delta_lcolor = c3 - lcolor;
	delta_rcolor = c3 - rcolor;

	for (float y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x2 + delta_right * (y - y2);
		if (scan_left < 1)
			scan_left = 1;
		if (scan_right > _width - 1)
			scan_right = (float)(_width - 1);

		if (scan_left > scan_right)
			continue;

		// Color operator* operator/ must put the float value on rhs
		//drawHorizonLine((int)(scan_left - 1), (int)(scan_right + 1), (int)(y), 
		//	c1 + delta_lcolor.mul((y - y1) / (y3 - y1)), c2 + delta_rcolor.mul((y - y2) / (y3 - y2)));
		drawHorizonLine((int)(scan_left - 1), (int)(scan_right + 1), (int)(y), 
			lcolor + delta_lcolor.mul((y - y1) / (y3 - y1)), rcolor + delta_rcolor.mul((y - y2) / (y3 - y2)));
	}
}
inline void Painter::_drawFlatTopTriangle(float x1, float y1, Color& c1,
	float x2, float y2, Color& c2, float x3, float y3, Color& c3)
{
	Color lcolor, rcolor, delta_lcolor, delta_rcolor;
	float vertical_div, delta_left, delta_right;
	float scan_top, scan_bottom, scan_left, scan_right;

	if (y3 > _height)
		scan_top = (float)(_height);
	else
		scan_top = y3;

	if (y1 < 0)
		scan_bottom = 0;
	else
		scan_bottom = y1;

	if (x3 < x2)
	{
		std::swap(x2, x3);
		lcolor = c3;
		rcolor = c2;
	}
	else
	{
		lcolor = c2;
		rcolor = c3;
	}
	
	vertical_div = 1 / (y3 - y1);
	delta_left = (x2 - x1) * vertical_div;
	delta_right = (x3 - x1) * vertical_div;
	delta_lcolor = (lcolor - c1);
	delta_rcolor = (rcolor - c1);

	for (float y = scan_bottom; y < scan_top; y++)
	{
		scan_left = x1 + delta_left * (y - y1);
		scan_right = x1 + delta_right * (y - y1);
		if (scan_left < 1)
			scan_left = 1;
		if (scan_right > _width - 1)
			scan_right = (float)(_width - 1);
		if (scan_left > scan_right)
			continue;

		// Color operator* operator/ must put the float value on rhs
		drawHorizonLine((int)(scan_left - 1), (int)(scan_right + 1), (int)(y), 
			c1 + delta_lcolor.mul((y - y1) * vertical_div), c1 + delta_rcolor.mul((y - y1) * vertical_div));
	}
}

#endif