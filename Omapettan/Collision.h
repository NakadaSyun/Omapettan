#pragma once
#include "DxLib.h"
#include "DrawCube.h"

#include <math.h>

class c_Collision {
public:
	c_Collision(VECTOR position,float w,float h,float d);
	bool f_Hit();
	void f_update(VECTOR position);
	void f_CubeDraw();
	void f_PolyDraw(float rot);
	c_DrawCube Cube;

	float wide, hight, depth;
	VECTOR pos;
	const int polyNum = 12;		//ボックスのポリゴン数
	
};