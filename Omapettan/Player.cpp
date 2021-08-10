//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"

#define PI 3.141592653589793

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 760.0f, 4500.0f);
	p_Rotation = VGet(0.0f, PI, 0.0f);

	c_colision = new c_Collision(p_Position, 100.0f, 200.0f, 100.0f);

	c_cameracon = new c_CameraCon;

	model_Arm = MV1LoadModel("models/arm2.mv1");
	model_KAMISORI = MV1LoadModel("models/KKAMISORI.mv1");
}

void c_Player::f_init() {
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);


	MV1SetPosition(model_KAMISORI, VGet(p_Position.x,p_Position.y, p_Position.z));

}

void c_Player::f_update(bool Isfall) {

	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(p_Model, p_Position);
	// ３Ｄモデルに新しい回転値をセット
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameraconを呼んで値を更新

	StartPos = p_Position;
	EndPos = VGet(p_Position.x , p_Position.y + 250.0f,p_Position.z);

	//腕のモデルに座標、回転値、コリジョンの設定
	MV1SetPosition(model_Arm, VGet(0.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(model_Arm,VGet(0.0f,PI/2,0.0f));
	MV1SetupCollInfo(model_Arm, -1, 8, 8, 8);		//モデル全体のフレームにコリジョンを準備

	//剃刀のモデルに座標、回転値、コリジョンの設定
	MV1SetRotationXYZ(model_KAMISORI, VGet(p_Rotation.x, p_Rotation.y, p_Rotation.z));
	MV1SetupCollInfo(model_KAMISORI, -1, 8, 8, 8);		//モデル全体のフレームにコリジョンを準備

	DrawLine3D(StartPos, EndPos, GetColor(255, 0, 0));		//キャラの当たり判定の線分

	//腕との当たり判定
	MV1_COLL_RESULT_POLY HitPoly = MV1CollCheck_Line(model_Arm,-1, StartPos, EndPos);
	//剃刀との当たり判定
	MV1_COLL_RESULT_POLY KAMISORI_HitPoly = MV1CollCheck_Line(model_KAMISORI, -1, StartPos, EndPos);

	//腕モデルとのヒットポリゴン*************************************************
	VECTOR Pos0= HitPoly.Position[0],
		   Pos1 = HitPoly.Position[1],
		   Pos2 = HitPoly.Position[2];
	int LineColor = GetColor(255,0,0);

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

	//ワールド軸確認
	DrawLine3D(p_Position, VGet(p_Position.x + 200, p_Position.y, p_Position.z), GetColor(255,0,0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y + 200, p_Position.z), GetColor(0, 255, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y, p_Position.z + 200), GetColor(0, 0, 255));

	//p_Rotation = HitPoly.Normal;		//法線のキャラの向きに代入

	if (HitPoly.HitFlag == 1) {
		p_Rotation = VGet(HitPoly.Normal.x, p_Rotation.y, HitPoly.Normal.z); 		//法線のキャラの向きに代入
	}

	//腕のモデルとのヒットしたポリゴンの三点座標を表示
	DrawFormatString(0, 200, GetColor(255, 255, 255), "Pos0.x:%f", HitPoly.Position[0].x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Pos0.y:%f", HitPoly.Position[0].y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Pos0.z:%f", HitPoly.Position[0].z);


	//剃刀のモデルとのヒットしたポリゴンの三点座標を表示
	DrawFormatString(0, 260, GetColor(255, 255, 255), "KAMISORI_HitPoly.x:%f", KAMISORI_HitPoly.Position[0].x);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "KAMISORI_HitPoly.y:%f", KAMISORI_HitPoly.Position[0].y);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "KAMISORI_HitPoly.z:%f", KAMISORI_HitPoly.Position[0].z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));		//ポリゴンの法線描画

	/**************************************
	*プレイヤーの移動処理
	**************************************/

	float MoveX = 0,MoveZ = 0;//プレイヤーの移動量
	Arm_XRotate = 0.0f;

	//キャラの今までの移動方法

	//if (CheckHitKey(KEY_INPUT_W) == 1) {
	//    MoveZ = p_Speed;
	//	Kamisori_Position.z = 80;
	//	Kamisori_Position.x = 0;
	//    p_Rotation.y = PI;			//最終定期なキャラの向く角度
	//}
	//if (CheckHitKey(KEY_INPUT_A) == 1) {
	//    p_Rotation.y = PI/2;
	//	Kamisori_Position.x = -80;
	//	Kamisori_Position.z = 0;
	//	MoveX = -p_Speed;
	//}
	//if (CheckHitKey(KEY_INPUT_S) == 1) {
	//    MoveZ = -p_Speed;
	//	Kamisori_Position.z = -80;
	//	Kamisori_Position.x = 0;
	//    p_Rotation.y = 0;
	//}
	//if (CheckHitKey(KEY_INPUT_D) == 1) {
	//    p_Rotation.y = -PI / 2;
	//	Kamisori_Position.x = 80;
	//	Kamisori_Position.z = 0;
	//	MoveX = p_Speed;
	//}

	static float Rota_Dif = 0.0;		//Rotate_Difference：：現在の回転値と向きたい方向の角度の差分格納変数
	static float Rota_Vec = 0.0;		//Rotate_Vectol：：キャラが入力されたキーに対して向くべき方向
	static float rad = PI/180;				//ラジアンでの1°  rad * 180 =　PI
	static int Dif_rad = 0;				//整数型での角度差分


	if (CheckHitKey(KEY_INPUT_W) == 1) {
		MoveZ = p_Speed;
		Kamisori_Position.z = 80;
		Kamisori_Position.x = 0;
		//プレイヤーの向く方向
		Rota_Vec = atan2(-MoveX, -MoveZ);
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		MoveX = -p_Speed;
		Kamisori_Position.x = -80;
		Kamisori_Position.z = 0;
		//プレイヤーの向く方向
		Rota_Vec = atan2(-MoveX, -MoveZ);
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		MoveZ = -p_Speed;
		Kamisori_Position.z = -80;
		Kamisori_Position.x = 0;
		//プレイヤーの向く方向
		Rota_Vec = atan2(-MoveX, -MoveZ);
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		MoveX = p_Speed;
		Kamisori_Position.x = 80;
		Kamisori_Position.z = 0;
		//プレイヤーの向く方向
		Rota_Vec = atan2(-MoveX, -MoveZ);
	}

	//p_Rotation.y = Rota_Vec;

	Rota_Dif = Rota_Vec - p_Rotation.y;

	if (Rota_Dif > p_Rotation.y) {
		p_Rotation.y += rad;
	}
	if (Rota_Dif < p_Rotation.y) {
		p_Rotation.y -= rad;
	}

	/*
	* 眠気が来たので明日の俺にまかせる
	* 取得できたもの
	*向くべき方向　　Rota_Vec
	*現在の向いている方向 p_Rotation.y
	*上二つの値の差分
	*だからその差分の値分現在の向いている方向から向くべき方向に向けて値を調整すればOK
	*/


	//剃刀の位置 = プレイヤーの位置　+　向いた方向に
	MV1SetPosition(model_KAMISORI, VGet(
		p_Position.x + Kamisori_Position.x, 
		p_Position.y + Kamisori_Position.y,
		p_Position.z + Kamisori_Position.z
	));
	

	p_Position = VAdd(p_Position,VGet(0,0,MoveZ));
	if (p_Position.z > 8000) {
		p_Position.z = 8000;
	}
	if (p_Position.z < 1000) {
		p_Position.z = 1000;
	}



	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		p_Position.y += 10;
	}

	DrawFormatString(0, 100, 0x00ffff, "Rota_Vec %f", Rota_Vec);
	DrawFormatString(0, 120, 0x00ffff, "Rota_Dif %f", Rota_Dif);
	DrawFormatString(0, 140, 0x00ffff, "p_Rotation.y %f", p_Rotation.y);

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
	//MV1SetScale(model_KAMISORI,VGet(-20.0f,-20.0f,-20.0f));

	MV1DrawModel(model_KAMISORI);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

