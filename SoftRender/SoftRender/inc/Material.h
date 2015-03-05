#ifndef Material_h
#define Material_h

class CheckerMaterial
{
private:
	double scale;

public:
	CheckerMaterial() = default;
	~CheckerMaterial() = default;

	CheckerMaterial(double s) : scale(s) {}

	Color sample(Ray3 ray, Vec3 position, Vec3 normal) {
		Color color;
		if ((abs((int)(floor(position.getx() * 0.1) + floor(position.getz() * scale)) % 2)) < 1)
			return color.getColor(Color_BLACK);
		return color.getColor(Color_WHITE);
	}

};

class PhongMaterial
{
public:
	PhongMaterial();
	~PhongMaterial();

private:
	
};

#endif