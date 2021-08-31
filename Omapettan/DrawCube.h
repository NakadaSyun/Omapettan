#pragma once

#include "DxLib.h"

class c_DrawCube {
public:
	void f_create(float x, float y, float z, float w, float h, float d);		//直方体の作成
	//c_DrawCube();

private:
	VERTEX3D Cubevertex[8];        //四角形の頂点8
	WORD Index[36];		//床のポリゴン12この頂点座標
};