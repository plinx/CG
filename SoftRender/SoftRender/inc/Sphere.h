#ifndef Sphere_h
#define Sphere_h

class Sphere
{
private:
	Vec3 center;
	double radius, sqrRadius;

public:
	Sphere() = default;
	~Sphere() = default;

	Sphere(Vec3 c, double r) : center(c), radius(r) {}
	Sphere copy() { return Sphere(center.copy(), radius); }
	void initialize() { sqrRadius = radius * radius; }
	
	IntersectResult intersect(Ray3 ray) {
		Vec3 v = ray.origin.sub(center);
		double a0 = v.sqrLength() - sqrRadius;
		double DdotV = ray.direction.dot(v);
		
		if (DdotV <= 0) {
			double discr = DdotV * DdotV - a0;
			if (discr >= 0) {
				IntersectResult result; // = IntersectResult();
				result.geometry = true;
				result.distance = -DdotV - sqrt(discr);
				result.position = ray.getPoint(result.distance);
				result.normal = result.position.sub(center).normalize();
				return result;
			}
		}
		return IntersectResult();
	}

};

#endif