#pragma once
#include "DxLib.h"
#include "Collision.h"

class c_Player {
public:
	c_Player(const int Model);
	void f_init();
	void f_update(bool Isfall);
	void f_draw();
	void f_fall();

	VECTOR f_GetPlayerPosition();		//�v���C���[�̍��W��߂�l�ŕԂ�
	c_Collision* c_colision;
private:
	int p_Model;
	VECTOR p_Rotation;
	VECTOR p_Position;

	const float p_Speed = 10.0f;		//�v���C���[�̈ړ���
	
};