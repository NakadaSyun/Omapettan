//Cameracon.h


#pragma once
#include "Dxlib.h"

class c_CameraCon {
public:
	c_CameraCon();
	void f_update();

	void f_setPosition();
	void f_setRotaion();

	float Camangle_H;	//カメラの水平角度
	float Camangle_V;	//カメラの垂直角度

	////Y軸の回転
	float HcosTriRot;		//カメラのH角度のコサイン
	float HsinTriRot;		//カメラのH角度のコサイン

	VECTOR position;


private:
	//VECTOR position;
	VECTOR rotation;

	const VECTOR Cameradistance = VGet(0.0f, 0.0f, -500);	//カメラとプレイヤーの距離

	float HRotate, VRotate, TRotate;			//垂直：水平：ひねり
};
