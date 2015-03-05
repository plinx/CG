#ifndef Color_h
#define Color_h

enum {
	Color_BLACK = 0,
	Color_WHITE,
	Color_RED,
	Color_GREEN,
	Color_BLUE
};

class Color
{
private:
	BYTE R, G, B;

public:
	Color() = default;
	Color(BYTE r, BYTE g, BYTE b) : R(r), G(g), B(b) {}
	~Color() = default;

	const BYTE getR() { return R; }
	const BYTE getG() { return G; }
	const BYTE getB() { return B; }

	Color copy() { return Color(R, G, B); }
	Color add(Color c) { return Color(R + c.R, G + c.G, B + c.B); }
	Color mul(double s) { return Color((BYTE)(R * s), (BYTE)(G * s), (BYTE)(B * s)); }
	Color modulate(Color c) { return Color(R * c.R, G * c.G, B * c.B); }

	Color getColor(int s) {
		switch (s)
		{
		case Color_BLACK:
			return Color(0, 0, 0);
		case Color_WHITE:
			return Color(1, 1, 1);
		case Color_RED:
			return Color(1, 0, 0);
		case Color_GREEN:
			return Color(0, 1, 0);
		case Color_BLUE:
			return Color(0, 0, 1);
		default:
			return Color(0, 0, 0);
		}
	}

};

#endif