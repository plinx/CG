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

	double view_h, view_v;
	double view_dist;
	double fov;

	double near_clip, far_clip;

	Plane3D right_plane, left_plane, top_plane, bottom_plane;

	double viewplane_width, viewplane_height;
	double viewport_width, viewport_height, viewport_cx, viewport_cy;
	double aspect_ratio;

	Matrix4x4 mcam, mper, mscr;

	Camera() = default;
	~Camera() = default;
	Camera(int a, Point4D p, Vector4D d, Point4D t,
		double nc, double fc, double f, double w, double h)
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
		viewplane_height = 2.0 / aspect_ratio;
		double tan_fov_div2 = tan(Angle_to_Radian(fov / 2));
		view_dist = (0.5) * viewplane_width * tan_fov_div2;
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
			Vector3D vn(view_dist, 0, -viewplane_width / 2.0);
			right_plane.init(pt_origin, vn, 1);
			vn.init(-(int)view_dist, 0, -viewplane_width / 2.0);
			left_plane.init(pt_origin, vn, 1);
			vn.init(0, view_dist, -viewplane_height / 2.0);
			top_plane.init(pt_origin, vn, 1);
			vn.init(0, -view_dist, -viewplane_width / 2.0);
			bottom_plane.init(pt_origin, vn, 1);
		}
	}

	void init(int a, Point4D p, Vector4D d, Point4D t,
		double nc, double fc, double f, double w, double h)
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
		viewplane_height = 2.0 / aspect_ratio;
		double tan_fov_div2 = tan(Angle_to_Radian(fov / 2));
		view_dist = (0.5) * viewplane_width * tan_fov_div2;
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
			Vector3D vn(view_dist, 0, -viewplane_width / 2.0);
			right_plane.init(pt_origin, vn, 1);
			vn.init(-(int)view_dist, 0, -viewplane_width / 2.0);
			left_plane.init(pt_origin, vn, 1);
			vn.init(0, view_dist, -viewplane_height / 2.0);
			top_plane.init(pt_origin, vn, 1);
			vn.init(0, -view_dist, -viewplane_width / 2.0);
			bottom_plane.init(pt_origin, vn, 1);
		}
	}

	void build_Euler(int cam_rot_seq)
	{
		Matrix4x4 mt_inv, mx_inv, my_inv, mz_inv, mrot, mtmp;
		mt_inv.init(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-pos.x, -pos.y, -pos.z, 1);

		double theta_x = dir.x;
		double theta_y = dir.y;
		double theta_z = dir.z;

		double cos_theta = Fast_cos(theta_x);
		double sin_theta = -Fast_sin(theta_x);
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

	void build_UVN(int mode)
	{
		Matrix4x4 mt_inv, mt_uvn;// , mtmp;
		mt_inv.init(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-pos.x, -pos.y, -pos.z, 1);

		if (mode == UVN_MODE_SPHERICAL)
		{
			double phi = dir.x;
			double theta = dir.y;

			double sin_phi = Fast_sin(phi);
			double cos_phi = Fast_cos(phi);

			double sin_theta = Fast_sin(theta);
			double cos_theta = Fast_cos(theta);

			target.x = -1.0 * sin_phi * sin_theta;
			target.y = 1.0 * cos_phi;
			target.z = 1.0 * sin_phi * cos_theta;
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

	void transform_World(PObject4D obj)
	{
		for (int vertex = 0; vertex < obj->num_vertices; vertex++)
		{
			obj->vlist_trans[vertex] = mcam.mul(&obj->vlist_trans[vertex]);
		}
	}

	void transform_World(PRenderList4D rlist)
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

	int cull(PObject4D obj, int cull_flag)
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
			double z_test = (0.5) * viewplane_width * sphere_pos.z / view_dist;
			if (((sphere_pos.x + obj->max_radius) < -z_test) ||
				((sphere_pos.x - obj->max_radius) > z_test))
			{
				obj->state |= OBJECT4D_STATE_CULLED;
				return 1;
			}
		}

		if (cull_flag & CULL_OBJECT_Y_PLANE)
		{
			double z_test = (0.5) * viewplane_height * sphere_pos.z / view_dist;
			if (((sphere_pos.x + obj->max_radius) < -z_test) ||
				((sphere_pos.x - obj->max_radius) > z_test))
			{
				obj->state |= OBJECT4D_STATE_CULLED;
				return 1;
			}
		}
		return 0;
	}

	void remove_Backfaces(PObject4D obj)
	{
		if (obj->state & OBJECT4D_STATE_CULLED)
			return;

		for (int poly = 0; poly < obj->num_poly; poly++)
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

			//n.print(); view.print();
			double dp = n.dot(&view);
			if (dp <= 0.0)
			{
				curr_poly->state |= POLY4D_STATE_BACKFACE;
				//std::cout << "remove plist";
			}
		}
	}

	void remove_Backfaces(PRenderList4D rlist)
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

			Vector4D u, v, n;

			u.init(&curr_poly->tvlist[0], &curr_poly->tvlist[1]);
			v.init(&curr_poly->tvlist[0], &curr_poly->tvlist[2]);
			n = u.cross(&v);

			Vector4D view(&curr_poly->tvlist[0], &pos);

			double dp = n.dot(&view);
			if (dp <= 0.0)
				curr_poly->state |= POLY4D_STATE_BACKFACE;
		}
	}

	/*void perspective(PObject4D obj)
	{
		for (int vertex = 0; vertex < obj->num_vertices; vertex++)
		{
			double z = obj->vlist_trans[vertex].z;

			obj->vlist_trans[vertex].x = view_h * obj->vlist_trans[vertex].x / z;
			obj->vlist_trans[vertex].y = view_v * obj->vlist_trans[vertex].y * aspect_ratio / z;
		}
	}

	void perspective(PRenderList4D rlist)
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
				double z = curr_poly->tvlist[vertex].z;
				curr_poly->tvlist[vertex].x = view_h * curr_poly->vlist[vertex].x / z;
				curr_poly->tvlist[vertex].y = view_v * curr_poly->vlist[vertex].y * aspect_ratio / z;
			}
		}
	}

	void build_Perspective_Matrix4x4(PMatrix4x4 m)
	{
		m->init(view_h, 0, 0, 0,
			0, view_v * aspect_ratio, 0, 0,
			0, 0, 1, 1,
			0, 0, 0, 0);
	}*/
	
	void build_Screen_Matrix4x4(PMatrix4x4 m)
	{
		//double alpha = 0.5 * viewport_width - 0.5;
		//double beta = 0.5 * viewport_height - 0.5;
		double alpha = 0.5 * viewport_width;
		double beta = 0.5 * viewport_height;
		m->init(alpha, 0, 0, 0,
			0, -beta, 0, 0,
			alpha, beta, 1, 0,
			0, 0, 0, 1);
	}

	void to_Perspective(PObject4D obj)
	{
		for (int vertex = 0; vertex < obj->num_vertices; vertex++)
		{
			double z = obj->vlist_trans[vertex].z;
			obj->vlist_trans[vertex].x = view_dist * obj->vlist_trans[vertex].x /z;
			obj->vlist_trans[vertex].y = view_dist * obj->vlist_trans[vertex].y * aspect_ratio / z;
		}
	}

	void to_Perspective(PRenderList4D rlist)
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
				double z = curr_poly->tvlist[vertex].z;
				curr_poly->tvlist[vertex].x = view_dist * curr_poly->tvlist[vertex].x / z;
				curr_poly->tvlist[vertex].y = view_dist * curr_poly->tvlist[vertex].y * aspect_ratio /z;
			}
		}
	}

	void to_Screen(PRenderList4D rlist)
	{
		for (int poly = 0; poly < rlist->num_polys; poly++)
		{
			PPolyFace4D curr_poly = rlist->poly_ptrs[poly];

			if ((curr_poly == NULL) ||
				!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
				continue;

			double alpha = 0.5 * viewport_width;
			double beta = 0.5 * viewport_height;

			for (int vertex = 0; vertex < 3; vertex++)
			{
				curr_poly->tvlist[vertex].x = alpha + alpha * curr_poly->tvlist[vertex].x;
				curr_poly->tvlist[vertex].y = beta - beta * curr_poly->tvlist[vertex].y;
			}
		}
	}

	void to_Screen(PObject4D obj)
	{
		//double alpha = 0.5 * viewport_width - 0.5;
		//double beta = 0.5 * viewport_height - 0.5;
		double alpha = 0.5 * viewport_width;
		double beta = 0.5 * viewport_height;

		for (int vertex = 0; vertex < obj->num_vertices; vertex++)
		{
			obj->vlist_trans[vertex].x = alpha + alpha * obj->vlist_trans[vertex].x;
			obj->vlist_trans[vertex].y = beta - beta * obj->vlist_trans[vertex].y;
		}
	}

};
typedef Camera* PCamera;

#endif