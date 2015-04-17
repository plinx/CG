#ifndef Color_h
#define Color_h

enum ColorStyle
{
	White = 0, Black, Red, Green, Blue, Yellow, Cyan, Megenta
};

struct Color
{
	int R, G, B, A;

	Color() = default;
	~Color() = default;
	Color(int r, int g, int b) : R(r), G(g), B(b), A(255) {}
	Color(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}
	Color(ColorStyle style);
	Color(Color& left, Color& right);

	void init(int r, int g, int b) { R = r; G = g; B = b; A = 255; }
	void init(int r, int g, int b, int a) { R = r; G = g; B = b; A = a; }
	void reset() { R = 0; G = 0; B = 0; A = 255; }
	void alpha(int alpha) { A = alpha; }
	Color mul(double scale);

	Color& operator=(Color& rhs);
	Color operator+(Color& rhs);
	Color operator-(Color& rhs);
};

inline Color::Color(ColorStyle style)
{
	switch (style)
	{
	case White:
		R = 255; G = 255; B = 255; A = 255; break;
	case Black:
		R = 0; G = 0; B = 0; A = 255; break;
	case Red:
		R = 255; G = 0; B = 0; A = 255; break;
	case Green:
		R = 0; G = 255; B = 0; A = 255; break;
	case Blue:
		R = 0; G = 0; B = 255; A = 255; break;
	case Yellow:
		R = 255; G = 255; B = 0; A = 255; break;
	case Cyan:
		R = 255; G = 0; B = 255; A = 255; break;
	case Megenta:
		R = 0; G = 255; B = 255; A = 255; break;
	default:
		R = 0; G = 0; B = 0; A = 255; break;
	}
}

inline Color::Color(Color& left, Color& right)
{
	R = right.R - left.R;
	G = right.G - left.G;
	B = right.B - left.B;
	A = right.A - left.A;
}

inline Color Color::mul(double scale)
{
	Color tmpColor;
	tmpColor.R = (int)(R * scale);
	tmpColor.G = (int)(G * scale);
	tmpColor.B = (int)(B * scale);
	tmpColor.A = 255;
	return tmpColor;
}

inline Color& Color::operator=(Color& rhs)
{
	R = rhs.R; G = rhs.G; B = rhs.B; A = rhs.A;
	return *this;
}

inline Color Color::operator+(Color& rhs)
{
	Color tmpColor;
	tmpColor.R = R + rhs.R;
	tmpColor.G = G + rhs.G;
	tmpColor.B = B + rhs.B;
	tmpColor.A = 255;
	return tmpColor;
}

inline Color Color::operator-(Color& rhs)
{
	Color tmpColor;
	tmpColor.R = R - rhs.R;
	tmpColor.G = G - rhs.G;
	tmpColor.B = B - rhs.B;
	tmpColor.A = 255;
	return tmpColor;
}

#endif