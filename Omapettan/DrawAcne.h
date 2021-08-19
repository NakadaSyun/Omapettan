#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <math.h>

class c_Acne{
public:
	c_Acne(const int Acne_Model,const int Acne_Graph);
	void f_init();
	void f_output();
	void f_update();

	float stageRotation;

	c_Collision* c_collision;
private:
	int modelacne;
	int graphacne;
};
