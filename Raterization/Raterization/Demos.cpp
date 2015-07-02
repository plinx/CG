#include "Demos.h"

void TriangleDemo()
{
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
	poly1.color.init(0, 0, 0);

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
		static float ang_y = 300;
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
		rlist.rotate(&mrot, TRANSFORM_LOCAL_TO_TRANS);
		rlist.to_World(&poly_pos, TRANSFORM_TRANS_ONLY);
		camera.build_Euler(CAM_ROT_SEQ_ZYX);
		camera.from_World(&rlist);
		camera.to_Perspective(&rlist);
		camera.to_Screen(&rlist);
		rlist.poly_data[0].vlist[0].print();
		rlist.poly_data[0].vlist[1].print();
		rlist.poly_data[0].vlist[2].print(); std::cout << std::endl;
		rlist.poly_data[0].tvlist[0].print();
		rlist.poly_data[0].tvlist[1].print();
		rlist.poly_data[0].tvlist[2].print(); std::cout << std::endl;
		//std::cout << rlist.poly_data[0].vlist[1].x << " " << rlist.poly_data[0].vlist[1].y << " | ";
		//std::cout << rlist.poly_data[0].vlist[2].x << " " << rlist.poly_data[0].vlist[2].y << std::endl;
	}
}

void CubeDemo1()
{
	Point4D cam_pos(0, 0, -10, 1);
	Point4D cam_target(0, 0, 0, 0);
	Vector4D cam_dir(0, 0, 0, 1);
	Vector4D vscale(0.5, 0.5, 0.5, 1), vpos(0, 0, 0, 1), vrot(0, 0, 0, 1);
	Point4D poly_pos(0, 0, 10, 1);
	Camera camera(0, cam_pos, cam_dir, cam_target, 50.0, 500.0, 90.0, 400, 400);
	Object4D obj;
	Matrix4x4 mrot;

	Build_SinCos_Tables();
	Load_Object4D_PLG(&obj, "resource/cube1.plg", &vscale, &vpos, &vrot);

	mrot.build(0, 15, 0);
	obj.rotate(&mrot, TRANSFORM_LOCAL_ONLY, 1);
	obj.to_World();
	camera.build_Euler(CAM_ROT_SEQ_ZYX);
	camera.from_World(&obj);
	camera.to_Perspective(&obj);
	camera.to_Screen(&obj);
	for (auto poly = 0; poly < obj.num_polys; poly++)
	{
		if (!(obj.plist[poly].state & POLY4D_STATE_ACTIVE) ||
			(obj.plist[poly].state & POLY4D_STATE_CLIPPED) ||
			(obj.plist[poly].state & POLY4D_STATE_BACKFACE))
			continue;

		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[0]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[0]].y << ")";
		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[1]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[1]].y << ")";
		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[2]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[2]].y << ")";
		std::cout << std::endl;
	}

}

void CubeDemo2()
{
	Point4D cam_pos(0, 0, -10, 1);
	Point4D cam_target(0, 0, 0, 0);
	Vector4D cam_dir(0, 0, 0, 1);
	Vector4D vscale(0.5, 0.5, 0.5, 1), vpos(0, 0, 0, 1), vrot(0, 0, 0, 1);
	Point4D poly_pos(0, 0, 10, 1);
	Camera camera(0, cam_pos, cam_dir, cam_target, 50.0, 500.0, 90.0, 400, 400);
	Object4D obj;
	Matrix4x4 mrot;

	Build_SinCos_Tables();
	Load_Object4D_PLG(&obj, "resource/cube2.plg", &vscale, &vpos, &vrot);

	mrot.build(0, 0, 0);
	obj.rotate(&mrot, TRANSFORM_LOCAL_ONLY, 1);
	obj.to_World();
	camera.build_Euler(CAM_ROT_SEQ_ZYX);
	camera.remove_Backfaces(&obj);
	camera.from_World(&obj);
	camera.to_Perspective(&obj);
	camera.to_Screen(&obj);
	for (auto poly = 0; poly < obj.num_polys; poly++)
	{
		if (!(obj.plist[poly].state & POLY4D_STATE_ACTIVE) ||
			(obj.plist[poly].state & POLY4D_STATE_CLIPPED) ||
			(obj.plist[poly].state & POLY4D_STATE_BACKFACE))
			continue;

		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[0]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[0]].y << ")";
		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[1]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[1]].y << ")";
		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[2]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[2]].y << ")";
		std::cout << std::endl;
	}
	obj.reset();
	mrot.build(0, 45, 0);
	obj.rotate(&mrot, TRANSFORM_LOCAL_ONLY, 1);
	obj.to_World();
	camera.build_Euler(CAM_ROT_SEQ_ZYX);
	camera.remove_Backfaces(&obj);
	camera.from_World(&obj);
	camera.to_Perspective(&obj);
	camera.to_Screen(&obj);
	for (auto poly = 0; poly < obj.num_polys; poly++)
	{
		if (!(obj.plist[poly].state & POLY4D_STATE_ACTIVE) ||
			(obj.plist[poly].state & POLY4D_STATE_CLIPPED) ||
			(obj.plist[poly].state & POLY4D_STATE_BACKFACE))
			continue;

		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[0]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[0]].y << ")";
		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[1]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[1]].y << ")";
		std::cout << "(" << obj.vlist_trans[obj.plist[poly].vert[2]].x << ","
			<< obj.vlist_trans[obj.plist[poly].vert[2]].y << ")";
		std::cout << std::endl;
	}
}

void TankDemo1()
{
	Point4D cam_pos(0, 0, -100, 1);
	Point4D cam_target(0, 0, 0, 0);
	Vector4D cam_dir(0, 0, 0, 1);
	Vector4D vscale(0.5, 0.5, 0.5, 1), vpos(0, 0, 0, 1), vrot(0, 0, 0, 1);
	Point4D poly_pos(0, 0, 100, 1);
	Camera camera(0, cam_pos, cam_dir, cam_target, 50.0, 500.0, 90.0, 400, 400);
	RenderList4D rlist;
	Object4D obj;
	Matrix4x4 mrot;

	Build_SinCos_Tables();
	Load_Object4D_PLG(&obj, "resource/tank1.plg", &vscale, &vpos, &vrot);

	mrot.build(0, 0, 0);

	//obj.rotate(&mrot, TRANSFORM_LOCAL_ONLY, 1);
	rlist.insert(&obj);
	rlist.rotate(&mrot, TRANSFORM_LOCAL_TO_TRANS);
	obj.to_World(TRANSFORM_LOCAL_TO_TRANS);
	obj.world_pos = poly_pos;
	obj.world_pos.z += 100;
	obj.to_World(TRANSFORM_TRANS_ONLY);
	obj.vlist_local[0].print();
	obj.vlist_local[1].print();
	std::cout << std::endl;
	rlist.insert(&obj);
	rlist.poly_data[0].vlist[0].print();
	rlist.poly_data[0].vlist[1].print();
	std::cout << std::endl;
	rlist.rotate(&mrot, TRANSFORM_LOCAL_TO_TRANS);
	rlist.to_World(&poly_pos, TRANSFORM_TRANS_ONLY);
	camera.build_Euler(CAM_ROT_SEQ_ZYX);
	camera.remove_Backfaces(&rlist);
	camera.from_World(&rlist);
	camera.to_Perspective(&rlist);
	camera.to_Screen(&rlist);

	std::cout << "(" << rlist.poly_data[0].tvlist[0].x << ","
		<< rlist.poly_data[0].tvlist[0].y << ")";
	std::cout << "(" << rlist.poly_data[0].tvlist[1].x << ","
		<< rlist.poly_data[0].tvlist[1].y << ")";
	std::cout << "(" << rlist.poly_data[0].tvlist[2].x << ","
		<< rlist.poly_data[0].tvlist[2].y << ")";
	std::cout << std::endl;
	std::cout << "(" << rlist.poly_ptrs[0]->tvlist[0].x << ","
		<< rlist.poly_ptrs[0]->tvlist[0].y << ")";
	std::cout << "(" << rlist.poly_ptrs[0]->tvlist[1].x << ","
		<< rlist.poly_ptrs[0]->tvlist[1].y << ")";
	std::cout << "(" << rlist.poly_ptrs[0]->tvlist[2].x << ","
		<< rlist.poly_ptrs[0]->tvlist[2].y << ")";;
	std::cout << std::endl;
	std::cout << "(" << rlist.poly_data[19].tvlist[0].x << ","
		<< rlist.poly_data[19].tvlist[0].y << ")";
	std::cout << "(" << rlist.poly_data[19].tvlist[1].x << ","
		<< rlist.poly_data[19].tvlist[1].y << ")";
	std::cout << "(" << rlist.poly_data[19].tvlist[2].x << ","
		<< rlist.poly_data[19].tvlist[2].y << ")";
	std::cout << std::endl;
	std::cout << "(" << rlist.poly_ptrs[19]->tvlist[0].x << ","
		<< rlist.poly_ptrs[19]->tvlist[0].y << ")";
	std::cout << "(" << rlist.poly_ptrs[19]->tvlist[1].x << ","
		<< rlist.poly_ptrs[19]->tvlist[1].y << ")";
	std::cout << "(" << rlist.poly_ptrs[19]->tvlist[2].x << ","
		<< rlist.poly_ptrs[19]->tvlist[2].y << ")";;
	std::cout << std::endl;

	int poly = 0;
	PPolyFace4D curr_poly = rlist.poly_ptrs[poly];
	std::cout << "curr_poly0 : (" << curr_poly->tvlist[1].x
		<< "," << curr_poly->tvlist[1].y << ")" << std::endl;
	poly = 19;
	curr_poly = rlist.poly_ptrs[poly];
	std::cout << "curr_poly1 : (" << curr_poly->tvlist[1].x
		<< "," << curr_poly->tvlist[1].y << ")" << std::endl;
}


