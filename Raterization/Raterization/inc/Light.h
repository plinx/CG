#ifndef Light_h
#define Light_h

enum LightType
{
	// delete ambient light
	//LIGHT_ATTR_AMBIENT = 1,
	LIGHT_ATTR_INFINITE = 1,
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

	//Color ambient;
	Color diffuse;
	Color specular;

	Point4D pos;
	Vector4D dir;
	float kc, kl, kq;
	float spot_inner, spot_outter;
	float powerfactor;

	Light() = default;
	~Light() = default;
	Light(const Light& rhs) { *this = rhs; }
	Light(int i, int s, int a, const Color& diff, const Color& spec,
		const Point4D& p, const Vector4D& d, float c, float l, float q,
		float inner, float outter, float pf)
		//: id(i), state(s), attr(a), ambient(amb), diffuse(diff), specular(spec),
		: id(i), state(s), attr(a), diffuse(diff), specular(spec),
		pos(p), dir(d), kc(c), kl(l), kq(q),
		spot_inner(inner), spot_outter(outter), powerfactor(pf) {}

	int init(int s, int i, int a, const Color& diff, const Color& spec,
		const Point4D& p, const Vector4D& d, float c, float l, float q,
		float inner, float outter, float pf);
	int reset();

	Light& operator=(const Light& rhs) {
		id = rhs.id; state = rhs.state; attr = rhs.attr;
		diffuse = rhs.diffuse; specular = rhs.specular;
		pos = rhs.pos; dir = rhs.dir; kc = rhs.kc; kl = rhs.kl; kq = rhs.kq;
		spot_inner = rhs.spot_inner; spot_outter = rhs.spot_outter; powerfactor = rhs.powerfactor;
		return *this;
	}
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

	int rayOn(PObject4D obj)// , PCamera cam)
	{
		int Rbase, Gbase, Bbase, Rsum, Gsum, Bsum;// , shaded_color;
		float dp;// , dist, intensity, nl, atten;
		//Color shaded_color;

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

			int vert0 = curr_poly->vert[0];
			int vert1 = curr_poly->vert[1];
			int vert2 = curr_poly->vert[2];

			Rbase = curr_poly->color.R;
			Gbase = curr_poly->color.G;
			Bbase = curr_poly->color.B;
			Rsum = Gsum = Bsum = 0;

			for (int i = 0; i < light_nums; i++)
			{
				if (list[i].state)
					continue;

				if (list[i].attr & LIGHT_ATTR_INFINITE)
				{
					Color light(list[i].diffuse);
					dp = obj->vlist_trans[vert0].normal.dot(&list[i].dir);
					if (dp <= 0.0)
					{
						obj->vlist_trans[vert0].color.init(
							(int)min(light.R * (-dp) + Rbase, 255),
							(int)min(light.G * (-dp) + Gbase, 255),
							(int)min(light.B * (-dp) + Bbase, 255));
							//min(Rbase - light.R * dp, 255), 
							//min(Gbase - light.G * dp, 255),
							//min(Bbase - light.B * dp, 255));
					}
					dp = obj->vlist_trans[vert1].normal.dot(&list[i].dir);
					if (dp <= 0.0)
					{
						obj->vlist_trans[vert1].color.init(
							//max(light.R * (-dp), Rbase),
							//max(light.G * (-dp), Gbase),
							//max(light.B * (-dp), Bbase));
							(int)min(light.R * (-dp) + Rbase, 255),
							(int)min(light.G * (-dp) + Gbase, 255),
							(int)min(light.B * (-dp) + Bbase, 255));
							//min(Rbase - light.R * dp, 255),
							//min(Gbase - light.G * dp, 255),
							//min(Bbase - light.B * dp, 255));
					}
					dp = obj->vlist_trans[vert2].normal.dot(&list[i].dir);
					if (dp <= 0.0)
					{
						obj->vlist_trans[vert2].color.init(
							//max(light.R * (-dp), Rbase),
							//max(light.G * (-dp), Gbase),
							//max(light.B * (-dp), Bbase));
							(int)min(light.R * (-dp) + Rbase, 255),
							(int)min(light.G * (-dp) + Gbase, 255),
							(int)min(light.B * (-dp) + Bbase, 255));
							//min(Rbase - light.R * dp, 255),
							//min(Gbase - light.G * dp, 255),
							//min(Bbase - light.B * dp, 255));
					}
				}
			} // end of iterator in light list

			//curr_poly->color.init(min(Rsum, 255), min(Gsum, 255), min(Bsum, 255));
		}
		return 1;
	}
};

// Light methods implement
inline int Light::init(int s, int i, int a, const Color& diff, const Color& spec,
	const Point4D& p, const Vector4D& d, float c, float l, float q,
	float inner, float outter, float pf)
{
	state = s; id = i; attr = a;
	diffuse = diff; specular = spec;
	pos = p; dir = d; kc = c; kl = l; kq = q;
	spot_inner = inner; spot_outter = outter;
	powerfactor = pf;

	return id;
}

// Light methods implement

#endif