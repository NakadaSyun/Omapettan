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
	// ¶¬‚·‚é–Ñ‚Ì”
	const int HAIR_NUM = 64;

	// ƒ|ƒŠƒSƒ“‚ÉŠÜ‚Ü‚ê‚é’¸“_‚Ì”
	const int POLY = 3;
}