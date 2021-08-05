//Camera.cpp

#include "CameraCon.h"
#include <math.h>
#include "GameManager.h"

#define PI 3.141592653589793


c_CameraCon::c_CameraCon() {
	VRotate = 0.0f;         //垂直回転
	HRotate = 0.0f;        //水平回転
	TRotate = 0.0f;         //捻り回転

	position = Cameradistance;	//カメラの座標

	rotation = VGet(VRotate, HRotate, TRotate);
}

void c_CameraCon::f_update() {
	f_setPosition();
	//f_setRotaion();

	// カメラの位置と回転値をセット、カメラの位置は原点
	SetCameraPositionAndTarget_UpVecY(position, Playerposition);
}

void c_CameraCon::f_setPosition() {

	position = VAdd(Playerposition, Cameradistance);

	DrawFormatString(0, 40, 0xffffff, "Playerposition.x %f", Playerposition.x);
	DrawFormatString(0, 60, 0xffffff, "Playerposition.y %f", Playerposition.y);
	DrawFormatString(0, 80, 0xffffff, "Playerposition.z %f", Playerposition.z);

}

void c_CameraCon::f_setRotaion() {

}
