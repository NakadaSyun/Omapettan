#pragma once

#include "DxLib.h"
#include <malloc.h>
using namespace std;

class c_Hair {
public:
	c_Hair(const int Model, const int Image);
	void f_init();
	void f_output();
	void f_update();
	void f_modelDuplication();
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

namespace {
	// ��������т̐�
	const int HAIR_NUM = 64;

	// �|���S���Ɋ܂܂�钸�_�̐�
	const int POLY = 3;
}