#include "DxLib.h"
#include "GameManeger.h"

VECTOR Playerposition;

// 初期化
void c_GameManeger::f_init()
{
	f_RoadModel();


	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(model_Plane, VGet(0.0f,-100.0f,0.0f));

	c_player = new c_Player(model_impostor);

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera = new c_CameraCon();

	c_dispUI = new c_DispUI();

}

void c_GameManeger::f_RoadModel()
{
	// ３Ｄモデルの読み込み
	model_impostor = MV1LoadModel("models/among us.mv1");
	model_Plane = MV1LoadModel("models/Plane.mv1");
}

// ゲーム更新
void c_GameManeger::f_update()
{
	c_player->f_update();

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera->f_update();
}

void c_GameManeger::f_output()
{
	//c_Dc->f_create(0, 0, 50, 640, 20, 250);

	//床の生成
	MV1DrawModel(model_Plane);
	c_player->f_draw();
	c_dispUI->f_draw();
}

