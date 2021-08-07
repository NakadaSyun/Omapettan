#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <iostream>
#include <malloc.h>
#include <math.h>
using namespace std;


namespace {
	// ��������т̐�
	const int HAIR_NUM = 64;

	// �|���S���Ɋ܂܂�钸�_�̐�
	const int POLY = 3;

	// �X�e�[�W(�r)�̑����̔��a
	const float ARM_RADIUS = 755.0f;

	// �X�e�[�W(�r)�̒���
	const float ARM_LENGTH = 7000.0f;

	// �r�̍��W���킹
	const float ARM_ADJUST_POS = 1000.0f;
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

	// ������ʊO�ֈړ�
	void f_MoveHairOffScreen(int num);

private:
	// �������̊��蓖��
	void f_allocateMemory();
	// ���̈ړ�
	void f_moveHair();
	// ���̍��W�Ɗp�x��ݒ�
	void f_setPosAndRot();
	VERTEX3D* vertex;
	DWORD* index;
	int vertexBufHandle;
	int indexBufHandle;
	int modelHandle; 
	int graphHandle;
	int indexNum = 0;
	int vertexNum = 0;
	int i;
	float personalRotation[HAIR_NUM];   // �e���̊p�x
	float personalPosZ[HAIR_NUM];       // �e����Z���W
	LONGLONG Time1;
	MV1_REF_POLYGONLIST RefMesh;
    DATEDATA date;                      // ���ݎ���
	VECTOR hairSize;

};
