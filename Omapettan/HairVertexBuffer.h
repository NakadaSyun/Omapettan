#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <malloc.h>
#include <math.h>
using namespace std;

namespace {
	// ��������т̐�
	const int HAIR_NUM = 16;

	//��������т̐��̕�����
	const int HAIR_NUM_SQUARE_ROOT = int(sqrtf(float(HAIR_NUM)));

	// �|���S���Ɋ܂܂�钸�_�̐�
	const int POLY = 3;
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

private:
	void f_allocateMemory();
	VERTEX3D* vertex;
	DWORD* index;
	int vertexBufHandle;
	int indexBufHandle;
	int modelHandle; 
	int graphHandle;
	int indexNum = 0;
	int vertexNum = 0;
	int i;
	LONGLONG Time1;
	MV1_REF_POLYGONLIST RefMesh;

};
