//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"
#include <stdlib.h>

#define PI 3.141592653589793

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 760.0f, 4500.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);

	c_colision = new c_Collision(VGet(sinf(p_Rotation.y) * -100 + p_Position.x,
		                              p_Position.y,
		                              cosf(p_Rotation.y) * -100 + p_Position.z),
		                         100.0f, 40.0f, 100.0f);

	/*  VGet(p_Position.x + Kamisori_Position.x,
        p_Position.y + Kamisori_Position.y,
        p_Position.z + Kamisori_Position.z)*/

	c_cameracon = new c_CameraCon;
	c_pad = new c_GamePad();

	model_Arm = MV1LoadModel("models/arm2.mv1");
	model_KAMISORI = MV1LoadModel("models/KKAMISORI.mv1");
	model_Acne = MV1LoadModel("models/dekimono.mv1");
}

c_Player::~c_Player() {
	delete c_cameracon;
	delete c_colision;
	delete c_pad;
}

void c_Player::f_init() {
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);


	MV1SetPosition(model_KAMISORI, VGet(p_Position.x, p_Position.y, p_Position.z));

}

void c_Player::f_update(bool Isfall) {
	c_pad->f_update();

	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(p_Model, p_Position);
	// ３Ｄモデルに新しい回転値をセット
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameraconを呼んで値を更新

	//プレイヤーの当たり判定の線分の開始位置と、終了位置
	StartPos = p_Position;
	EndPos = VGet(p_Position.x, p_Position.y + 250.0f, p_Position.z);

	//腕のモデルに座標、回転値、コリジョンの設定
	MV1SetPosition(model_Arm, VGet(0.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(model_Arm, VGet(0.0f, PI / 2, 0.0f));
	MV1SetupCollInfo(model_Arm, -1, 8, 8, 8);		//モデル全体のフレームにコリジョンを準備

	//剃刀のモデルに座標、回転値、コリジョンの設定
	MV1SetRotationXYZ(model_KAMISORI, VGet(p_Rotation.x, p_Rotation.y, p_Rotation.z));
	MV1SetupCollInfo(model_KAMISORI, -1, 8, 8, 8);		//モデル全体のフレームにコリジョンを準備

	DrawLine3D(StartPos, EndPos, GetColor(255, 0, 0));		//キャラの当たり判定の線分

	//腕との当たり判定
	MV1_COLL_RESULT_POLY HitPoly = MV1CollCheck_Line(model_Arm, -1, StartPos, EndPos);
	//剃刀との当たり判定
	MV1_COLL_RESULT_POLY KAMISORI_HitPoly = MV1CollCheck_Line(model_KAMISORI, -1, StartPos, EndPos);
	//吹き出物との当たり判定
	MV1_COLL_RESULT_POLY AcneHitPoly = MV1CollCheck_Line(model_Acne, -1, StartPos, EndPos);

	//腕モデルとのヒットポリゴン*************************************************
	VECTOR Pos0 = HitPoly.Position[0],
		Pos1 = HitPoly.Position[1],
		Pos2 = HitPoly.Position[2];
	int LineColor = GetColor(255, 0, 0);

	DrawLine3D(Pos0, Pos1, LineColor);
	DrawLine3D(Pos1, Pos2, LineColor);
	DrawLine3D(Pos2, Pos0, LineColor);
	//*************************************************************************


	//かみそりモデルのヒットポリゴン*******************************************
	VECTOR KAMI_Pos0 = KAMISORI_HitPoly.Position[0],
		KAMI_Pos1 = KAMISORI_HitPoly.Position[1],
		KAMI_Pos2 = KAMISORI_HitPoly.Position[2];
	int KAMI_LineColor = GetColor(0, 255, 0);

	DrawLine3D(KAMI_Pos0, KAMI_Pos1, KAMI_LineColor);
	DrawLine3D(KAMI_Pos1, KAMI_Pos2, KAMI_LineColor);
	DrawLine3D(KAMI_Pos2, KAMI_Pos0, KAMI_LineColor);
	//*************************************************************************

	//吹き出物モデルのヒットポリゴン*******************************************
	VECTOR Acne_Pos0 = AcneHitPoly.Position[0],
		Acne_Pos1 = AcneHitPoly.Position[1],
		Acne_Pos2 = AcneHitPoly.Position[2];
	int Acne_LineColor = GetColor(0, 255, 0);

	DrawLine3D(Acne_Pos0, Acne_Pos1, Acne_LineColor);
	DrawLine3D(Acne_Pos1, Acne_Pos2, Acne_LineColor);
	DrawLine3D(Acne_Pos2, Acne_Pos0, Acne_LineColor);
	//*************************************************************************

	//ワールド軸確認
	DrawLine3D(p_Position, VGet(p_Position.x + 200, p_Position.y, p_Position.z), GetColor(255, 0, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y + 200, p_Position.z), GetColor(0, 255, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y, p_Position.z + 200), GetColor(0, 0, 255));

	//腕のモデルとのヒットしたポリゴンの三点座標を表示
	DrawFormatString(0, 200, GetColor(255, 255, 255), "Pos0.x:%f", HitPoly.Position[0].x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Pos0.y:%f", HitPoly.Position[0].y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Pos0.z:%f", HitPoly.Position[0].z);

	//吹き出物モデルとのヒットしたポリゴンの三点座標を表示
	DrawFormatString(0, 260, GetColor(255, 255, 255), "AcneHitPoly.x:%f", AcneHitPoly.Position[0].x);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "AcneHitPoly.y:%f", AcneHitPoly.Position[0].y);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "AcneHitPoly.z:%f", AcneHitPoly.Position[0].z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));		//ポリゴンの法線描画

	/**************************************
	*プレイヤーの移動処理
	**************************************/

	float MoveX = 0, MoveZ = 0;//プレイヤーの移動量
	Arm_XRotate = 0.0f;


	static float Rota_Vec = 0;		//Rotate_Vectol：：キャラが入力されたキーに対して向くべき方向
	static int int_angle = 0;			//Rotate_Vectolをラジアン角度に直したint型整数
	static float rad = PI / 180;		//ラジアンでの1°  rad * 180 =　PI
	static int Rota_Dif = 0;			//Rotate_Difference：：現在の回転値と向きたい方向の　時計廻り角度の差分格納変数
	static int NowRota = 0;				//Now_Rotate：：現在の向いているラジアン角度

	//bool MoveKeyFlag = CheckHitKey(KEY_INPUT_W) ||		//移動キーが一つでも押されているかのフラグ
	//	CheckHitKey(KEY_INPUT_A) ||
	//	CheckHitKey(KEY_INPUT_S) ||
	//	CheckHitKey(KEY_INPUT_D);

	bool MoveKeyFlag = false;	//移動キーが一つでも押されているかのフラグ
	if (c_pad->LeftStick != 0) MoveKeyFlag = true;		//スティックがどこかに傾いていたらtrue


	//if (CheckHitKey(KEY_INPUT_W) == 1) {
	//	MoveZ = p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//プレイヤーの向く方向
	//}
	//if (CheckHitKey(KEY_INPUT_A) == 1) {
	//	MoveX = -p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//プレイヤーの向く方向
	//}
	//if (CheckHitKey(KEY_INPUT_S) == 1) {
	//	MoveZ = -p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//プレイヤーの向く方向
	//}
	//if (CheckHitKey(KEY_INPUT_D) == 1) {
	//	MoveX = p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//プレイヤーの向く方向
	//}

	/*****	コントローラーの入力	*****/
	if (c_pad->LeftStick == UP||
		c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == LEFTUP ) {
		MoveZ = p_Speed;
	}
	if (c_pad->LeftStick == LEFTUP ||
		c_pad->LeftStick == LEFT ||
		c_pad->LeftStick == LEFTDOWN) {
		MoveX = -p_Speed;
	}
	if (c_pad->LeftStick == DOWN ||
		c_pad->LeftStick == RIGHTDOWN ||
		c_pad->LeftStick == LEFTDOWN) {
		MoveZ = -p_Speed;
	}
	if (c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == RIGHT ||
		c_pad->LeftStick == RIGHTDOWN) {
		MoveX = p_Speed;
	}

	Rota_Vec = atan2(-MoveX, -MoveZ);			//プレイヤーの向く方向
	if (Rota_Vec < 0) {								//プレイヤーの向くべき方向が-3.14など反時計廻りに回るときに-の値になった時
		Rota_Vec = PI + (PI + Rota_Vec);			//2PIで一周換算した値にする
	}

	DrawFormatString(0, 100, 0x00ffff, "Rota_Vec %f", Rota_Vec);

	int_angle = Rota_Vec / rad;						//向くべき方向をラジアン角度に変換

	if (p_Rotation.y < 0) {							//プレイヤーの向いている方向が-3.14など反時計廻りに回るときに-の値になった時
		p_Rotation.y = PI + (PI + p_Rotation.y);	//2PIで一周換算した値にする
	}

	NowRota = abs(p_Rotation.y) / rad;				//現在の向いているラジアン角度

	if (int_angle == 0 && NowRota > 180) {
		int_angle = 360;
	}
	if (int_angle > 180 && NowRota == 0) {
		NowRota = 360;
	}	
	Rota_Dif = int_angle - NowRota;			//向きたい角度　ー　現在の角度 の差分
	Rota_Dif = abs(Rota_Dif);				//上記の値の差分の絶対値

	Rota_Dif = Rota_Dif % 360;				//差分が360°以上行かないようにする

	if (MoveKeyFlag == TRUE) {				//移動キーが押されている時

		//現在の角度から向きたい方向に向く処理
		if (int_angle > NowRota) {			//現在の角度と、向きべき角度を比べる
			if (Rota_Dif <= 180) {			//差分を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y += rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
			if (Rota_Dif > 180) {			//現在の角度と、向くべき角度を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y -= rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
		}
		if (int_angle < NowRota) {			//現在の角度と、向きべき角度を比べる
			if (Rota_Dif <= 180) {			//差分を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y -= rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
			if (Rota_Dif > 180) {			//差分を比べる
				if (Rota_Dif != 0) {		//差分が0になるまで
					if (Rota_Dif > 10) {	//差分が10°以上あるとき
						p_Rotation.y += rad * 10;		//角度を10°ずつ加算する
					}
					else {
						p_Rotation.y = int_angle * rad;		//角度を1°ずつ加算する
					}
				}
			}
		}
	}

	//現在の角度が初期位置と同じなった時、値が超過しないように値を初期値にする
	if (NowRota == 360 && Rota_Dif == 0 && int_angle == 360) {		
		p_Rotation.y = 0.0f;
	}

	//かみそりの位置、角度をプレイヤーとの位置と角度に準拠させる
	MV1SetPosition(model_KAMISORI, VGet(
		sinf(p_Rotation.y) * -100 + p_Position.x,
		p_Position.y,
		cosf(p_Rotation.y) * -100 + p_Position.z
	));

	p_Position = VAdd(p_Position, VGet(0, 0, MoveZ));	//プレイヤーの座標加減算処理


	if (p_Position.z > 8000) {						//キャラが腕ステージ内での移動制限//腕の手首より上には行けない
		p_Position.z = 8000;
	}
	if (p_Position.z < 1000) {						//キャラが腕ステージ内での移動制限//肘手前より下には行けない
		p_Position.z = 1000;
	}

	DrawFormatString(0, 120, 0x00ffff, "p_Rotation.y %f", p_Rotation.y);
	DrawFormatString(0, 140, 0x00ffff, "Rota_Dif %d", Rota_Dif);
	DrawFormatString(0, 160, 0x00ffff, "NowRota %d", NowRota);
	DrawFormatString(0, 180, 0x00ffff, "int_angle %d", int_angle);


	if (HitPoly.HitFlag == 0)f_fall();		//重力
	c_colision->f_update(p_Position);
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {
	c_colision->CubeDraw();
	// ３Ｄモデルの描画
	MV1DrawModel(p_Model);

	MV1DrawModel(model_KAMISORI);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

