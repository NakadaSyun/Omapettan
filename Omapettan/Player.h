//Player.h

#pragma once
#include "DxLib.h"
#include "Collision.h"
#include "CameraCon.h"


class c_Player {
public:
	c_Player(const int Model);
	void f_init();
	void f_update(bool Isfall);
	void f_draw();
	void f_fall();

	float PlayerAngle_H = 0.0f;

	VECTOR f_GetPlayerPosition();		//�v���C���[�̍��W��߂�l�ŕԂ�

	//���݂���̃v���C���[����̉��Z���W�i�[�ϐ�
	VECTOR Kamisori_Position = VGet(0,20, 0);

	VECTOR StartPos = VGet(0.0f,0.0f,0.0f), EndPos = VGet(0.0f, 0.0f, 0.0f);		//�v���C���[�̓����蔻��̐����̎n�_�A�I�_

	c_Collision* c_colision;

	c_CameraCon* c_cameracon;

private:
	int p_Model;
	int model_Arm;
	int model_KAMISORI;
	float Arm_XRotate;
	VECTOR p_Rotation;
	VECTOR p_Position;

	const float p_Speed = 10.0f;		//�v���C���[�̈ړ���

};