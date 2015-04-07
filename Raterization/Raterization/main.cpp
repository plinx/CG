#include "stdafx.h"

std::ofstream RunLog("log/Runlog.txt", std::ofstream::app);

#define RUN_ASSERT(condition, output) if (condition) { \
	std::cout << output << std::endl; \
	RunLog << output << std::endl; \
}

//#define UNITTEST_MODE 
#undef UNITTEST_MODE 

extern double sin_table[361];
extern double cos_table[361];

#ifndef UNITTEST_MODE
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	LWindow win;

	win.Create(480, 480, hInstance);
	win.Render();

	return 0;
}

#else

int main()
{
	//AutoTest();
	Point4D cam_pos(0, 0, -100, 1);
	Point4D cam_target(0, 0, 0, 0);
	Vector4D cam_dir(0, 0, 0, 1);
	Vector4D vscale(0.5, 0.5, 0.5, 1), vpos(0, 0, 0, 1), vrot(0, 0, 0, 1);
	Camera camera;
	RenderList4D rlist;
	PolyFace4D poly1;
	Point4D poly_pos(0, 0, 100, 1);

	Build_SinCos_Tables();

	poly1.state = POLY4D_STATE_ACTIVE;
	poly1.attr = 0;
	poly1.color = RGB(0, 0, 0);

	poly1.vlist[0].x = 0;
	poly1.vlist[0].y = 50;
	poly1.vlist[0].z = 0;
	poly1.vlist[0].w = 1;

	poly1.vlist[1].x = 50;
	poly1.vlist[1].y = -50;
	poly1.vlist[1].z = 0;
	poly1.vlist[1].w = 1;

	poly1.vlist[2].x = -50;
	poly1.vlist[2].y = -50;
	poly1.vlist[2].z = 0;
	poly1.vlist[2].w = 1;

	poly1.next = NULL;
	poly1.prev = NULL;

	camera = Camera(0, cam_pos, cam_dir, cam_target, 50.0, 500.0, 90.0, 400, 400);
	// need the reset func in renderlist
	rlist.num_polys = 1;

	// need the insert func in rederlist
	rlist.poly_ptrs[0] = &rlist.poly_data[0];
	rlist.poly_data[0] = poly1;
	
	for (int i = 0; i < 90; i++)
	{
		static Matrix4x4 mrot;
		static double ang_y = 300;
		rlist.poly_data[0] = poly1;
		rlist.poly_data[0].vlist[0].print();
		rlist.poly_data[0].vlist[1].print();
		rlist.poly_data[0].vlist[2].print(); std::cout << std::endl;

		/*std::cout << mrot.v[0][0] << " " << mrot.v[0][1] << " " << mrot.v[0][2] << " " << mrot.v[0][3] << std::endl
			<< mrot.v[1][0] << " " << mrot.v[1][1] << " " << mrot.v[1][2] << " " << mrot.v[1][3] << std::endl
			<< mrot.v[2][0] << " " << mrot.v[2][1] << " " << mrot.v[2][2] << " " << mrot.v[2][3] << std::endl
			<< mrot.v[3][0] << " " << mrot.v[3][1] << " " << mrot.v[3][2] << " " << mrot.v[3][3] << std::endl;*/
		mrot.build(0, ang_y, 0);
		//std::cout << "fastsin : " << Fast_sin(ang_y) << " fastcos : " << Fast_cos(ang_y) << std::endl;
		/*std::cout << mrot.v[0][0] << "\t" << mrot.v[0][1] << "\t" << mrot.v[0][2] << "\t" << mrot.v[0][3] << std::endl
			<< mrot.v[1][0] << "\t\t" << mrot.v[1][1] << "\t" << mrot.v[1][2] << "\t\t" << mrot.v[1][3] << std::endl
			<< mrot.v[2][0] << "\t" << mrot.v[2][1] << "\t" << mrot.v[2][2] << "\t" << mrot.v[2][3] << std::endl
			<< mrot.v[3][0] << "\t\t" << mrot.v[3][1] << "\t" << mrot.v[3][2] << "\t\t" << mrot.v[3][3] << std::endl;*/
		
		if (++ang_y >= 360.0) ang_y = 0;
		rlist.transform(&mrot, TRANSFORM_LOCAL_TO_TRANS);
		rlist.transformWorld(&poly_pos, TRANSFORM_TRANS_ONLY);
		camera.build_Euler(CAM_ROT_SEQ_ZYX);
		camera.transformWorld(&rlist);
		camera.to_Perspective_Screen(&rlist);
		camera.perspective_to_Renderlist(&rlist);
		rlist.poly_data[0].vlist[0].print();
		rlist.poly_data[0].vlist[1].print();
		rlist.poly_data[0].vlist[2].print(); std::cout << std::endl;
		rlist.poly_data[0].tvlist[0].print();
		rlist.poly_data[0].tvlist[1].print();
		rlist.poly_data[0].tvlist[2].print(); std::cout << std::endl;
		//std::cout << rlist.poly_data[0].vlist[1].x << " " << rlist.poly_data[0].vlist[1].y << " | ";
		//std::cout << rlist.poly_data[0].vlist[2].x << " " << rlist.poly_data[0].vlist[2].y << std::endl;
	}

	system("pause");

	return 0;
}

#endif

