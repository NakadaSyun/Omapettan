#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <math.h>

namespace {
	const int ACNE_NUM = 4;

	// �X�e�[�W(�r)�̑����̔��a
	const float ARM_RADIUS_ACNE = 760.0f - 10.0f;

	// �X�e�[�W(�r)�̒���
	const float ARM_LENGTH_ACNE = 6000.0f;

	const float ARM_ADJUST_POS_ACNE = 1000.0f;

	const float START_PLAYER_DISTANCE = 4200.0f;

	const float END_PLAYER_DISTANCE = 4800.0f;
}

class c_Acne{
public:
	c_Acne(const int Acne_Model,const int Acne_Graph, const int Bandage_Model);
	c_Acne();
	void f_init();
	void f_output();
	void f_update();

	int status[ACNE_NUM];

	float stageRotation;
	float acnepersonalPosZ[ACNE_NUM];

	c_Collision* c_collision[ACNE_NUM];
private:
	VECTOR position[ACNE_NUM];

	int modelacne;
	int modelBandage;
	int graphacne;
	float acnepersonalRotation[ACNE_NUM];   // �e�ł����̂̊p�x
};
