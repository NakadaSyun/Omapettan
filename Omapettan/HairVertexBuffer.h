#pragma once

#include "DxLib.h"
#include "Collision.h"
#include "DrawAcne.h"
#include <iostream>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
using namespace std;


namespace {
	// ��������т̐�
	const int HAIR_NUM = 255;

	// �|���S���Ɋ܂܂�钸�_�̐�
	const int POLY = 3;

	// �X�e�[�W(�r)�̑����̔��a
	const float ARM_RADIUS = 755.0f - 10.0f;

	// �X�e�[�W(�r)�̒���
	const float ARM_LENGTH = 7000.0f;

	// �r�̍��W���킹
	const float ARM_ADJUST_POS = 1000.0f;

	enum hair_status {
		ROOTED_IS,        // ���t���Ă���
		SHAVED,           // ���ꂽ
		OFF_SCREEN,       // ��ʊO
		DO_NOT_ANYTHING,  // �Ȃɂ����Ȃ�
		STATUS_MAX        // �X�e�[�^�X�̐�
	};
}

class c_Hair {
public:
	c_Hair(const int Model, const int Image);
	void f_init();
	void f_output();
	void f_update();
	void f_modelDuplication();
	//�{�b�N�X�R���[�Q���`��
	void CubeDraw();
	//
	c_Collision* c_colision[HAIR_NUM];
	//
	c_DrawCube Cube;
	//�т̓����蔻��p�̍��W
	VECTOR CollisionPosition[HAIR_NUM];
	//�т̓����蔻��p�̃t���O
	bool HitHair[HAIR_NUM];

	// �X�e�[�W��X���̉�](���W�A��)
	float stageXRotation;
	//// �т̈ړ�
	//void f_moveHair(int num);
	//// �т���ʊO�ֈړ�
	//void f_MoveHairOffScreen(int num);
	// �т̏�Ԃ�ω�
	void f_hairCut(int num);
	//// ���ꂽ�т��΂�
	//void f_flyShavedHair(int num);
	//�т̏�Ԃ�����
	bool f_hairStatusSee();
	// �����̉�]�l���擾
	void f_getRotationY(int num, float rot);

	void f_GetAcnePosZ(c_Acne *c_acne);
private:
	// �������̊��蓖��
	void f_allocateMemory();
	// �т̈ړ�
	void f_moveHair(int num);
	// �т̍��W�Ɗp�x��ݒ�
	void f_setPosAndRot();
	// �т���ʊO�ֈړ�
	void f_MoveHairOffScreen(int num);
	//// �т̏�Ԃ�ω�
	//void f_changeHairStatus(int num);
	// ���ꂽ�т��΂�
	void f_flyShavedHair(int num);
	// �������Ȃ�
	void f_doNotAnything(int num);
	// �т̍X�V
	void f_hairUpdate();
	// �v���C���[�Ƃ̏d���̊m�F
	bool CheckingOverlapsWithPlayer(float rot, float posZ);

	// �֐��|�C���^
	void (c_Hair::* f_hairStatusFuncList[STATUS_MAX])(int num) = 
	{ &c_Hair::f_moveHair, &c_Hair::f_flyShavedHair, &c_Hair::f_MoveHairOffScreen, &c_Hair::f_doNotAnything};
	
	bool numflg = false;
	int num=0;
	VERTEX3D* vertex;
	DWORD* index;
	int vertexBufHandle;
	int indexBufHandle;
	int modelHandle; 
	int graphHandle;
	int indexNum = 0;
	int vertexNum = 0;        
	int hairStatus[HAIR_NUM];            // �e�т̏��
	float personalRotation[HAIR_NUM];    // �e�т̊p�x
	float personalPosZ[HAIR_NUM];        // �e�т�Z���W
	float personalRadius[HAIR_NUM];      // �e�т̒��S���W(x = 0, y = 0)����̔��a
	float hairFlyingRotX[HAIR_NUM];      // �т���тȂ����]����l
	float hairFlyingRotZ[HAIR_NUM];      // �т���тȂ����]����l
	float hairFlyingVec[HAIR_NUM];       // �e�т����ł����x�N�g��
	float playerRotY[HAIR_NUM];          // �v���C���[��Y���̌���

	c_Acne *acnepersonalpos;

	LONGLONG Time1;
	MV1_REF_POLYGONLIST RefMesh;
    DATEDATA date;                      // ���ݎ���
	VECTOR hairSize;                    // �����蔻��p�̖т̑傫��
};

