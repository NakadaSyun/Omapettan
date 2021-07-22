#pragma once
#include "DxLib.h"
#include "DrawCube.h"

class c_Collision {
public:
	c_Collision(VECTOR position,float w,float h,float d);
	bool f_Hit(c_Collision Col);
	void CubeDraw();
	c_DrawCube Cube;

private:
	float wide, hight, depth;
	VECTOR pos;
	
};