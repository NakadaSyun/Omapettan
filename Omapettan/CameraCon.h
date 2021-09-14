//Cameracon.h


#pragma once
#include "Dxlib.h"
#include "MainUI.h"

class c_CameraCon {
public:
	c_CameraCon();
	void f_update();

	void f_setPosition();
	void f_setRotaion();
	void f_rotate(float* x, float* y, const float ang, const float mx, const float my);

	float Camangle_H = 0.0f;	//カメラの水平角度
	float Camangle_V = 0.0f;	//カメラの垂直角度


	c_MainUI* c_mainui;

	VECTOR position;


private:
	//VECTOR position;
	VECTOR rotation;

	const VECTOR Cameradistance = VGet(0.0f, 600.0f, -800.0f);	//カメラとプレイヤーの距離

	float HRotate, VRotate, TRotate;			//垂直：水平：ひねり
};
