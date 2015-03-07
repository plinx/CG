#ifndef IntersectResult_h
#define IntersectResult_h

class IntersectResult
{
public:
	bool geometry;
	double distance;
	Vec3 position, normal;
	Material* material;

public:
	IntersectResult() {
		geometry = false; 
		distance = 10000.0;
		material = new Material();// PhongMaterial(getColor(Color_RED), getColor(Color_WHITE), 26);
		//position = Vec3();
		//normal = Vec3();
	}
	~IntersectResult() = default;

	//void setMaterial(Material m) { material = m; }

};

#endif
