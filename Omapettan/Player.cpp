#include "Player.h"
#include "Math.h"

#define PI 3.141592653589793

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 10.0f, 150.0f);
	p_Rotation = VGet(0.0f,PI,0.0f);

}

void c_Player::f_init() {
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(){
	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(p_Model, p_Position);
	// ３Ｄモデルに新しい回転値をセット
	MV1SetRotationXYZ(p_Model, p_Rotation);

	float MoveX = 0,MoveZ = 0;//プレイヤーの移動量

	if (CheckHitKey(KEY_INPUT_W) == 1) {
		MoveZ = p_Speed;
		p_Rotation.y = PI;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		MoveX = -p_Speed;
		p_Rotation.y = PI/2;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		MoveZ = -p_Speed;
		p_Rotation.y = 0;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		MoveX = p_Speed;
		p_Rotation.y = -PI / 2;
	}

	if (MoveZ != 0 && MoveX != 0 ) {
		p_Rotation.y = atan2(-MoveX,-MoveZ);
	}


	p_Position = VAdd(p_Position,VGet(MoveX,0,MoveZ));


}

void c_Player::f_draw() {
	// ３Ｄモデルの描画
	MV1DrawModel(p_Model);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}