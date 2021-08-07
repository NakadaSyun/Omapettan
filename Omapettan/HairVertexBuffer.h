#pragma once

#include "DxLib.h"
#include "Collision.h"
#include <iostream>
#include <malloc.h>
#include <math.h>
using namespace std;


namespace {
	// 生成する毛の数
	const int HAIR_NUM = 64;

	// ポリゴンに含まれる頂点の数
	const int POLY = 3;

	// ステージ(腕)の太さの半径
	const float ARM_RADIUS = 755.0f;

	// ステージ(腕)の長さ
	const float ARM_LENGTH = 7000.0f;

	// 腕の座標合わせ
	const float ARM_ADJUST_POS = 1000.0f;
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

	// ステージのX軸の回転(ラジアン)
	float stageXRotation;

	// 髪を画面外へ移動
	void f_MoveHairOffScreen(int num);

private:
	// メモリの割り当て
	void f_allocateMemory();
	// 髪の移動
	void f_moveHair();
	// 髪の座標と角度を設定
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
	float personalRotation[HAIR_NUM];   // 各髪の角度
	float personalPosZ[HAIR_NUM];       // 各髪のZ座標
	LONGLONG Time1;
	MV1_REF_POLYGONLIST RefMesh;
    DATEDATA date;                      // 現在時刻
	VECTOR hairSize;

};
