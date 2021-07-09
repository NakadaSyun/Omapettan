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

	float HRotate, VRotate,TRotate;			//êÇíºÅFêÖïΩÅFÇ–ÇÀÇË
};
