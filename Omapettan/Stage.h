#pragma once
#include "DxLib.h"
#include "Collision.h"
#include "Controller.h"

class c_Stage {
public:
	c_Stage(const int Model);
	~c_Stage();

	void f_init();
	void f_update();
	void f_output();

	c_Collision* c_colision;
	float f_GetXRotation();
	c_GamePad* c_pad;

	bool IsAcneHit;
private:
	VECTOR position;
	int sModel;

	int image_armTexture;
	float Arm_XRotate = 0.0f;

	float Arm_OldXRotate = 0.0f;
	int  Arm_RotateSpeed = 2; //ステージ回転速度（プレイヤーのダッシュ倍率と同じにする）
};
