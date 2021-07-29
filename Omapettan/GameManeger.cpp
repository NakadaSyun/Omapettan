#include "DxLib.h"
#include "GameManeger.h"

VECTOR Playerposition;

// 初期化
void c_GameManeger::f_init()
{
	f_RoadModel();


	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(model_Plane, VGet(0.0f,-100.0f,0.0f));

	MV1SetPosition(model_Sphere, VGet(0.0f, -850.0f, 0.0f));			//球体


	c_player = new c_Player(model_impostor);

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera = new c_CameraCon();

	c_dispUI = new c_DispUI();

	c_stage = new c_Stage(model_Plane);

}

void c_GameManeger::f_RoadModel()
{
	// ３Ｄモデルの読み込み
	model_impostor = MV1LoadModel("models/among us.mv1");
	model_Plane = MV1LoadModel("models/Plane.mv1");
	model_Sphere = MV1LoadModel("models/TestSphere.mv1");
	model_Cylinder = MV1LoadModel("models/cylinder.mv1");
}

// ゲーム更新
void c_GameManeger::f_update()
{
	bool Isfall = f_HitCheck(*c_player->c_colision, *c_stage->c_colision);
	c_player->f_update(Isfall);

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera->f_update();

	c_stage->f_update();

}

void c_GameManeger::f_output()
{
	//c_Dc->f_create(0, 0, 50, 640, 20, 250);

	//床の生成
	//MV1DrawModel(model_Plane);
	//球体の生成
	//MV1SetScale(model_Sphere, VGet(3.0f, 3.0f, 3.0f));
	//MV1DrawModel(model_Sphere);
	//for (int x = 0; x < 64; x++) {
	//	MV1SetPosition(model_Cylinder, VGet(0.0f + (x * 50), 0.0f, 0.0f));
	//	MV1DrawModel(model_Cylinder);
	//}
									//exeファイルだと正常に動作しないので一旦コメント化
	c_stage->f_output();
	c_player->f_draw();
	c_dispUI->f_draw();
}

bool c_GameManeger::f_HitCheck(c_Collision col1, c_Collision col2) {
	VECTOR Cubevertex1[8];        //四角形の頂点8
	VECTOR Cubevertex2[8];        //四角形の頂点8


	//頂点座標の設定
	Cubevertex1[0] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y, col1.pos.z - (col1.depth / 2));																			//
	Cubevertex1[1] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y, col1.pos.z - (col1.depth / 2));
	Cubevertex1[2] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z - (col1.depth / 2));
	Cubevertex1[3] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z - (col1.depth / 2));
	Cubevertex1[4] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y, col1.pos.z + (col1.depth / 2));
	Cubevertex1[5] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y, col1.pos.z + (col1.depth / 2));
	Cubevertex1[6] = VGet(col1.pos.x - (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));
	Cubevertex1[7] = VGet(col1.pos.x + (col1.wide / 2), col1.pos.y + col1.hight, col1.pos.z + (col1.depth / 2));

	Cubevertex2[0] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y, col2.pos.z - (col2.depth / 2));
	Cubevertex2[1] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y, col2.pos.z - (col2.depth / 2));
	Cubevertex2[2] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z - (col2.depth / 2));
	Cubevertex2[3] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z - (col2.depth / 2));
	Cubevertex2[4] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y, col2.pos.z + (col2.depth / 2));
	Cubevertex2[5] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y, col2.pos.z + (col2.depth / 2));
	Cubevertex2[6] = VGet(col2.pos.x - (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z + (col2.depth / 2));
	Cubevertex2[7] = VGet(col2.pos.x + (col2.wide / 2), col2.pos.y + col2.hight, col2.pos.z + (col2.depth / 2));


	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[1], Cubevertex1[2], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return false;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[4], Cubevertex1[6], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return false;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[4], Cubevertex1[5], Cubevertex1[7], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return false;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[1], Cubevertex1[5], Cubevertex1[3], Cubevertex2[0], Cubevertex2[1], Cubevertex2[4])) {
		return false;
	}


	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[1], Cubevertex1[2], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return false;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[0], Cubevertex1[4], Cubevertex1[6], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return false;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[4], Cubevertex1[5], Cubevertex1[7], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return false;
	}
	if (HitCheck_Triangle_Triangle(Cubevertex1[1], Cubevertex1[5], Cubevertex1[3], Cubevertex2[1], Cubevertex2[4], Cubevertex2[5])) {
		return false;
	}
	return true;
}

