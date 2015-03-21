#include "stdafx.h"
std::ofstream RunLog("log/Runlog.txt", std::ofstream::app);

#define RUN_ASSERT(condition, output) if (condition) { \
	std::cout << output << std::endl; \
	RunLog << output << std::endl; \
}

#define UNITTEST_MODE

extern double sin_table[361];
extern double cos_table[361];

#ifndef UNITTEST_MODE
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LWindow win;

	win.Create(480, 480, hInstance);
	win.MsgLoop();

	return 0;
}

#else

int main()
{
	//AutoTest();

	PObject4DV1 obj;
	double scale = 1.0;
	PVector4D pos = new Vector4D(0, 0, 0, 1);
	PVector4D rot = new Vector4D(0, 0, 0, 1);

	std::vector<std::string> data;
	std::string line, tmp;
	std::ifstream ifs("load/test.txt");
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

	
	


	return 0;
}

#endif

