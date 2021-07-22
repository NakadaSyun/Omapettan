#pragma once
#include "DxLib.h"
#include "Collision.h"

class c_Player {
public:
	c_Player(const int Model);
	void f_init();
	void f_update();
	void f_draw();

	VECTOR f_GetPlayerPosition();		//プレイヤーの座標を戻り値で返す

private:
	int p_Model;
	VECTOR p_Rotation;
	VECTOR p_Position;

	const float p_Speed = 10.0f;		//プレイヤーの移動量

};