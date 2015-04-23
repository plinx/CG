#ifndef Vertex_h
#define Vertex_h

struct Vertex4D : public Vector4D
{
	Vector4D normal;
	Color color;

	//Vertex4D& normalize();

	// override operator
	Vertex4D& operator=(const Vertex4D& vert);
	Vertex4D& operator=(const Vector4D& vec);
	Vertex4D operator+(const Vector4D& vec);
};
typedef Vertex4D* PVertex4D;

inline Vertex4D& Vertex4D::operator=(const Vertex4D& vert)
{
	x = vert.x; y = vert.y; z = vert.z; w = 1.0;
	normal = vert.normal;
	//normal.x = vert.normal.x; normal.y = vert.normal.y;
	//normal.z = vert.normal.z; normal.w = vert.normal.w;
	color = vert.color;
	return *this;
}

inline Vertex4D& Vertex4D::operator=(const Vector4D& vec)
{
	x = vec.x; y = vec.y; z = vec.z; w = 1.0;
	return *this;
}

inline Vertex4D Vertex4D::operator+(const Vector4D& v)
{
	Vertex4D tmp;
	tmp = *this;
	tmp.x += v.x; tmp.y += v.y; tmp.z += v.z; w = 1.0;

	return tmp;
}

#endif