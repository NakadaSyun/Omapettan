//Player.h

#pragma once
#include "DxLib.h"
#include "Collision.h"
#include "CameraCon.h"
#include "Controller.h"

namespace {
	// �����蔻��܂ł̋���
	float DISTANCE_TO_COLLISION_DETECTION = 100.0f;
}

class c_Player {
public:
	c_Player(const int Model);
	~c_Player();
	void f_init();
	void f_update(bool Isfall);
	void f_draw();
	void f_fall();
	bool f_PlayerDebug(bool DebugFlg,bool speedFlg);//�v���C���[�̃f�o�b�O�p�̊֐�

	float PlayerAngle_H = 0.0f;

	VECTOR f_GetPlayerPosition();		//�v���C���[�̍��W��߂�l�ŕԂ�

	float f_GetPlayerRotationY();       // �v���C���[��Y���̉�]�l��߂�l�ŕԂ�

	bool IsAcneHit;						//�ł����̂Ƃ̏Փ˔���p�ϐ�
	bool IsMove;				//�ړ��̐���

	//���݂���̃v���C���[����̉��Z���W�i�[�ϐ�
	VECTOR Kamisori_Position = VGet(0,20, 0);

	VECTOR StartPos = VGet(0.0f,0.0f,0.0f), EndPos = VGet(0.0f, 0.0f, 0.0f);		//�v���C���[�̓����蔻��̐����̎n�_�A�I�_

	c_Collision* c_colision;

	c_CameraCon* c_cameracon;

	c_GamePad* c_pad;

private:
	int p_Model;
	int model_Arm;
	int model_KAMISORI;
	int model_Acne;
	float Arm_XRotate;
	VECTOR p_Rotation;
	VECTOR p_Position;
	VECTOR p_OldPosition;

	const float p_Speed = 10.0f;		//�v���C���[�̈ړ���
	int p_SpeedMagnification = 2; //�v���C���[�̃_�b�V���̔{��

};