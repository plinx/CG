#ifndef Camera_h
#define Camera_h
enum 
{
	CAM_ROT_SEQ_XYZ = 0,
	CAM_ROT_SEQ_YXZ,
	CAM_ROT_SEQ_XZY,
	CAM_ROT_SEQ_YZX,
	CAM_ROT_SEQ_ZYX,
	CAM_ROT_SEQ_ZXY
};

enum 
{
	UVN_MODE_SIMPLE,
	UVN_MODE_SPHERICAL
};

/*
// general culling flags
#define CULL_OBJECT_X_PLANE           0x0001 // cull on the x clipping planes
#define CULL_OBJECT_Y_PLANE           0x0002 // cull on the y clipping planes
#define CULL_OBJECT_Z_PLANE           0x0004 // cull on the z clipping planes
#define CULL_OBJECT_XYZ_PLANES        (CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE)
*/
const int CULL_OBJECT_X_PLANE = 0x0001;
const int CULL_OBJECT_Y_PLANE = 0x0002;
const int CULL_OBJECT_Z_PLANE = 0x0004;
const int CULL_OBJECT_XYZ_PLANE = CULL_OBJECT_X_PLANE | CULL_OBJECT_Y_PLANE | CULL_OBJECT_Z_PLANE;

struct Camera
{
	int state;
	int attr;

	Point4D pos;
	Vector4D dir;
	Vector4D u, v, n;
	Point4D target;

	float view_h, view_v;
	float view_dist;
	float fov;

	float near_clip, far_clip;

	Plane3D right_plane, left_plane, top_plane, bottom_plane;

	float viewplane_width, viewplane_height;
	float viewport_width, viewport_height, viewport_cx, viewport_cy;
	float aspect_ratio;

	Matrix4x4 mcam, mper, mscr;

	// Contructor
	Camera() = default;
	~Camera() = default;
	Camera(int a, Point4D p, Vector4D d, Point4D t,
		float nc, float fc, float f, float w, float h);

	// basic methods
	void init(int a, Point4D p, Vector4D d, Point4D t,
		float nc, float fc, float f, float w, float h);
	void build_Euler(int cam_rot_seq);
	void build_UVN(int mode);
	void from_World(PObject4D obj);
	void from_World(PRenderList4D rlist);
	int cull(PObject4D obj, int cull_flag);
	void remove_Backfaces(PObject4D obj);
	void remove_Backfaces(PRenderList4D rlist);
	void build_Screen_Matrix4x4(PMatrix4x4 m);
	void to_Perspective(PObject4D obj);
	void to_Perspective(PRenderList4D rlist);
	void to_Screen(PRenderList4D rlist);
	void to_Screen(PObject4D obj);

};
typedef Camera* PCamera;

// Camera methods implement
inline Camera::Camera(int a, Point4D p, Vector4D d, Point4D t,
	float nc, float fc, float f, float w, float h)
	: attr(a), pos(p), dir(d), target(t),
	near_clip(nc), far_clip(fc), fov(f), viewport_width(w), viewport_height(h)
{
	u.init(1, 0, 0);
	v.init(0, 1, 0);
	n.init(0, 0, 1);

	//viewport_cx = (viewport_width - 1) / 2;
	//viewport_cy = (viewport_height - 1) / 2;
	viewport_cx = viewport_width / 2;
	viewport_cy = viewport_height / 2;
	aspect_ratio = viewport_width / viewport_height;

	mcam.unit();
	mper.unit();
	mscr.unit();

	viewplane_width = 2.0;
	viewplane_height = (float)2.0 / aspect_ratio;
	float tan_fov_div2 = tan(Angle_to_Radian(fov / 2));
	view_dist = (float)(0.5) * viewplane_width * tan_fov_div2;
	if (89.99 < fov && fov < 90.01)
	{
		Point3D pt_origin(0, 0, 0);
		Vector3D vn(1, 0, -1);
		right_plane.init(pt_origin, vn, 1);
		vn.init(-1, 0, 1);
		left_plane.init(pt_origin, vn, 1);
		vn.init(0, 1, -1);
		top_plane.init(pt_origin, vn, 1);
		vn.init(0, -1, -1);
		bottom_plane.init(pt_origin, vn, 1);
	}
	else
	{
		Point3D pt_origin(0, 0, 0);
		Vector3D vn(view_dist, 0, (float)(-viewplane_width / 2.0));
		right_plane.init(pt_origin, vn, 1);
		//vn.init(-(int)view_dist, 0, (float)(-viewplane_width / 2.0));
		vn.init(-ceil(view_dist), 0, (float)(-viewplane_width / 2.0));
		left_plane.init(pt_origin, vn, 1);
		vn.init(0, view_dist, (float)(-viewplane_height / 2.0));
		top_plane.init(pt_origin, vn, 1);
		vn.init(0, -view_dist, (float)(-viewplane_width / 2.0));
		bottom_plane.init(pt_origin, vn, 1);
	}
}

inline void Camera::init(int a, Point4D p, Vector4D d, Point4D t,
	float nc, float fc, float f, float w, float h)
{
	attr = a; pos = p; dir = d; target = t;
	near_clip = nc; far_clip = fc; fov = f; viewport_width = w; viewport_height = h;

	u.init(1, 0, 0);
	v.init(0, 1, 0);
	n.init(0, 0, 1);

	viewport_cx = viewport_width / 2;
	viewport_cy = viewport_height / 2;
	aspect_ratio = viewport_width / viewport_height;

	mcam.unit();
	mper.unit();
	mscr.unit();

	viewplane_width = 2.0;
	viewplane_height = (float)2.0 / aspect_ratio;
	float tan_fov_div2 = tan(Angle_to_Radian(fov / 2));
	view_dist = (float)(0.5) * viewplane_width * tan_fov_div2;
	if (89.99 < fov && fov < 90.01)
	{
		Point3D pt_origin(0, 0, 0);
		Vector3D vn(1, 0, -1);
		right_plane.init(pt_origin, vn, 1);
		vn.init(-1, 0, 1);
		left_plane.init(pt_origin, vn, 1);
		vn.init(0, 1, -1);
		top_plane.init(pt_origin, vn, 1);
		vn.init(0, -1, -1);
		bottom_plane.init(pt_origin, vn, 1);
	}
	else
	{
		Point3D pt_origin(0, 0, 0);
		Vector3D vn(view_dist, 0, (float)(-viewplane_width / 2.0));
		right_plane.init(pt_origin, vn, 1);
		//vn.init(-(int)view_dist, 0, (float)(-viewplane_width / 2.0));
		vn.init(-ceil(view_dist), 0, (float)(-viewplane_width / 2.0));
		left_plane.init(pt_origin, vn, 1);
		vn.init(0, view_dist, (float)(-viewplane_height / 2.0));
		top_plane.init(pt_origin, vn, 1);
		vn.init(0, -view_dist, (float)(-viewplane_width / 2.0));
		bottom_plane.init(pt_origin, vn, 1);
	}
}

inline void Camera::build_Euler(int cam_rot_seq)
{
	Matrix4x4 mt_inv, mx_inv, my_inv, mz_inv, mrot, mtmp;
	mt_inv.init(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-pos.x, -pos.y, -pos.z, 1);

	float theta_x = dir.x;
	float theta_y = dir.y;
	float theta_z = dir.z;

	float cos_theta = Fast_cos(theta_x);
	float sin_theta = -Fast_sin(theta_x);
	mx_inv.init(1, 0, 0, 0,
		0, cos_theta, sin_theta, 0,
		0, -sin_theta, cos_theta, 0,
		0, 0, 0, 1);

	cos_theta = Fast_cos(theta_y);
	sin_theta = -Fast_sin(theta_y);
	my_inv.init(cos_theta, 0, -sin_theta, 0,
		0, 1, 0, 0,
		sin_theta, 0, cos_theta, 0,
		0, 0, 0, 1);

	cos_theta = Fast_cos(theta_z);
	sin_theta = -Fast_sin(theta_z);
	mz_inv.init(cos_theta, sin_theta, 0, 0,
		-sin_theta, cos_theta, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	switch (cam_rot_seq)
	{
	case CAM_ROT_SEQ_XYZ:
		mtmp = mx_inv * my_inv;
		mrot = mtmp * mz_inv;
		break;
	case CAM_ROT_SEQ_YXZ:
		mtmp = my_inv * mx_inv;
		mrot = mtmp * mz_inv;
		break;
	case CAM_ROT_SEQ_XZY:
		mtmp = mx_inv * mz_inv;
		mrot = mtmp * my_inv;
		break;
	case CAM_ROT_SEQ_YZX:
		mtmp = my_inv * mz_inv;
		mrot = mtmp * mx_inv;
		break;
	case CAM_ROT_SEQ_ZYX:
		mtmp = mz_inv * my_inv;
		mrot = mtmp * mx_inv;
		break;
	case CAM_ROT_SEQ_ZXY:
		mtmp = mz_inv * mx_inv;
		mrot = mtmp * my_inv;
		break;
	default:
		break;
	}
	mcam = mt_inv * mrot;
}

inline void Camera::build_UVN(int mode)
{
	Matrix4x4 mt_inv, mt_uvn;// , mtmp;
	mt_inv.init(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-pos.x, -pos.y, -pos.z, 1);

	if (mode == UVN_MODE_SPHERICAL)
	{
		float phi = dir.x;
		float theta = dir.y;

		float sin_phi = Fast_sin(phi);
		float cos_phi = Fast_cos(phi);

		float sin_theta = Fast_sin(theta);
		float cos_theta = Fast_cos(theta);

		target.x = (float)-1.0 * sin_phi * sin_theta;
		target.y = (float)1.0 * cos_phi;
		target.z = (float)1.0 * sin_phi * cos_theta;
	}
	n = target - pos;
	v.init(0, 1, 0);
	u = v.cross(&n);
	v = n.cross(&u);

	u.normalize();
	v.normalize();
	n.normalize();

	mt_uvn.init(u.x, v.x, n.x, 0,
		u.y, v.y, n.y, 0,
		u.z, v.z, n.z, 0,
		0, 0, 0, 1);

	mcam = mt_inv * mt_uvn;
}

inline void Camera::from_World(PObject4D obj)
{
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		obj->vlist_trans[vertex] = mcam.mul(&obj->vlist_trans[vertex]);
	}
}

inline void Camera::from_World(PRenderList4D rlist)
{
	for (int poly = 0; poly < rlist->num_polys; poly++)
	{
		PPolyFace4D curr_poly = rlist->poly_ptrs[poly];

		if ((curr_poly == NULL) ||
			!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		for (int vertex = 0; vertex < 3; vertex++)
		{
			curr_poly->tvlist[vertex] = mcam.mul(&curr_poly->tvlist[vertex]);
		}
	}
}

inline int Camera::cull(PObject4D obj, int cull_flag)
{
	Point4D sphere_pos;
	sphere_pos = mcam.mul(&obj->world_pos);

	if (cull_flag & CULL_OBJECT_Z_PLANE)
	{
		if (((sphere_pos.z + obj->max_radius) < near_clip) ||
			((sphere_pos.z - obj->max_radius) > far_clip))
		{
			obj->state |= OBJECT4D_STATE_CULLED;
			return 1;
		}
	}

	if (cull_flag & CULL_OBJECT_X_PLANE)
	{
		float z_test = (float)(0.5) * viewplane_width * sphere_pos.z / view_dist;
		if (((sphere_pos.x + obj->max_radius) < -z_test) ||
			((sphere_pos.x - obj->max_radius) > z_test))
		{
			obj->state |= OBJECT4D_STATE_CULLED;
			return 1;
		}
	}

	if (cull_flag & CULL_OBJECT_Y_PLANE)
	{
		float z_test = (float)(0.5) * viewplane_height * sphere_pos.z / view_dist;
		if (((sphere_pos.x + obj->max_radius) < -z_test) ||
			((sphere_pos.x - obj->max_radius) > z_test))
		{
			obj->state |= OBJECT4D_STATE_CULLED;
			return 1;
		}
	}
	return 0;
}

inline void Camera::remove_Backfaces(PObject4D obj)
{
	if (obj->state & OBJECT4D_STATE_CULLED)
		return;

	for (int poly = 0; poly < obj->num_polys; poly++)
	{
		PPoly4D curr_poly = &obj->plist[poly];

		if (!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->attr & POLY4D_ATTR_2SIDED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		int vert0 = curr_poly->vert[0];
		int vert1 = curr_poly->vert[1];
		int vert2 = curr_poly->vert[2];

		Vector4D u(&obj->vlist_trans[vert0], &obj->vlist_trans[vert1]);
		Vector4D v(&obj->vlist_trans[vert0], &obj->vlist_trans[vert2]);
		Vector4D n(u.cross(&v));
		Vector4D view(&obj->vlist_trans[vert0], &pos);

		//obj->vlist_local[vert0].normal = n;
		//obj->vlist_local[vert1].normal = n;
		//obj->vlist_local[vert2].normal = n;

		//n.print(); view.print();
		float dp = n.dot(&view);
		if (dp <= 0.0)
		{
			curr_poly->state |= POLY4D_STATE_BACKFACE;
			//std::cout << "remove plist";
		}
	}
}

inline void Camera::remove_Backfaces(PRenderList4D rlist)
{
	for (int poly = 0; poly < rlist->num_polys; poly++)
	{
		PPolyFace4D curr_poly = rlist->poly_ptrs[poly];

		if ((curr_poly == NULL) ||
			!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->attr & POLY4D_ATTR_2SIDED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		Vector4D u(&curr_poly->tvlist[0], &curr_poly->tvlist[1]);
		Vector4D v(&curr_poly->tvlist[0], &curr_poly->tvlist[2]);
		Vector4D n(u.cross(&v));
		Vector4D view(&curr_poly->tvlist[0], &pos);

		float dp = n.dot(&view);
		if (dp <= 0.0)
			curr_poly->state |= POLY4D_STATE_BACKFACE;
	}
}

inline void Camera::build_Screen_Matrix4x4(PMatrix4x4 m)
{
	//float alpha = 0.5 * viewport_width - 0.5;
	//float beta = 0.5 * viewport_height - 0.5;
	float alpha = (float)0.5 * viewport_width;
	float beta = (float)0.5 * viewport_height;
	m->init(alpha, 0, 0, 0,
		0, -beta, 0, 0,
		alpha, beta, 1, 0,
		0, 0, 0, 1);
}

inline void Camera::to_Perspective(PObject4D obj)
{
	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		float z = obj->vlist_trans[vertex].z;
		obj->vlist_trans[vertex].x = view_dist * obj->vlist_trans[vertex].x / z;
		obj->vlist_trans[vertex].y = view_dist * obj->vlist_trans[vertex].y * aspect_ratio / z;
	}
}

inline void Camera::to_Perspective(PRenderList4D rlist)
{
	for (int poly = 0; poly < rlist->num_polys; poly++)
	{
		PPolyFace4D curr_poly = rlist->poly_ptrs[poly];

		if ((curr_poly == NULL) ||
			!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		for (int vertex = 0; vertex < 3; vertex++)
		{
			float z = curr_poly->tvlist[vertex].z;
			curr_poly->tvlist[vertex].x = view_dist * curr_poly->tvlist[vertex].x / z;
			curr_poly->tvlist[vertex].y = view_dist * curr_poly->tvlist[vertex].y * aspect_ratio / z;
		}
	}
}

inline void Camera::to_Screen(PRenderList4D rlist)
{
	for (int poly = 0; poly < rlist->num_polys; poly++)
	{
		PPolyFace4D curr_poly = rlist->poly_ptrs[poly];

		if ((curr_poly == NULL) ||
			!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
			(curr_poly->state & POLY4D_STATE_CLIPPED) ||
			(curr_poly->state & POLY4D_STATE_BACKFACE))
			continue;

		float alpha = (float)0.5 * viewport_width;
		float beta = (float)0.5 * viewport_height;

		for (int vertex = 0; vertex < 3; vertex++)
		{
			curr_poly->tvlist[vertex].x = alpha + alpha * curr_poly->tvlist[vertex].x;
			curr_poly->tvlist[vertex].y = beta + beta * curr_poly->tvlist[vertex].y;
		}
	}
}

inline void Camera::to_Screen(PObject4D obj)
{
	//float alpha = 0.5 * viewport_width - 0.5;
	//float beta = 0.5 * viewport_height - 0.5;
	float alpha = (float)0.5 * viewport_width;
	float beta = (float)0.5 * viewport_height;

	for (int vertex = 0; vertex < obj->num_vertices; vertex++)
	{
		obj->vlist_trans[vertex].x = alpha + alpha * obj->vlist_trans[vertex].x;
		obj->vlist_trans[vertex].y = beta + beta * obj->vlist_trans[vertex].y;
	}
}

#endif