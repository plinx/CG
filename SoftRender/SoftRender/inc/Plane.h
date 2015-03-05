#ifndef Plane_h
#define Plane_h

class Plane
{
private:
	Vec3 normal, position;
	double D;

public:
	Plane() = default;
	Plane(Vec3 n, double d) : normal(n), D(d) {}
	~Plane() = default;

	Plane copy() { return Plane(normal, D); }
	void initialize() { position = normal.mul(D); }
	IntersectResult intersect(Ray3 ray) {
		auto a = ray.direction.dot(normal);
		if (a >= 0)
			return IntersectResult();

		auto b = normal.dot(ray.origin.sub(position));
		auto result = IntersectResult();
		result.geometry = true;
		result.distance = -b / a;
		result.position = ray.getPoint(result.distance);
		result.normal = normal;

		return result;
		
	}

};

#endif