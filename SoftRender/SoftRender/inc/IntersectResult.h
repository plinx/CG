#ifndef IntersectResult_h
#define IntersectResult_h

class IntersectResult
{
public:
	bool geometry;
	double distance;
	Vec3 position, normal;

public:
	IntersectResult() {
		geometry = false; 
		distance = 0.0;
		//position = Vec3();
		//normal = Vec3();
	}

	~IntersectResult() = default;

};

#endif
