#pragma once

#include "DxLib.h"

class c_DrawCube {
public:
	void f_create(float x, float y, float z, float w, float h, float d);		//�����̂̍쐬
	//c_DrawCube();

private:
	VERTEX3D Cubevertex[8];        //�l�p�`�̒��_8
	WORD Index[36];		//���̃|���S��12���̒��_���W
};