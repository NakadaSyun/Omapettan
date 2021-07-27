#pragma once
#include "DxLib.h"
#include "DrawCube.h"

class c_Collision {
public:
	c_Collision(VECTOR position,float w,float h,float d);
	bool f_Hit();
	void CubeDraw();
	void f_update();
	c_DrawCube Cube;


private:
	float wide, hight, depth;
	VECTOR pos;
	const int polyNum = 12;		//�{�b�N�X�̃|���S����
	
};