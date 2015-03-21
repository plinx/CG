#ifndef Pipeline_h
#define Pipeline_h

#define OBJEC4DV1_MAX_VERTICES 1024
#define OBJEC4DV1_MAX_POLYS 1024
#define RENDERLIST4DV1_MAX_POLYS 32768

struct Poly4DV1
{
	int state;
	int attr;
	int color;

	PPoint4D vlist;
	int vert[3];
};
typedef Poly4DV1* PPoly4DV1;

struct PolyF4DV1
{
	int state;
	int attr;
	int color;

	Point4D vlist[3];
	Point4D tvlist[3];

	PPoly4DV1 *next;
	PPoly4DV1 *prev;
};
typedef PolyF4DV1* PPolyF4DV1;

struct Object4DV1
{
	int id;
	std::string name;
	int state;
	int attr;
	float avg_radius;
	float max_radius;

	Point4D world_pos;

	Vector4D dir;
	Vector4D ux, uy, uz;

	int num_vertices;
	Point4D vlist_local[OBJEC4DV1_MAX_VERTICES];
	Point4D vlist_trans[OBJEC4DV1_MAX_VERTICES];

	int num_poly;
	Poly4DV1 plist[OBJEC4DV1_MAX_POLYS];
};
typedef Object4DV1* PObject4DV1;

struct RenderList4DV1
{
	int state;
	int attr;

	PPolyF4DV1 poly_ptrs[RENDERLIST4DV1_MAX_POLYS];
	PolyF4DV1 poly_data[RENDERLIST4DV1_MAX_POLYS];

	int num_polys;
};
typedef RenderList4DV1* PRenderList4DV1;

#endif