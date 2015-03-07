#ifndef Model_h
#define Model_h

class Model
{
public:
	Material* material;

public:
	Model() = default;
	~Model() = default;

	virtual Model copy() { return Model(); }
	virtual void initialize() {}
	virtual IntersectResult intersect(Ray3 ray) { return IntersectResult(); }
};

class Sphere : public Model
{
private:
	Vec3 center;
	double radius, sqrRadius;

public:
	Sphere() = default;
	~Sphere() = default;

	Sphere(Vec3 c, double r) : center(c), radius(r) {}
	Model copy() { return Sphere(center.copy(), radius); }
	void initialize() { sqrRadius = radius * radius; }
	
	IntersectResult intersect(Ray3 ray) {
		Vec3 v = ray.origin.sub(center);
		double a0 = v.sqrLength() - sqrRadius;
		double DdotV = ray.direction.dot(v);

		if (DdotV <= 0) {
			double discr = DdotV * DdotV - a0;
			if (discr >= 0) {
				IntersectResult result;
				result.geometry = true;
				result.distance = -DdotV - sqrt(discr);
				result.position = ray.getPoint(result.distance);
				result.normal = result.position.sub(center).normalize();
				result.material = material;

				return result;
			}
		}
		return IntersectResult();
	}


};

class Plane : public Model
{
public:
	Material* material;

private:
	Vec3 normal, position;
	double D;

public:
	Plane() = default;
	~Plane() = default;

	Plane(Vec3 n, double d) : normal(n), D(d) {}

	Model copy() { return Plane(normal, D); }
	void initialize() { position = normal.mul(D); }

	IntersectResult intersect(Ray3 ray) {
		auto a = ray.direction.dot(normal);
		if (a >= 0)
			return IntersectResult();

		auto b = normal.dot(ray.origin.sub(position));
		IntersectResult result;
		result.geometry = true;
		result.distance = -b / a;
		result.position = ray.getPoint(result.distance);
		result.normal = normal;
		result.material = material;

		return result;

	}

};

#endif