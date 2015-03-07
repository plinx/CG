#ifndef Material_h
#define Material_h

class Material
{
public:
	double reflectiveness;
public:
	Material() = default;
	~Material() = default;

	virtual double getReflect() { return reflectiveness; }
	virtual Color sample(Ray3 ray, Vec3 position, Vec3 normal) { return getColor(Color_BLACK); }
};

class CheckerMaterial : public Material
{
public:
	double reflectiveness;
private:
	double scale;

public:
	CheckerMaterial() = default;
	~CheckerMaterial() = default;

	CheckerMaterial(double s) : scale(s), reflectiveness(0.0) {}
	CheckerMaterial(double s, double r) : scale(s), reflectiveness(r) {}
	
	double getReflect() { return reflectiveness; }
	Color sample(Ray3 ray, Vec3 position, Vec3 normal) {
		if ((abs((int)(floor(position.getx() * 0.1) + floor(position.getz() * scale)) % 2)) < 1)
			return getColor(Color_BLACK);
		return getColor(Color_WHITE);
	}
};

class PhongMaterial : public Material
{
public:
	double reflectiveness;
private:
	Color diffuse, specular;
	double shiness;

public:
	PhongMaterial() = default;
	~PhongMaterial() = default;
	
	double getReflect() { return reflectiveness; }
	PhongMaterial(Color diff, Color spec, double shin) :
		diffuse(diff), specular(spec), shiness(shin), reflectiveness(0.0) {}
	PhongMaterial(Color diff, Color spec, double shin, double refl) :
		diffuse(diff), specular(spec), shiness(shin), reflectiveness(refl) {}

	Color sample(Ray3 ray, Vec3 position, Vec3 normal) {
		auto lightDir = Vec3(1, 1, 1).normalize();
		auto lightColor = getColor(Color_WHITE);

		auto NdotL = normal.dot(lightDir);
		auto H = (lightDir.sub(ray.direction)).normalize();
		auto NdotH = normal.dot(H);

		auto diffuseTerm = diffuse.mul(max(NdotL, 0));
		auto specularTerm = specular.mul(pow(max(NdotH, 0), shiness));
		return lightColor.modulate(diffuseTerm.add(specularTerm));
	}

};

#endif