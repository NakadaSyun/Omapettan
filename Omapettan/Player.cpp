#include "Player.h"

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(320.0f, 10.0f, 150.0f);

}

void c_Player::f_init() {
	// ３Ｄモデルの座標を初期化
	p_Position = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(){
	// ３Ｄモデルに新しい座標をセット
	MV1SetPosition(p_Model, p_Position);
}

void c_Player::f_draw() {
	// ３Ｄモデルの描画
	MV1DrawModel(p_Model);
}