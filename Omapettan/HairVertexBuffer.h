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
	// 生成する毛の数
	const int HAIR_NUM = 255;

	// ポリゴンに含まれる頂点の数
	const int POLY = 3;

	// ステージ(腕)の太さの半径
	const float ARM_RADIUS = 755.0f - 10.0f;

	// ステージ(腕)の長さ
	const float ARM_LENGTH = 7000.0f;

	// 腕の座標合わせ
	const float ARM_ADJUST_POS = 1000.0f;

	enum hair_status {
		ROOTED_IS,        // 根付いている
		SHAVED,           // 剃られた
		OFF_SCREEN,       // 画面外
		DO_NOT_ANYTHING,  // なにもしない
		STATUS_MAX        // ステータスの数
	};
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
	//// 毛の移動
	//void f_moveHair(int num);
	//// 毛を画面外へ移動
	//void f_MoveHairOffScreen(int num);
	// 毛の状態を変化
	void f_hairCut(int num);
	//// 剃られた毛を飛ばす
	//void f_flyShavedHair(int num);
	//毛の状態を見る
	bool f_hairStatusSee();
	// ｙ軸の回転値を取得
	void f_getRotationY(int num, float rot);

	void f_GetAcnePosZ(c_Acne *c_acne);
private:
	// メモリの割り当て
	void f_allocateMemory();
	// 毛の移動
	void f_moveHair(int num);
	// 毛の座標と角度を設定
	void f_setPosAndRot();
	// 毛を画面外へ移動
	void f_MoveHairOffScreen(int num);
	//// 毛の状態を変化
	//void f_changeHairStatus(int num);
	// 剃られた毛を飛ばす
	void f_flyShavedHair(int num);
	// 何もしない
	void f_doNotAnything(int num);
	// 毛の更新
	void f_hairUpdate();
	// プレイヤーとの重複の確認
	bool CheckingOverlapsWithPlayer(float rot, float posZ);

	// 関数ポインタ
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
	int hairStatus[HAIR_NUM];            // 各毛の状態
	float personalRotation[HAIR_NUM];    // 各毛の角度
	float personalPosZ[HAIR_NUM];        // 各毛のZ座標
	float personalRadius[HAIR_NUM];      // 各毛の中心座標(x = 0, y = 0)からの半径
	float hairFlyingRotX[HAIR_NUM];      // 毛が飛びながら回転する値
	float hairFlyingRotZ[HAIR_NUM];      // 毛が飛びながら回転する値
	float hairFlyingVec[HAIR_NUM];       // 各毛が飛んでいくベクトル
	float playerRotY[HAIR_NUM];          // プレイヤーのY軸の向き

	c_Acne *acnepersonalpos;

	LONGLONG Time1;
	MV1_REF_POLYGONLIST RefMesh;
    DATEDATA date;                      // 現在時刻
	VECTOR hairSize;                    // 当たり判定用の毛の大きさ
};

