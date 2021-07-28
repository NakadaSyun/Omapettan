#pragma once
#include "DxLib.h"
#include "DrawCube.h"

class c_Collision {
public:
	c_Collision();
	c_Collision(VECTOR position,float w,float h,float d);
	bool f_Hit();
	void CubeDraw();
	void f_update(VECTOR position);
	c_DrawCube Cube;

	float wide, hight, depth;
	VECTOR pos;
	const int polyNum = 12;		//ボックスのポリゴン数
	
};