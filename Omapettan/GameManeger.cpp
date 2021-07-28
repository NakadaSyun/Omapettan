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
	c_testplayer = new c_TestPlayer(model_impostor);

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
	c_player->f_update();

	c_testplayer->f_update();

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
	c_testplayer->f_draw();
	c_dispUI->f_draw();
}

