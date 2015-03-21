#ifndef Camera_h
#define Camera_h

struct Cam4DV1
{
	int state;
	int attr;

	Point4D pos;
	Vector4D dir;
	Vector4D u, v, n;
	Point4D target;

	double horizon, vertical;
	double view_dist;
	double fov;

	double near_clip, far_clip;

	Plane3D right_plane, left_plane, top_plane, bottom_plane;

	double viewplane_width, viewplane_height;
	double viewport_width, viewport_height, viewport_cx, viewport_cy;
	double aspect_ratio;

	Matrix4x4 mcam, mper, mscr;

	Cam4DV1() = default;
	~Cam4DV1() = default;
	Cam4DV1(int a, Point4D p, Vector4D d, Point4D t,
		double nc, double fc, double f, double w, double h)
		: attr(a), pos(p), dir(d), target(t),
		near_clip(nc), far_clip(fc), fov(f), viewport_width(w), viewport_height(h)
	{
		u.init(1, 0, 0);
		v.init(0, 1, 0);
		n.init(0, 0, 1);
		viewport_cx = (viewport_width - 1) / 2;
		viewport_cy = (viewport_height - 1) / 2;
		aspect_ratio = viewport_width / viewplane_height;
		mcam.init(); 
		mper.init();
		mscr.init();
		viewplane_width = 2.0;
		viewplane_height = 2.0 / aspect_ratio;
		double tan_fov_div2 = tan(DEG_TO_RAD(fov / 2));
		view_dist = (0.5) * viewplane_height * tan_fov_div2;
		if (89.9 < fov && fov < 90.1)
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
};
typedef Cam4DV1* PCam4DV1;

#endif