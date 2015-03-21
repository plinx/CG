#ifndef Pipeline_h
#define Pipeline_h

#define OBJECT4DV1_MAX_VERTICES 1024
#define OBJECT4DV1_MAX_POLYS 1024
#define RENDERLIST4DV1_MAX_POLYS 32768

#define OBJECT4DV1_STATE_ACTIVE           0x0001
#define OBJECT4DV1_STATE_VISIBLE          0x0002 
#define OBJECT4DV1_STATE_CULLED           0x0004

#define PLX_RGB_MASK          0x8000   // mask to extract RGB or indexed color
#define PLX_SHADE_MODE_MASK   0x6000   // mask to extract shading mode
#define PLX_2SIDED_MASK       0x1000   // mask for double sided
#define PLX_COLOR_MASK        0x0fff   // xxxxrrrrggggbbbb, 4-bits per channel RGB
// xxxxxxxxiiiiiiii, indexed mode 8-bit index

// these are the comparision flags after masking
// color mode of polygon
#define PLX_COLOR_MODE_RGB_FLAG     0x8000   // this poly uses RGB color
#define PLX_COLOR_MODE_INDEXED_FLAG 0x0000   // this poly uses an indexed 8-bit color 

// double sided flag
#define PLX_2SIDED_FLAG              0x1000   // this poly is double sided
#define PLX_1SIDED_FLAG              0x0000   // this poly is single sided

// shading mode of polygon
#define PLX_SHADE_MODE_PURE_FLAG      0x0000  // this poly is a constant color
#define PLX_SHADE_MODE_CONSTANT_FLAG  0x0000  // alias
#define PLX_SHADE_MODE_FLAT_FLAG      0x2000  // this poly uses flat shading
#define PLX_SHADE_MODE_GOURAUD_FLAG   0x4000  // this poly used gouraud shading
#define PLX_SHADE_MODE_PHONG_FLAG     0x6000  // this poly uses phong shading
#define PLX_SHADE_MODE_FASTPHONG_FLAG 0x6000  // this poly uses phong shading (alias)

#define POLY4DV1_ATTR_2SIDED              0x0001
#define POLY4DV1_ATTR_TRANSPARENT         0x0002
#define POLY4DV1_ATTR_8BITCOLOR           0x0004
#define POLY4DV1_ATTR_RGB16               0x0008
#define POLY4DV1_ATTR_RGB24               0x0010

#define POLY4DV1_ATTR_SHADE_MODE_PURE       0x0020
#define POLY4DV1_ATTR_SHADE_MODE_CONSTANT   0x0020 // (alias)
#define POLY4DV1_ATTR_SHADE_MODE_FLAT       0x0040
#define POLY4DV1_ATTR_SHADE_MODE_GOURAUD    0x0080
#define POLY4DV1_ATTR_SHADE_MODE_PHONG      0x0100
#define POLY4DV1_ATTR_SHADE_MODE_FASTPHONG  0x0100 // (alias)
#define POLY4DV1_ATTR_SHADE_MODE_TEXTURE    0x0200 

// states of polygons and faces
#define POLY4DV1_STATE_ACTIVE             0x0001
#define POLY4DV1_STATE_CLIPPED            0x0002
#define POLY4DV1_STATE_BACKFACE           0x0004

// defines for objects version 1
#define OBJECT4DV1_MAX_VERTICES           1024  // 64
#define OBJECT4DV1_MAX_POLYS              1024 // 128

// states for objects
#define OBJECT4DV1_STATE_ACTIVE           0x0001
#define OBJECT4DV1_STATE_VISIBLE          0x0002 
#define OBJECT4DV1_STATE_CULLED           0x0004

// Models
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
	double avg_radius;
	double max_radius;

	Point4D world_pos;

	Vector4D dir;
	Vector4D ux, uy, uz;

	int num_vertices;
	Point4D vlist_local[OBJECT4DV1_MAX_VERTICES];
	Point4D vlist_trans[OBJECT4DV1_MAX_VERTICES];

	int num_poly;
	Poly4DV1 plist[OBJECT4DV1_MAX_POLYS];

	Object4DV1() = default;
	~Object4DV1() = default;

	void clear() { memset(this, 0, sizeof(Object4DV1)); }
	double compute_radius() {
		avg_radius = 0;
		max_radius = 0;

		for (int vertex = 0; vertex < num_vertices; vertex++)
		{
			double length = vlist_local[vertex].length();
			avg_radius += length;

			if (length > max_radius)
				max_radius = length;
		}

		avg_radius /= num_vertices;

		return max_radius;
	}

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

// file loader
/*
int Load_Object4DV1_PLG(PObject4DV1 obj, std::string fpath,
	double scale, PVector4D pos, PVector4D rot)
{
	return 0;
}*/


#endif