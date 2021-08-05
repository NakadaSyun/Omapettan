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
}

void c_Player::f_init() {
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(bool Isfall) {

	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(p_Model, p_Position);
	// ３Ｄモデルに新しい回転値をセット
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameraconを呼んで値を更新

	StartPos = p_Position;
	EndPos = VGet(p_Position.x , p_Position.y + 250.0f,p_Position.z);

	static int model_Arm = MV1LoadModel("models/arm2.mv1");

	MV1SetPosition(model_Arm, VGet(0.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(model_Arm,VGet(0.0f,PI/2,0.0f));
	MV1SetupCollInfo(model_Arm, -1, 8, 8, 8);		//モデル全体のフレームにコリジョンを準備

	DrawLine3D(StartPos, EndPos, GetColor(255, 0, 0));		//キャラの当たり判定の線分

	MV1_COLL_RESULT_POLY HitPoly = MV1CollCheck_Line(model_Arm,-1, StartPos, EndPos);

	VECTOR Pos0= HitPoly.Position[0],
		   Pos1 = HitPoly.Position[1],
		   Pos2 = HitPoly.Position[2];
	int LineColor = GetColor(255,0,0);

	DrawLine3D(Pos0, Pos1, LineColor);
	DrawLine3D(Pos1, Pos2, LineColor);
	DrawLine3D(Pos2, Pos0, LineColor);

	//ワールド軸確認
	DrawLine3D(p_Position, VGet(p_Position.x + 200, p_Position.y, p_Position.z), GetColor(255,0,0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y + 200, p_Position.z), GetColor(0, 255, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y, p_Position.z + 200), GetColor(0, 0, 255));

	//p_Rotation = HitPoly.Normal;		//法線のキャラの向きに代入

	if (HitPoly.HitFlag == 1) {
		p_Rotation = VGet(HitPoly.Normal.x, p_Rotation.y, HitPoly.Normal.z); 		//法線のキャラの向きに代入
	}

	DrawFormatString(0, 200, GetColor(255, 255, 255), "Pos0.x:%f個", HitPoly.Position[0].x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Pos0.y:%f個", HitPoly.Position[0].y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Pos0.z:%f個", HitPoly.Position[0].z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));		//ポリゴンの法線描画

	float MoveX = 0,MoveZ = 0;//プレイヤーの移動量
	static float Arm_XRotate = 0.0f;

	if (CheckHitKey(KEY_INPUT_W) == 1) {
	    MoveZ = p_Speed;
	    p_Rotation.y = PI;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
	    p_Rotation.y = PI/2;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
	    MoveZ = -p_Speed;
	    p_Rotation.y = 0;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
	    p_Rotation.y = -PI / 2;
	}


	//if (MoveZ != 0 && MoveX != 0 ) {
	//    p_Rotation.y = atan2(-MoveX,-MoveZ);
	//}

	p_Position = VAdd(p_Position,VGet(MoveX,0,MoveZ));
	if (p_Position.z > 8000) {
		p_Position.z = 8000;
	}
	if (p_Position.z < 1000) {
		p_Position.z = 1000;
	}



	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		p_Position.y += 10;
	}

	DrawFormatString(0, 100, 0xffffff, "p_Position.x %f", p_Position.x);
	DrawFormatString(0, 120, 0xffffff, "p_Position.z %f", p_Position.z);
	DrawFormatString(0, 140, 0xffffff, "p_Rotation.y %f", p_Rotation.y);

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
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

