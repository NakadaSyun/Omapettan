#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <malloc.h>
#include <math.h>
using namespace std;

namespace {
	// 生成する毛の数
	const int HAIR_NUM = 16;

	//生成する毛の数の平方根
	const int HAIR_NUM_SQUARE_ROOT = int(sqrtf(float(HAIR_NUM)));

	// ポリゴンに含まれる頂点の数
	const int POLY = 3;
}

class c_Hair {
public:
	c_Hair(const int Model, const int Image);
	void f_init();
	void f_output();
	void f_update();
	void f_modelDuplication();
	//ボックスコラーゲン描画
	void CubeDraw();
	//
	c_Collision* c_colision[HAIR_NUM];
	//
	c_DrawCube Cube;
	//毛の当たり判定用の座標
	VECTOR CollisionPosition[HAIR_NUM];
	//毛の当たり判定用のフラグ
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
