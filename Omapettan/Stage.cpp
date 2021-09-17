#include "Stage.h"
#include <math.h>

#define PI 3.141592653589793

c_Stage::c_Stage(const int Model) {
	sModel = Model;
	// ３Ｄモデルの座標を初期化
	position = VGet(0.0f, 0.0f, 0.0f);

	MV1SetRotationXYZ(sModel, VGet(0.0f, PI / 2, 0.0f));

	c_colision = new c_Collision(position, 2000.0f, -200.0f, 2000.0f);
	Arm_XRotate = 0.0f;
	Arm_OldXRotate = 0.0f;

	IsAcneHit = false;

	c_pad = new c_GamePad();


	image_armTexture = LoadGraph("images/ArmTexture.004a.png");

	// マテリアルで使用されているテクスチャの番号を取得
	//int TexIndex = MV1GetMaterialDifMapTexture(sModel, 2);


}

c_Stage::~c_Stage() {
	delete c_colision;
	delete c_pad;
}

void c_Stage::f_init() {

	// ３Ｄモデルの座標を初期化
	position = VGet(0.0f, 0.0f, 0.0f);

}

void c_Stage::f_update() {
	c_pad->f_update();
	

	/*if (CheckHitKey(KEY_INPUT_A) == 1) {
		Arm_XRotate += 0.01f;
	}

	if (CheckHitKey(KEY_INPUT_D) == 1) {
		Arm_XRotate -= 0.01f;
	}*/
	
	///*******	コントローラーの入力	******/
	if (c_pad->LeftStick == LEFT) {
		if (c_pad->IsButton2 == TRUE) Arm_XRotate += 0.015f * Arm_RotateSpeed;
		else {
			Arm_XRotate += 0.01f;
		}
	}
	if (c_pad->LeftStick == LEFTUP || 
		c_pad->LeftStick == LEFTDOWN) {
		if(c_pad->IsButton2 == TRUE) Arm_XRotate += 0.015f * cos(PI / 4) * Arm_RotateSpeed;
		else {
			Arm_XRotate += 0.01f * cos(PI / 4);
		}
	}

	if (c_pad->LeftStick == RIGHT) {
		if (c_pad->IsButton2 == TRUE) Arm_XRotate -= 0.015f * Arm_RotateSpeed;
		else {
			Arm_XRotate -= 0.01f;
		}
	}
	
	if (c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == RIGHTDOWN) {
		if (c_pad->IsButton2 == TRUE) Arm_XRotate -= 0.015f * cos(PI / 4) * Arm_RotateSpeed;
		else {
			Arm_XRotate -= 0.01f * cos(PI / 4);
		}
	}

	if (IsAcneHit) {		//吹き出物に衝突していたら一フレーム前の回転値に戻す
		Arm_XRotate = Arm_XRotate - (Arm_XRotate - Arm_OldXRotate) * 5;
	}
	else {
		Arm_OldXRotate = Arm_XRotate;
	}

	MV1SetRotationXYZ(sModel, VGet(Arm_XRotate, PI / 2, 0.0f));
	IsAcneHit = false;
}

void c_Stage::f_output() {

	//マテリアルで使用されているテクスチャの番号を取得
	int Skin1 = MV1GetMaterialDifMapTexture(sModel, 0);
	//マテリアルで使用されているテクスチャの番号を取得
	int Skin2 = MV1GetMaterialDifMapTexture(sModel, 2);

	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(sModel, Skin1, image_armTexture, FALSE);
	// テクスチャで使用するグラフィックハンドルを変更する
	MV1SetTextureGraphHandle(sModel, Skin2, image_armTexture, FALSE);

	//床の生成
	MV1DrawModel(sModel);
}

float c_Stage::f_GetXRotation() {
	return Arm_XRotate;
}