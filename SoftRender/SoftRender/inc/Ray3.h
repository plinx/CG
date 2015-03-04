#ifndef Ray3_h
#define Ray3_h

class Ray3
{
public:
	Vec3 origin, direction;

public:
	Ray3() = default;
	~Ray3() = default;

	Ray3(Vec3 o, Vec3 d) : origin(o), direction(d) {}
	Vec3 getPoint(double t) {
		return origin.add(direction.mul(t));
	}
};

#endif