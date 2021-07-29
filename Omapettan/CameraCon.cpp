//Camera.cpp

#include "CameraCon.h"
#include <math.h>
#include "GameManeger.h"

#define PI 3.141592653589793


c_CameraCon::c_CameraCon() {
	VRotate = PI / 4;         //垂直回転
	HRotate = 0.0f;        //水平回転
	TRotate = 0.0f;         //捻り回転

	position = Cameradistance;	//カメラの座標

	rotation = VGet(VRotate, HRotate, TRotate);
}

void c_CameraCon::f_update() {
	f_setPosition();
	//f_setRotaion();

	// カメラの位置と回転値をセット、カメラの位置は原点
   // SetCameraPositionAndAngle(position, rotation.x, rotation.y, rotation.z );
	SetCameraPositionAndTarget_UpVecY(position, Playerposition);
}

void c_CameraCon::f_setPosition() {

	int Nowx, Nowy;		//マウスの座標変数
	GetMousePoint(&Nowx, &Nowy);	//マウスの座標取得
	//画面中心が原点に来るように調整
	Nowx -= 640 / 2;
	Nowy -= 480 / 2;
	//カメラのY軸の上限設定 90度まで
	if (Nowy > 90) Nowy = 90;
	//カメラのY軸の下限設定 20度まで
	if (Nowy < 20) Nowy = 20;

	Camangle_H = Nowx * PI / 90;	//カメラの水平角度
	Camangle_V = Nowy * PI / 90;	//カメラの垂直角度


	DrawFormatString(0, 0, 0xffffff, "Nowy %d", Nowy);
	DrawFormatString(0, 20, 0xffffff, "Nowx %d", Nowx);

	position.x = Cameradistance.x * cos(Camangle_H) + Cameradistance.z * sin(Camangle_H);
	position.z = -Cameradistance.x * sin(Camangle_H) + Cameradistance.z * cos(Camangle_H);
	position.y = Cameradistance.x * sin(Camangle_V) + Cameradistance.z * cos(Camangle_V);
	position.x += Playerposition.x;
	position.z += Playerposition.z;
	position.y -= Playerposition.y - 500.0f;

	DrawFormatString(0, 40, 0xffffff, "position.x %f", position.x);
	DrawFormatString(0, 60, 0xffffff, "Playerposition.y %f", Playerposition.y);
	DrawFormatString(0, 80, 0xffffff, "position.y %f", position.y);

}

void c_CameraCon::f_setRotaion() {
	int Nowx, Nowy;
	GetMousePoint(&Nowx, &Nowy);

	static int Oldx = Nowx, Oldy = Nowy;

	if (Oldx < Nowx) {
		HRotate += (Nowx % 10) * 0.005f;
	}
	if (Oldx > Nowx) {
		HRotate -= (Nowx % 10) * 0.005f;
	}
	if (Oldy < Nowy) {
		VRotate += (Nowy % 10) * 0.005f;
	}
	if (Oldy > Nowy) {
		VRotate -= (Nowy % 10) * 0.005f;
	}
	rotation = VGet(VRotate, HRotate, TRotate);

	//atan2(Nowx * PI/180, Nowy);

	//カメラの座標　=　(プレイヤーの座標+プレイヤーとの固定距離)
	//position = VGet(Nowx * PI / 180 + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);

	SetMousePoint(640 / 2, 480 / 2);
	Oldx = 640 / 2;
	Oldy = 480 / 2;
}
