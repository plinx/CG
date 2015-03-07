#ifndef Color_h
#define Color_h

enum {
	Color_BLACK = 0,
	Color_WHITE,
	Color_RED,
	Color_GREEN,
	Color_BLUE,
	Color_YELLOW
};

class Color
{
private:
	double R, G, B;

public:
	Color() = default;
	~Color() = default;

	Color(double r, double g, double b) : R(r), G(g), B(b) {}

	const double getR() { return R > 1 ? 1 : R; }
	const double getG() { return G > 1 ? 1 : G; }
	const double getB() { return B > 1 ? 1 : B; }

	Color copy() { return Color(R, G, B); }
	Color add(Color c) { return Color(R + c.R, G + c.G, B + c.B); }
	Color mul(double s) { return Color((double)(R * s), (double)(G * s), (double)(B * s)); }
	Color modulate(Color c) { return Color(R * c.R, G * c.G, B * c.B); }

};

inline Color getColor(int s) {
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
	case Color_YELLOW:
		return Color(1, 1, 0);
	default:
		return Color(0, 0, 0);
	}
}

#endif