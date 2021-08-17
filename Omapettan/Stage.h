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
private:
	VECTOR position;
	int sModel;
	float Arm_XRotate = 0.0f;
};
