#pragma once
#include "DxLib.h"

class c_Player {
public:
	c_Player(const int Model);
	void f_init();
	void f_update();
	void f_draw();

	VECTOR f_GetPlayerPosition();		//�v���C���[�̍��W��߂�l�ŕԂ�

private:
	int p_Model;
	VECTOR p_Rotation;
	VECTOR p_Position;

	const float p_Speed = 10.0f;		//�v���C���[�̈ړ���

};