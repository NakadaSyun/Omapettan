//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManeger.h"

#define PI 3.141592653589793



c_Player::c_Player(const int Model) {
	p_Model = Model;
	// ‚R‚cƒ‚ƒfƒ‹‚ÌÀ•W‚ð‰Šú‰»
	p_Position = VGet(0.0f, 500.0f, 150.0f);
	p_Rotation = VGet(0.0f, PI, 0.0f);

	c_colision = new c_Collision(p_Position, 100.0f, 200.0f, 100.0f);

	c_cameracon = new c_CameraCon;
}

void c_Player::f_init() {
	// ‚R‚cƒ‚ƒfƒ‹‚ÌÀ•W‚ð‰Šú‰»
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(bool Isfall) {



	// ‚R‚cƒ‚ƒfƒ‹‚ÉV‚µ‚¢À•W‚ðƒZƒbƒg
	MV1SetPosition(p_Model, p_Position);
	// ‚R‚cƒ‚ƒfƒ‹‚ÉV‚µ‚¢‰ñ“]’l‚ðƒZƒbƒg
	MV1SetRotationXYZ(p_Model, p_Rotation);

	float MoveX = 0, MoveZ = 0;//ƒvƒŒƒCƒ„[‚ÌˆÚ“®—Ê

	c_cameracon->f_update();

	//MoveX = atan2(p_Position.x, c_cameracon->position.x);
	//MoveZ = atan2(p_Position.z, c_cameracon->position.z);

	//float MoveZ = (c_cameracon->position.z * c_cameracon->HcosTriRot) + (c_cameracon->position.x * c_cameracon->HsinTriRot) * (-1);	//¶‰E‚ÌˆÚ“®—Ê‚ð”½“]
	//float MoveX = (c_cameracon->position.x * c_cameracon->HcosTriRot) + (c_cameracon->position.z * c_cameracon->HsinTriRot);

	////X‚ÆZ‚ÌˆÚ“®—Ê‚ðYŽ²‚Ì‰ñ“]—Ê‚É‡‚í‚¹‚Äsin cos‚ð‚©‚¯‚é
	 //float MoveZ = (CamZ * HcosTriRot) + (CamX * HsinTriRot) * (-1);	//¶‰E‚ÌˆÚ“®—Ê‚ð”½“]
	 //float MoveX = (CamX * HcosTriRot) + (CamZ * HsinTriRot);

	if (CheckHitKey(KEY_INPUT_W) == 1) {
		//MoveZ = p_Speed;
		p_Rotation.y = c_cameracon->Camangle_H + PI;

		//MoveX = -500 * cos(c_cameracon->Camangle_H) + -500 * sin(c_cameracon->Camangle_H);
		//MoveZ = 500 * sin(c_cameracon->Camangle_H) + -500 * cos(c_cameracon->Camangle_H);
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		MoveX = -p_Speed;
		//p_Rotation.y = PI/2;
		p_Rotation.y = c_cameracon->Camangle_H + PI / 2;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		MoveZ = -p_Speed;
		//p_Rotation.y = 0;
		p_Rotation.y = c_cameracon->Camangle_H;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		MoveX = p_Speed;
		//p_Rotation.y = -PI / 2;
		p_Rotation.y = c_cameracon->Camangle_H + -PI / 2;
	}

	//if (MoveZ != 0 && MoveX != 0 ) {
	//	p_Rotation.y = atan2(-MoveX,-MoveZ);
	//}

	if (CheckHitKey(KEY_INPUT_Q) == 1) {
		p_Position.y += 10;
	}

	p_Position = VAdd(p_Position, VGet(MoveX, 0, MoveZ));

	DrawFormatString(0, 100, 0xffffff, "p_Position.x %f", p_Position.x);
	DrawFormatString(0, 120, 0xffffff, "p_Position.z %f", p_Position.z);
	DrawFormatString(0, 140, 0xffffff, "p_Position.y %f", p_Position.y);

	//float MoveZ = (CamZ * HcosTriRot) + (CamX * HsinTriRot) * (-1);	//¶‰E‚ÌˆÚ“®—Ê‚ð”½“]
	//float MoveX = (CamX * HcosTriRot) + (CamZ * HsinTriRot);

	//ƒJƒƒ‰‚ÌÀ•W@ = (ƒvƒŒƒCƒ„[‚ÌÀ•W + ƒvƒŒƒCƒ„[‚Æ‚ÌŒÅ’è‹——£)
	//position = VGet(Playerposition.x + Cameradistance.x, Playerposition.y + Cameradistance.y, Playerposition.z + Cameradistance.z);
	//p_Position = VGet(Nowx * PI / 180 + Cameradistance.x, Playerposition.y + Cameradistance.y, Nowx * PI / 180 + Cameradistance.z);

	if (Isfall)f_fall();		//d—Í
	c_colision->f_update(p_Position);
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {
	c_colision->CubeDraw();
	// ‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(p_Model);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

