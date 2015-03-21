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

#define TRANSFORM_LOCAL_ONLY       0  // perform the transformation in place on the
// local/world vertex list 
#define TRANSFORM_TRANS_ONLY       1  // perfrom the transformation in place on the 
// "transformed" vertex list

#define TRANSFORM_LOCAL_TO_TRANS   2  // perform the transformation to the local
// vertex list, but store the results in the
// transformed vertex list

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

	void transform(PMatrix4x4 m, int select, int basis)
	{
		switch (select)
		{
		case TRANSFORM_LOCAL_ONLY:
			for (int vertex = 0; vertex < num_vertices; vertex++)
			{
				vlist_local[vertex] = m->mul(&vlist_local[vertex]);
			}
		case TRANSFORM_TRANS_ONLY:
			for (int vertex = 0; vertex < num_vertices; vertex++)
			{
				vlist_trans[vertex] = m->mul(&vlist_trans[vertex]);
			}
		case TRANSFORM_LOCAL_TO_TRANS:
			for (int vertex = 0; vertex < num_vertices; vertex++)
			{
				vlist_trans[vertex] = m->mul(&vlist_local[vertex]);
			}
		default:
			break;
		}

		if (basis)
		{
			ux = m->mul(&ux);
			uy = m->mul(&uy);
			uz = m->mul(&uz);
		}
	}
	void transformWorld(int select = TRANSFORM_LOCAL_TO_TRANS)
	{
		if (select == TRANSFORM_LOCAL_TO_TRANS)
		{
			for (int vertex = 0; vertex < num_vertices; vertex++)
			{
				vlist_trans[vertex] = vlist_local[vertex] + world_pos;
			}
		}
		else
		{
			for (int vertex = 0; vertex < num_vertices; vertex++)
			{
				vlist_trans[vertex] += world_pos;
			}
		}
	}

};
typedef Object4DV1* PObject4DV1;

struct RenderList4DV1
{
	int state;
	int attr;
	int num_polys;

	PPolyF4DV1 poly_ptrs[RENDERLIST4DV1_MAX_POLYS];
	PolyF4DV1 poly_data[RENDERLIST4DV1_MAX_POLYS];

	void transform(PMatrix4x4 m, int select) 
	{
		switch (select)
		{
		case TRANSFORM_LOCAL_ONLY:
			for (int poly = 0; poly < num_polys; poly++) 
			{
				PPolyF4DV1 curr_poly = poly_ptrs[poly];

				if ((curr_poly == NULL) ||
					!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
					(curr_poly->state & POLY4DV1_STATE_BACKFACE))
					continue;

				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->vlist[vertex] = m->mul(&curr_poly->vlist[vertex]);
				}
			}
			break;
		case TRANSFORM_TRANS_ONLY:
			for (int poly = 0; poly < num_polys; poly++)
			{
				PPolyF4DV1 curr_poly = poly_ptrs[poly];

				if ((curr_poly == NULL) ||
					!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
					(curr_poly->state & POLY4DV1_STATE_BACKFACE))
					continue;

				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->tvlist[vertex] = m->mul(&curr_poly->tvlist[vertex]);
				}
			}
		case TRANSFORM_LOCAL_TO_TRANS:
			for (int poly = 0; poly < num_polys; poly++)
			{
				PPolyF4DV1 curr_poly = poly_ptrs[poly];

				if ((curr_poly == NULL) ||
					!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
					(curr_poly->state & POLY4DV1_STATE_BACKFACE))
					continue;
				
				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->tvlist[vertex] = m->mul(&curr_poly->vlist[vertex]);
				}
			}
		default:
			break;
		}
	}

	void transformWorld(PPoint4D pos, int select = TRANSFORM_LOCAL_TO_TRANS)
	{
		if (select == TRANSFORM_LOCAL_TO_TRANS)
		{
			for (int poly = 0; poly < num_polys; poly++)
			{
				PPolyF4DV1 curr_poly = poly_ptrs[poly];

				if ((curr_poly == NULL) ||
					!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					!(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
					!(curr_poly->state & POLY4DV1_STATE_BACKFACE))
					continue;

				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->tvlist[vertex] = curr_poly->vlist[vertex] + *pos;
				}
			}
		}
		else
		{
			for (int poly = 0; poly < num_polys; poly++)
			{
				PPolyF4DV1 curr_poly = poly_ptrs[poly];

				if ((curr_poly == NULL) ||
					!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					!(curr_poly->state & POLY4DV1_STATE_CLIPPED) ||
					!(curr_poly->state & POLY4DV1_STATE_BACKFACE))
					continue;

				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->tvlist[vertex] += *pos;
				}
			}
		}
	}
};
typedef RenderList4DV1* PRenderList4DV1;

// file loader

inline int Load_Object4DV1_PLG(PObject4DV1& obj, std::string fpath,
	double scale, PVector4D pos, PVector4D rot)
{
	std::vector<std::string> data;
	std::string line, tmp;
	std::ifstream ifs(fpath);
	std::istringstream iss;

	int i = 0;
	int offset = 0;
	if (!ifs.is_open())
	{
		std::cout << "file is not opening" << std::endl;
		return 0;
	}
	while (std::getline(ifs, line))
	{
		if (line.length() == 0 || line.at(0) == '#')
			continue;
		data.push_back(line);
	}

	obj = (PObject4DV1)malloc(sizeof(Object4DV1));
	obj->clear();
	obj->state = OBJECT4DV1_STATE_ACTIVE | OBJECT4DV1_STATE_VISIBLE;
	obj->world_pos = *pos;
	iss.str(data[offset]);
	offset++;
	iss >> obj->name >> obj->num_vertices >> obj->num_poly;
	std::cout << "name : " << obj->name << std::endl;
	std::cout << "vertices : " << obj->num_vertices << std::endl;
	std::cout << "poly : " << obj->num_poly << std::endl;

	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		iss.clear();
		iss.str(data[vertex + offset]);
		iss >> obj->vlist_local[vertex].x >> obj->vlist_local[vertex].y >> obj->vlist_local[vertex].z;
		obj->vlist_local[vertex] *= scale;

		std::cout << obj->vlist_local[vertex].x << " " << obj->vlist_local[vertex].y << " " << obj->vlist_local[vertex].z;
		std::cout << std::endl;
	}
	offset += obj->num_vertices;

	obj->compute_radius();

	int poly_surface_desc = 0;
	int poly_num_verts = 0;
	int poly = 0;
	for (int poly = 0; poly < obj->num_poly; poly++)
	{
		iss.clear();
		iss.str(data[poly + offset]);
		iss >> std::hex >> poly_surface_desc >> std::dec >> poly_num_verts
			>> obj->plist[poly].vert[0] >> obj->plist[poly].vert[1] >> obj->plist[poly].vert[3];
		std::cout << std::hex << poly_surface_desc << " " << std::dec << poly_num_verts << " " << obj->plist[poly].vert[0] << " " << obj->plist[poly].vert[1] << " " << obj->plist[poly].vert[2] << std::endl;
		if (poly_surface_desc & PLX_2SIDED_FLAG)
		{
			obj->plist[poly].attr |= POLY4DV1_ATTR_2SIDED;
		}

		if (poly_surface_desc & PLX_COLOR_MODE_RGB_FLAG)
		{
			obj->plist[poly].attr |= POLY4DV1_ATTR_RGB16;

			int red = (poly_surface_desc & 0x0f00) >> 4;
			int green = (poly_surface_desc & 0x00f0);
			int blue = (poly_surface_desc & 0x000f) << 4;
			std::cout << "red : " << red << " green : " << green << " blue : " << blue << std::endl;
			obj->plist[poly].color = RGB(red, green, blue);
		}

		int shade_mode = (poly_surface_desc & PLX_SHADE_MODE_MASK);

		switch (shade_mode)
		{
		case PLX_SHADE_MODE_PURE_FLAG:
			obj->plist[poly].attr |= POLY4DV1_ATTR_SHADE_MODE_PURE;
			break;
		case PLX_SHADE_MODE_FLAT_FLAG:
			obj->plist[poly].attr |= POLY4DV1_ATTR_SHADE_MODE_FLAT;
			break;
		case PLX_SHADE_MODE_GOURAUD_FLAG:
			obj->plist[poly].attr |= POLY4DV1_ATTR_SHADE_MODE_GOURAUD;
			break;
		case PLX_SHADE_MODE_PHONG_FLAG:
			obj->plist[poly].attr |= POLY4DV1_ATTR_SHADE_MODE_PHONG;
			break;
		default:
			break;
		}

		obj->plist[poly].state = POLY4DV1_STATE_ACTIVE;
	}
	ifs.close();

	return 1;
}


#endif