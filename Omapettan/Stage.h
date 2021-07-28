#pragma once
#include "DxLib.h"
#include "Collision.h"

class c_Stage {
public:
	c_Stage(const int Model);

	void f_init();
	void f_update();
	void f_output();

	c_Collision* c_colision;

private:
	VECTOR position;
	int sModel;
};
