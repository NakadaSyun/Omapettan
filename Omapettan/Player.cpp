//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"

#define PI 3.141592653589793

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 500.0f, 150.0f);
	p_Rotation = VGet(0.0f, PI, 0.0f);

	c_colision = new c_Collision(p_Position, 100.0f, 200.0f, 100.0f);

	c_cameracon = new c_CameraCon;
}

void c_Player::f_init() {
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);
}

void c_Player::f_update(bool Isfall) {

	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(p_Model, p_Position);
	// �R�c���f���ɐV������]�l���Z�b�g
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameracon���Ă�Œl���X�V

	p_Rotation.y = c_cameracon->Camangle_H + PI;

	if (CheckHitKey(KEY_INPUT_W) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H + PI;		//�L�����̉�]Y�����J�����Ɍ������� + 90�x�����ɂ���

		//�L�����̍��WX�����J�����������Ă�������ɐi�܂���
		p_Position.x += sin(c_cameracon->Camangle_H) * 10.0f;
		p_Position.z += cos(c_cameracon->Camangle_H) * 10.0f;

	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H + PI / 2;		//�L�����̉�]Y�����J�����Ɍ������� + 45�x�����ɂ���

		//�L�����̍��WX�����J�������������� + 45�x�����ɐi�܂���
		p_Position.x -= sin(c_cameracon->Camangle_H + PI / 2) * 10.0f;
		p_Position.z -= cos(c_cameracon->Camangle_H + PI / 2) * 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_W) == 1 && CheckHitKey(KEY_INPUT_A) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H + PI - PI / 4;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H + -PI / 2;		//�L�����̉�]Y�����J�����Ɍ������� - 45�x�����ɂ���

		//�L�����̍��WX�����J�������������� - 45�x�����ɐi�܂���
		p_Position.x += sin(c_cameracon->Camangle_H + PI / 2) * 10.0f;
		p_Position.z += cos(c_cameracon->Camangle_H + PI / 2) * 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_W) == 1 && CheckHitKey(KEY_INPUT_D) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H + PI + PI / 4;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H;		//�L�����̉�]Y�����J�����Ɍ����������ɂ���

		//�L�����̍��WX�����J�����������������ɐi�܂���
		p_Position.x -= sin(c_cameracon->Camangle_H) * 10.0f;
		p_Position.z -= cos(c_cameracon->Camangle_H) * 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_A) == 1 && CheckHitKey(KEY_INPUT_S) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H + PI / 4;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1 && CheckHitKey(KEY_INPUT_S) == 1) {
		p_Rotation.y = c_cameracon->Camangle_H - PI / 4;
	}

	StartPos = VGet(p_Position.x, p_Position.y + 500.0f, p_Position.z);
	EndPos = VGet(p_Position.x , p_Position.y - 500.0f,p_Position.z);

	static int model_Arm;
	//static int flg = 0;
	//if (flg++ == 0 ) {
	//}
	model_Arm = MV1LoadModel("models/arm.mv1");
	MV1SetupCollInfo(model_Arm, -1, 8, 8, 8);		//���f���S�̂̃t���[���ɃR���W����������

	DrawLine3D(StartPos, EndPos, GetColor(255, 0, 0));

	MV1_COLL_RESULT_POLY HitPoly = MV1CollCheck_Line(model_Arm,-1, StartPos, EndPos);

	p_Rotation = HitPoly.Normal;

	DrawFormatString(0, 200, GetColor(255, 255, 255), "Normal.x:%f��", HitPoly.Normal.x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Normal.y:%f��", HitPoly.Normal.y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Normal.z:%f��", HitPoly.Normal.z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));





	if (CheckHitKey(KEY_INPUT_Q) == 1) {
		p_Position.y += 10;
	}

	DrawFormatString(0, 100, 0xffffff, "p_Position.x %f", p_Position.x);
	DrawFormatString(0, 120, 0xffffff, "p_Position.z %f", p_Position.z);
	DrawFormatString(0, 140, 0xffffff, "p_Rotation.y %f", p_Rotation.y);

	if (Isfall)f_fall();		//�d��
	c_colision->f_update(p_Position);
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {
	c_colision->CubeDraw();
	// �R�c���f���̕`��
	MV1DrawModel(p_Model);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

