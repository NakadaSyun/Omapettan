//Player.h

#pragma once
#include "DxLib.h"
#include "Collision.h"
#include "CameraCon.h"
#include "Controller.h"

namespace {
	// 当たり判定までの距離
	float DISTANCE_TO_COLLISION_DETECTION = 60.0f;
	VECTOR KAMISORI_SIZE = VGet(120.0f, 40.0f, 110.0f);
}

class c_Player {
public:
	c_Player(const int Model);
	~c_Player();
	void f_init();
	void f_update(bool Isfall);
	void f_draw();
	void f_fall();
	bool f_PlayerDebug(bool DebugFlg,bool speedFlg);//プレイヤーのデバッグ用の関数
	void AnimSet();
	float PlayerAngle_H = 0.0f;

	VECTOR f_GetPlayerPosition();		//プレイヤーの座標を戻り値で返す

	float f_GetPlayerRotationY();       // プレイヤーのY軸の回転値を戻り値で返す

	bool IsAcneHit;						//できものとの衝突判定用変数
	bool IsMove;				        //移動の制限



	c_Collision* c_colision;

	c_CameraCon* c_cameracon;

	c_GamePad* c_pad;

private:
	int p_Model;
	int model_Arm;
	int model_KAMISORI;
	int model_Acne;
	float Arm_XRotate;
	VECTOR p_Rotation;
	VECTOR p_Position;
	VECTOR p_OldPosition;

	int image_PTexture;
	float TotalAnimTime;

	const float p_Speed = 10.0f;		//プレイヤーの移動量
	int p_SpeedMagnification = 2; //プレイヤーのダッシュの倍率

};