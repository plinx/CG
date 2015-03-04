#ifndef Camera_h
#define Camera_h

#define PI 3.14159

class Camera
{
private:
	Vec3 eye, front, refUp;
	Vec3 right, up;
	double fov, fovScale;


public:
	Camera() = default;
	~Camera() = default;

	Camera(Vec3 e, Vec3 f, Vec3 r, int v) :
		eye(e), front(f), refUp(r), fov(v) {}

	void initialize() {
		right = front.cross(refUp);
		up = right.cross(front);
		fovScale = tan(fov * 0.5 * PI / 180) * 2;
	}

	Ray3 generateRay(double x, double y) {
		Vec3 r = right.mul((x - 0.5) * fovScale);
		Vec3 u = up.mul((y - 0.5) * fovScale);
		return Ray3(eye, front.add(r).add(u).normalize());
	}


};

#endif