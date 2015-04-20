#ifndef Light_h
#define Light_h

enum LightType
{
	LIGHT_ATTR_AMBIENT = 0,
	LIGHT_ATTR_INFINITE,
	LIGHT_ATTR_POINT,
};

enum LightState
{
	LIGHT_ON = 0,
	LIGHT_OFF,
	LIGHT_MAX_NUMS = 8,
};

struct Light
{
	int id;
	int state;
	int attr;

	Color ambient;
	Color diffuse;
	Color specular;

	Point4D pos;
	Vector4D dir;
	double kc, kl, kq;
	double spot_inner, spot_outter;
	double powerfactor;

	Light() = default;
	~Light() = default;
	Light(int i, int s, int a, const Color& amb, const Color& diff, const Color& spec,
		const Point4D& p, const Vector4D& d, double c, double l, double q,
		double inner, double outter, double pf)
		: id(i), state(s), attr(a), ambient(amb), diffuse(diff), specular(spec),
		pos(p), dir(d), kc(c), kl(l), kq(q),
		spot_inner(inner), spot_outter(outter), powerfactor(pf) {}

	int init(int s, int i, int a, const Color& amb, const Color& diff, const Color& spec,
		const Point4D& p, const Vector4D& d, double c, double l, double q,
		double inner, double outter, double pf);
	int reset();

};
typedef Light* PLight;

struct LightList
{
	Light list[LIGHT_MAX_NUMS];
	int light_nums;

	LightList() { light_nums = 0; }
	~LightList() = default;

	void insert(Light light)
	{
		list[light.id] = light;
		light_nums++;
	}

	int on(PObject4D obj)// , PCamera cam)
	{
		int Rbase, Gbase, Bbase, Rsum, Gsum, Bsum;// , shaded_color;
		double dp, dist, intensity;// , nl, atten;
		//Color shaded_color;

		if (!(obj->state & OBJECT4D_STATE_ACTIVE) ||
			(obj->state & OBJECT4D_STATE_CULLED) ||
			!(obj->state & OBJECT4D_STATE_VISIBLE))
			return 0;


		for (int poly = 0; poly < obj->num_polys; poly++)
		{
			PPoly4D curr_poly = &obj->plist[poly];
			int index0 = curr_poly->vert[0];
			int index1 = curr_poly->vert[1];
			int index2 = curr_poly->vert[2];

			if (!(curr_poly->state & POLY4D_STATE_ACTIVE) ||
				(curr_poly->state & POLY4D_STATE_CLIPPED) ||
				(curr_poly->state & POLY4D_STATE_BACKFACE))
				continue;

			Rbase = curr_poly->color.R;
			Gbase = curr_poly->color.G;
			Bbase = curr_poly->color.B;
			Rsum = Gsum = Bsum = 0;

			for (int i = 0; i < light_nums; i++)
			{
				if (list[i].state)
					continue;

				if (list[i].attr & LIGHT_ATTR_AMBIENT)
				{
					Rsum += list[i].ambient.R * Rbase / 255;
					Gsum += list[i].ambient.G * Gbase / 255;
					Bsum += list[i].ambient.B * Bbase / 255;
				}
				/*else if (it->attr & LIGHT_ATTR_INFINITE)
				{
					Vector4D u, v, n;

					u.init(&obj->vlist_trans[index0], &obj->vlist_trans[index1]);
					v.init(&obj->vlist_trans[index0], &obj->vlist_trans[index2]);
					n = u.cross(&v);

					dp = n.dot(&it->dir);

					if (dp > 0)
					{

					}
				}*/
			} // end of iterator in light list

			curr_poly->color.init(max(Rsum, 255), max(Gsum, 255), max(Bsum, 255));
		}
		return 1;
	}
};

// Light methods implement
inline int Light::init(int s, int i, int a, const Color& amb, const Color& diff, const Color& spec,
	const Point4D& p, const Vector4D& d, double c, double l, double q,
	double inner, double outter, double pf)
{
	state = s; id = i; attr = a;
	ambient = amb; diffuse = diff; specular = spec;
	pos = p; dir = d; kc = c; kl = l; kq = q;
	spot_inner = inner; spot_outter = outter;
	powerfactor = pf;

	return id;
}

// Light methods implement

#endif