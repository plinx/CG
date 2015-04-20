#ifndef Vertex_h
#define Vertex_h

struct Vertex4D : public Vector4D
{
	Vector4D normal;
	Color color;

	// override operator
	Vertex4D& operator=(const Vertex4D& vert);
	Vertex4D& operator=(const Vector4D& vert);
};
typedef Vertex4D* PVertex4D;

inline Vertex4D& Vertex4D::operator=(const Vertex4D& vert)
{
	x = vert.x; y = vert.y; z = vert.z; w = 1.0;
	normal.x = vert.normal.x; normal.y = vert.normal.y;
	normal.z = vert.normal.z; normal.w = vert.normal.w;
	color = vert.color;
	return *this;
}

inline Vertex4D& Vertex4D::operator=(const Vector4D& v)
{
	x = v.x; y = v.y; z = v.z; w = 1.0;
	return *this;
}

#endif