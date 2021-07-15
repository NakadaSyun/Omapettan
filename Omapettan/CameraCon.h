#pragma once
#include "Dxlib.h"

class c_CameraCon {
public:
	c_CameraCon();
	void f_update();

	void f_setPosition();
	void f_setRotaion();


private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR Cameradistance = VGet(0.0f,350.0f,-250);	//カメラとプレイヤーの距離

	float HRotate, VRotate,TRotate;			//垂直：水平：ひねり
};
