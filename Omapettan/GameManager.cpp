#include "DxLib.h"
#include "GameManager.h"


extern Sound g_Snd;
VECTOR Playerposition;

// 初期化
void c_GameManager::f_init()
{
	f_RoadModel();
	f_RoadImage();

	// カメラの描画距離をセット
	SetCameraNearFar(100.0f, 50000.0f);

	// ３Ｄモデルに新しい座標をセット
	//MV1SetPosition(model_Plane, VGet(0.0f,-100.0f,0.0f));
	MV1SetPosition(model_Arm, VGet(0.0f, 0.0f, 0.0f));
	//MV1SetDifColorScale(model_Arm, GetColorF(0.8f, 0.6f, 0.4f, 1.0f));

	MV1SetPosition(model_Sphere, VGet(0.0f, -850.0f, 0.0f));

	MV1SetPosition(model_SkyBox, VGet(0.0f, 760.0f, 10000.0f));


	c_player = new c_Player(model_impostor);

	Playerposition = c_player->f_GetPlayerPosition();

	c_camera = new c_CameraCon();

	c_dispUI = new c_DispUI();

	//c_stage = new c_Stage(model_Plane);

	c_stage = new c_Stage(model_Arm);

	c_acne = new c_Acne(model_Acne, image_Acne, model_Bandage);

	c_pad = new c_GamePad();

	c_mainUI = new c_MainUI(image_Bansoko);

	c_hair = new c_Hair(model_Cylinder, image_Cylinder);

	c_hair->f_GetAcnePosZ(c_acne);
}

// モデルの読み込み
void c_GameManager::f_RoadModel()
{
	// ３Ｄモデルの読み込み
	model_impostor = MV1LoadModel("models/among us.mv1");
	model_Plane = MV1LoadModel("models/Plane.mv1");
	model_Sphere = MV1LoadModel("models/TestSphere.mv1");
	model_Cylinder = MV1LoadModel("models/cylinder.mv1");
	model_Arm = MV1LoadModel("models/arm3.mv1");
	model_SkyBox = MV1LoadModel("models/roomBox.mv1");
	model_Acne = MV1LoadModel("models/dekimono.mv1");
	model_Bandage = MV1LoadModel("models/Bandage.mv1");
	
}

void c_GameManager::f_RoadImage() 
{
	// 画像の読み込み
	image_Cylinder = LoadGraph("images/hairtexture_brack.bmp");
	image_Acne = LoadGraph("images/acne.bmp");
	image_Bansoko = LoadGraph("images/Bansoko.png");

}

// ゲーム更新
void c_GameManager::f_update()
{
	bool Isfall = f_HitCheck(*c_player->c_colision, *c_stage->c_colision);
	int DamegeSound = GetRand(3);

	// プレイヤーと各毛の当たり判定
	for (int num = 0; num < HAIR_NUM; num++)
	{
		//c_hair->HitHair[num] = f_HitCheck(*c_player->c_colision, *c_hair->c_colision[num]);
		if (f_HitCheck(*c_hair->c_colision[num], *c_player->c_colision) == false) {
			c_hair->f_getRotationY(num, c_player->f_GetPlayerRotationY());
			c_hair->f_hairCut(num);
			c_pad->f_HairCutVibration();
			printf("%d\n", num);
		}
	}

	for (int i = 0; i < ACNE_NUM; i++) {
		if (f_HitCheck(*c_acne->c_collision[i], *c_player->c_colision) == false){
			if (c_acne->status[i] == 0) {
				c_pad->f_AcneCutVibration();
				c_acne->status[i] = 1;
				PlaySoundMem(g_Snd.Customer_Damage, DX_PLAYTYPE_BACK);
				PlaySoundMem(g_Snd.Customer_Cry[DamegeSound], DX_PLAYTYPE_BACK);
			}
			else {
				c_player->IsAcneHit = true;
				c_stage->IsAcneHit = true;
			}
		}
	}
	

	////毛の当たり判定用のデバッグ
	//for (int num = 0; num < HAIR_NUM; num++)
	//{
	//	if (!c_hair->HitHair[num])
	//	{
	//		//printf("atatta");
	//		std::cout << "HitHair" << num << "is" << c_hair->HitHair[num] << std::endl;
	//		c_hair->HitHair[num] = true;
	//	}
	//}

	// 一時停止用フラグ
	if (c_mainUI->pauseFlg == false) {

		c_player->f_update(Isfall);

		Playerposition = c_player->f_GetPlayerPosition();

		c_camera->f_update();

		c_stage->f_update();
		c_hair->stageXRotation = c_stage->f_GetXRotation();
		c_acne->stageRotation = c_stage->f_GetXRotation();

		c_hair->f_update();

		c_acne->f_update();
	}

	c_mainUI->f_update();
	for (int i = 0; i < HAIR_NUM; i++) {
		c_mainUI->hairStateFlg[i] = c_hair->HitHair[i];
	}
	for (int i = 0; i < ACNE_NUM; i++) {
		c_mainUI->acneStateFlg[i] = c_acne->status[i];
	}

	//背景移動のアップデート
	MV1SetRotationXYZ(model_SkyBox, VGet(c_hair->stageXRotation, DX_PI_F / 2, 0.0f));
}

// 出力(描画)
void c_GameManager::f_output()
{
	f_SkyBoxDraw();
	c_stage->f_output();
	c_player->f_draw();
	c_dispUI->f_draw();
	c_hair->f_output();
	c_acne->f_output();
	c_mainUI->f_draw();
}

// 背景の描画
void c_GameManager::f_SkyBoxDraw()
{
	SetUseLighting(FALSE);
	MV1DrawModel(model_SkyBox);
	SetUseLighting(TRUE);
}

// 衝突判定
bool c_GameManager::f_HitCheck(c_Collision col1, c_Collision col2) {
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

