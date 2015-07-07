#ifndef Pipeline_h
#define Pipeline_h

enum InsertMode 
{
	OBJECT4D_LOCAL_INSERT = 0,
	OBJECT4D_TRANS_INSERT,
};

enum 
{
	OBJECT4D_MAX_VERTICES = 1024,
	OBJECT4D_MAX_POLYS = 1024,
	RENDERLIST4D_MAX_POLYS = 1024,
};

enum TransformMode 
{
	TRANSFORM_LOCAL_ONLY = 0,
	TRANSFORM_TRANS_ONLY,
	TRANSFORM_LOCAL_TO_TRANS,
};

enum RenderState
{
	OBJECT4D_STATE_ACTIVE = 1,	// 0x0001
	OBJECT4D_STATE_VISIBLE = 2,	// 0x0002
	OBJECT4D_STATE_CULLED = 4,	// 0x0004
	POLY4D_STATE_ACTIVE = 1,	// 0x0001
	POLY4D_STATE_CLIPPED = 2,	// 0x0002
	POLY4D_STATE_BACKFACE = 4,	// 0x0004
};
//const int OBJECT4D_STATE_ACTIVE = 0x0001;
//const int OBJECT4D_STATE_VISIBLE = 0x0002;
//const int OBJECT4D_STATE_CULLED = 0x0004;
//const int POLY4D_STATE_ACTIVE = 0x0001;
//const int POLY4D_STATE_CLIPPED = 0x0002;
//const int POLY4D_STATE_BACKFACE = 0x0004;

// float sided flag
#define PLX_2SIDED_FLAG              0x1000   // this poly is float sided
#define PLX_1SIDED_FLAG              0x0000   // this poly is single sided

const int POLY4D_ATTR_2SIDED = 0x0001;
const int POLY4D_ATTR_TRANSPARENT = 0x0002;

struct Poly4D
{
	int state;
	int attr;
	Color color;

	//PPoint4D vlist = NULL;
	PVertex4D vlist = NULL;
	int vert[3];
};
typedef Poly4D* PPoly4D;

struct PolyList4D
{
	int state;
	int attr;
	Color color;

	//Point4D vlist[3];
	//Point4D tvlist[3];
	Vertex4D vlist[3];
	Vertex4D tvlist[3];

	PolyList4D* next = NULL;
	PolyList4D* prev = NULL;
};
typedef PolyList4D* PPolyList4D;

struct Object4D
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
	//Point4D vlist_local[OBJECT4D_MAX_VERTICES];
	//Point4D vlist_trans[OBJECT4D_MAX_VERTICES];
	Vertex4D vlist_local[OBJECT4D_MAX_VERTICES];
	Vertex4D vlist_trans[OBJECT4D_MAX_VERTICES];

	int num_polys;
	Poly4D plist[OBJECT4D_MAX_POLYS];

	Object4D() = default;
	~Object4D() = default;

	void clear();
	void reset();
	void rotate(PMatrix4x4 m, TransformMode mode, int basis);
	void to_World(TransformMode mode = TRANSFORM_LOCAL_TO_TRANS);
	void compute_Vertex();
};
typedef Object4D* PObject4D;

struct RenderList4D
{
	int state;
	int attr;
	int num_polys;

	PPolyList4D poly_ptrs[RENDERLIST4D_MAX_POLYS];
	PolyList4D poly_data[RENDERLIST4D_MAX_POLYS];

	RenderList4D() { num_polys = 0; }
	~RenderList4D() = default;

	void reset();
	int insert(PPoly4D poly);
	int insert(PObject4D obj, InsertMode mode = OBJECT4D_TRANS_INSERT);	
	void rotate(PMatrix4x4 m, TransformMode mode);
	void to_World(PPoint4D pos, TransformMode mode);
	void zsort();
};
typedef RenderList4D* PRenderList4D;

// Object4D methods implement
inline void Object4D::clear() 
{ 
	memset(this, 0, sizeof(Object4D)); 
}

inline void Object4D::reset()
{
	state &= ~OBJECT4D_STATE_CULLED;

	for (int poly = 0; poly < num_polys; poly++)
	{
		PPoly4D curr_poly = &plist[poly];

		if (!(curr_poly->state & POLY4D_STATE_ACTIVE))
			continue;

		curr_poly->state &= ~POLY4D_STATE_CLIPPED;
		curr_poly->state &= ~POLY4D_STATE_BACKFACE;
	}

	// use vertex list trans rather than vertex list local 
	// use vertex list trans and no need to reset normal
	for (int vertex = 0; vertex < num_vertices; vertex++)
	{
		//vlist_trans[vertex] = vlist_local[vertex];
		vlist_trans[vertex].normal.zero();
		vlist_trans[vertex].color = vlist_local[vertex].color;
	}
}

inline void Object4D::rotate(PMatrix4x4 m, TransformMode mode, int basis)
{
	switch (mode)
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

inline void Object4D::to_World(TransformMode mode)
{
	if (mode == TRANSFORM_LOCAL_TO_TRANS)
	{
		for (int vertex = 0; vertex < num_vertices; vertex++)
		{
			vlist_trans[vertex] = vlist_local[vertex] + world_pos;
			// implement vlist_trans.color = vlist_local.color in operator+()
			//vlist_trans[vertex].color = vlist_local[vertex].color;
		}
	}
	else if (mode == TRANSFORM_TRANS_ONLY)
	{
		for (int vertex = 0; vertex < num_vertices; vertex++)
		{
			vlist_trans[vertex] += world_pos;
		}
	}
}
inline void Object4D::compute_Vertex()
{
	float vertex_angle[OBJECT4D_MAX_VERTICES];

	memset(vertex_angle, 0, sizeof(float) * OBJECT4D_MAX_VERTICES);
	for (int poly = 0; poly < num_polys; poly++)
	{
		int vert0 = plist[poly].vert[0];
		int vert1 = plist[poly].vert[1];
		int vert2 = plist[poly].vert[2];

		//Vector4D u(&vlist_local[vert0], &vlist_local[vert1]); // vec01
		//Vector4D v(&vlist_local[vert0], &vlist_local[vert2]); // vec02
		Vector4D u(&vlist_trans[vert0], &vlist_trans[vert1]); // vec01
		Vector4D v(&vlist_trans[vert0], &vlist_trans[vert2]); // vec02
		Vector4D n(u.cross(&v));
		n.normalize();

		Vector4D vec12(&vlist_local[vert1], &vlist_local[vert2]);	// vec12
		float angle0 = acos(u.normalize().dot(&v.normalize()));	// vec01.dot(vec02), vec01 and vec02 normalize
		float angle1 = acos(u.reverse().dot(&vec12.normalize()));	// vec10.dot(vec12), vec12 normalize
		float angle2 = acos(v.reverse().dot(&vec12.reverse()));	// vec20.dot(vec21), all vecs were normalized

		vertex_angle[vert0] += angle0;
		vertex_angle[vert1] += angle1;
		vertex_angle[vert2] += angle2;

		// init vertex normal to zero
		// vertex normal add face normal
		// use vertex list trans rather than vertex list local
		vlist_trans[vert0].normal += n * angle0;
		vlist_trans[vert1].normal += n * angle1;
		vlist_trans[vert2].normal += n * angle2;
	}

	for (int vertex = 0; vertex < num_vertices; vertex++)
	{
		vlist_trans[vertex].normal /= vertex_angle[vertex];
		vlist_trans[vertex].normal.normalize();					// the result has already been normalized
	}
}

// RenderList4D methods implement
inline void RenderList4D::reset() 
{ 
	num_polys = 0; 
}

inline int RenderList4D::insert(PPoly4D poly)
{
	if (num_polys >= RENDERLIST4D_MAX_POLYS)
		return 0;

	poly_ptrs[num_polys] = &poly_data[num_polys];
	poly_data[num_polys].state = poly->state;
	poly_data[num_polys].attr = poly->attr;
	poly_data[num_polys].color = poly->color;

	poly_data[num_polys].tvlist[0] = poly->vlist[poly->vert[0]];
	poly_data[num_polys].tvlist[1] = poly->vlist[poly->vert[1]];
	poly_data[num_polys].tvlist[2] = poly->vlist[poly->vert[2]];

	poly_data[num_polys].vlist[0] = poly->vlist[poly->vert[0]];
	poly_data[num_polys].vlist[1] = poly->vlist[poly->vert[1]];
	poly_data[num_polys].vlist[2] = poly->vlist[poly->vert[2]];

	if (num_polys != 0)
	{
		poly_data[num_polys].prev = &poly_data[num_polys - 1];
		poly_data[num_polys - 1].next = &poly_data[num_polys];
	}
	num_polys++;
	return 1;
}

inline int RenderList4D::insert(PObject4D obj, InsertMode mode)
{
	if (!(obj->state & OBJECT4D_STATE_ACTIVE) ||
		(obj->state & OBJECT4D_STATE_CULLED) ||
		!(obj->state & OBJECT4D_STATE_VISIBLE))
		return 0;

	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		PPoly4D curr_poly = &obj->plist[poly];

		if (!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		//PPoint4D vlist_old = curr_poly->vlist;
		PVertex4D vlist_old = curr_poly->vlist;
		if (mode == OBJECT4D_TRANS_INSERT)
		{
			curr_poly->vlist = obj->vlist_trans;
		}
		else // OBJECT4D_LOCAL_INSERT
		{
			curr_poly->vlist = obj->vlist_local;
		}

		if (!this->insert(curr_poly))
		{
			curr_poly->vlist = vlist_old;
			return 0;
		}
		//curr_poly->vlist = vlist_old;
	}
	return 1;
}

inline void RenderList4D::rotate(PMatrix4x4 m, TransformMode mode)
{
	switch (mode)
	{
	case TRANSFORM_LOCAL_ONLY:
		for (int poly = 0; poly < num_polys; poly++)
		{
			PPolyList4D curr_poly = poly_ptrs[poly];

			if ((curr_poly == NULL) ||
				!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
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
			PPolyList4D curr_poly = poly_ptrs[poly];

			if ((curr_poly == NULL) ||
				!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
				continue;

			for (int vertex = 0; vertex < 3; vertex++)
			{
				curr_poly->tvlist[vertex] = m->mul(&curr_poly->tvlist[vertex]);
			}
		}
	case TRANSFORM_LOCAL_TO_TRANS:
		for (int poly = 0; poly < num_polys; poly++)
		{
			PPolyList4D curr_poly = poly_ptrs[poly];

			if ((curr_poly == NULL) ||
				!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
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

inline void RenderList4D::to_World(PPoint4D pos, TransformMode mode)
{
	if (mode == TRANSFORM_LOCAL_TO_TRANS)
	{
		for (int poly = 0; poly < num_polys; poly++)
		{
			PPolyList4D curr_poly = poly_ptrs[poly];

			if ((curr_poly == NULL) ||
				!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
				continue;

			for (int vertex = 0; vertex < 3; vertex++)
			{
				curr_poly->tvlist[vertex] = curr_poly->vlist[vertex] + *pos;
			}
		}
	}
	else if (mode == TRANSFORM_TRANS_ONLY)
	{
		for (int poly = 0; poly < num_polys; poly++)
		{
			PPolyList4D curr_poly = poly_ptrs[poly];

			if ((curr_poly == NULL) ||
				!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
				continue;

			for (int vertex = 0; vertex < 3; vertex++)
			{
				curr_poly->tvlist[vertex] += *pos;
			}
		}
	}
}

// file loader

inline int Load_Object4D_PLG(PObject4D obj, std::string fpath,
	PVector4D scale, PVector4D pos, PVector4D rot)
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

	obj->clear();
	obj->state = OBJECT4D_STATE_ACTIVE | OBJECT4D_STATE_VISIBLE;
	obj->world_pos = *pos;
	iss.str(data[offset]);
	offset++;
	iss >> obj->name >> obj->num_vertices >> obj->num_polys;
	//std::cout << "name : " << obj->name << std::endl;
	//std::cout << "vertices : " << obj->num_vertices << std::endl;
	//std::cout << "poly : " << obj->num_polys << std::endl;

	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		iss.clear();
		iss.str(data[vertex + offset]);
		iss >> obj->vlist_local[vertex].x >> obj->vlist_local[vertex].y >> obj->vlist_local[vertex].z;
		obj->vlist_local[vertex].x *= scale->x;
		obj->vlist_local[vertex].y *= scale->y;
		obj->vlist_local[vertex].z *= scale->z;

		//std::cout << obj->vlist_local[vertex].x << " " << obj->vlist_local[vertex].y << " " << obj->vlist_local[vertex].z;
		//std::cout << std::endl;
	}
	offset += obj->num_vertices;

	//obj->compute_radius();

	int poly_surface_desc = 0;
	int poly_num_verts = 0;
	int poly = 0;
	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		iss.clear();
		iss.str(data[poly + offset]);
		iss >> std::hex >> poly_surface_desc >> std::dec >> poly_num_verts
			>> obj->plist[poly].vert[0] >> obj->plist[poly].vert[1] >> obj->plist[poly].vert[2];
		/*std::cout << std::hex << poly_surface_desc 
			<< " " << std::dec << poly_num_verts 
			<< " " << obj->plist[poly].vert[0] 
			<< " " << obj->plist[poly].vert[1] 
			<< " " << obj->plist[poly].vert[2] << std::endl;*/
		if (poly_surface_desc & PLX_2SIDED_FLAG)
		{
			obj->plist[poly].attr |= POLY4D_ATTR_2SIDED;
		}

		obj->plist[poly].state = POLY4D_STATE_ACTIVE;
	}
	ifs.close();

	return 1;
}

inline int Compare_avgz(const void* arg1, const void* arg2)
{
	float z1, z2;
	PPolyList4D poly1 = *((PPolyList4D*)arg1);
	PPolyList4D poly2 = *((PPolyList4D*)arg2);

	z1 = (float)0.333 * (poly1->tvlist[0].z + poly1->tvlist[1].z + poly1->tvlist[2].z);
	z2 = (float)0.333 * (poly2->tvlist[0].z + poly2->tvlist[1].z + poly2->tvlist[2].z);

	if (z1 > z2)
		return -1;
	else if (z1 < z2)
		return 1;
	else
		return 0;
}

inline void RenderList4D::zsort()
{
	qsort(poly_ptrs, this->num_polys, sizeof(PPolyList4D), Compare_avgz);
}

#endif