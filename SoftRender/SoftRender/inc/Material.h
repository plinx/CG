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
		if ((abs((int)(floor(position.getx() * 0.1) + floor(position.getz() * scale)) % 2)) < 1)
			return getColor(Color_BLACK);
		return getColor(Color_WHITE);
	}

};

class PhongMaterial
{
private:
	Color diffuse, specular;
	double shiness;

public:
	PhongMaterial() = default;
	~PhongMaterial() = default;
	
	PhongMaterial(Color diff, Color spec, double shin) :
		diffuse(diff), specular(spec), shiness(shin) {}

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