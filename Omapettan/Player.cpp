//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"
#include <stdlib.h>

#define PI 3.141592653589793

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 760.0f, 4500.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);

	c_colision = new c_Collision(VGet(p_Position.x + Kamisori_Position.x,
		p_Position.y + Kamisori_Position.y,
		p_Position.z + Kamisori_Position.z),
		100.0f, 20.0f, 100.0f);

	c_cameracon = new c_CameraCon;

	model_Arm = MV1LoadModel("models/arm2.mv1");
	model_KAMISORI = MV1LoadModel("models/KKAMISORI.mv1");
}

void c_Player::f_init() {
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);


	MV1SetPosition(model_KAMISORI, VGet(p_Position.x, p_Position.y, p_Position.z));

}

void c_Player::f_update(bool Isfall) {

	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(p_Model, p_Position);
	// �R�c���f���ɐV������]�l���Z�b�g
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameracon���Ă�Œl���X�V

	StartPos = p_Position;
	EndPos = VGet(p_Position.x, p_Position.y + 250.0f, p_Position.z);

	//�r�̃��f���ɍ��W�A��]�l�A�R���W�����̐ݒ�
	MV1SetPosition(model_Arm, VGet(0.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(model_Arm, VGet(0.0f, PI / 2, 0.0f));
	MV1SetupCollInfo(model_Arm, -1, 8, 8, 8);		//���f���S�̂̃t���[���ɃR���W����������

	//�䓁�̃��f���ɍ��W�A��]�l�A�R���W�����̐ݒ�
	MV1SetRotationXYZ(model_KAMISORI, VGet(p_Rotation.x, p_Rotation.y, p_Rotation.z));
	MV1SetupCollInfo(model_KAMISORI, -1, 8, 8, 8);		//���f���S�̂̃t���[���ɃR���W����������

	DrawLine3D(StartPos, EndPos, GetColor(255, 0, 0));		//�L�����̓����蔻��̐���

	//�r�Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY HitPoly = MV1CollCheck_Line(model_Arm, -1, StartPos, EndPos);
	//�䓁�Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY KAMISORI_HitPoly = MV1CollCheck_Line(model_KAMISORI, -1, StartPos, EndPos);

	//�r���f���Ƃ̃q�b�g�|���S��*************************************************
	VECTOR Pos0 = HitPoly.Position[0],
		Pos1 = HitPoly.Position[1],
		Pos2 = HitPoly.Position[2];
	int LineColor = GetColor(255, 0, 0);

	DrawLine3D(Pos0, Pos1, LineColor);
	DrawLine3D(Pos1, Pos2, LineColor);
	DrawLine3D(Pos2, Pos0, LineColor);
	//*************************************************************************


	//���݂��胂�f���̃q�b�g�|���S��*******************************************
	VECTOR KAMI_Pos0 = KAMISORI_HitPoly.Position[0],
		KAMI_Pos1 = KAMISORI_HitPoly.Position[1],
		KAMI_Pos2 = KAMISORI_HitPoly.Position[2];
	int KAMI_LineColor = GetColor(0, 255, 0);

	DrawLine3D(KAMI_Pos0, KAMI_Pos1, KAMI_LineColor);
	DrawLine3D(KAMI_Pos1, KAMI_Pos2, KAMI_LineColor);
	DrawLine3D(KAMI_Pos2, KAMI_Pos0, KAMI_LineColor);
	//*************************************************************************

	//���[���h���m�F
	DrawLine3D(p_Position, VGet(p_Position.x + 200, p_Position.y, p_Position.z), GetColor(255, 0, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y + 200, p_Position.z), GetColor(0, 255, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y, p_Position.z + 200), GetColor(0, 0, 255));

	//p_Rotation = HitPoly.Normal;		//�@���̃L�����̌����ɑ��

	if (HitPoly.HitFlag == 1) {
		p_Rotation = VGet(HitPoly.Normal.x, p_Rotation.y, HitPoly.Normal.z); 		//�@���̃L�����̌����ɑ��
	}

	//�r�̃��f���Ƃ̃q�b�g�����|���S���̎O�_���W��\��
	DrawFormatString(0, 200, GetColor(255, 255, 255), "Pos0.x:%f", HitPoly.Position[0].x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Pos0.y:%f", HitPoly.Position[0].y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Pos0.z:%f", HitPoly.Position[0].z);


	//�䓁�̃��f���Ƃ̃q�b�g�����|���S���̎O�_���W��\��
	DrawFormatString(0, 260, GetColor(255, 255, 255), "KAMISORI_HitPoly.x:%f", KAMISORI_HitPoly.Position[0].x);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "KAMISORI_HitPoly.y:%f", KAMISORI_HitPoly.Position[0].y);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "KAMISORI_HitPoly.z:%f", KAMISORI_HitPoly.Position[0].z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));		//�|���S���̖@���`��

	/**************************************
	*�v���C���[�̈ړ�����
	**************************************/

	float MoveX = 0, MoveZ = 0;//�v���C���[�̈ړ���
	Arm_XRotate = 0.0f;


	//static float Rota_Dif = 0.0;		//Rotate_Difference�F�F���݂̉�]�l�ƌ������������́@���v���p�x�̍����i�[�ϐ�
	static float Rota_Vec = 0;		//Rotate_Vectol�F�F�L���������͂��ꂽ�L�[�ɑ΂��Č����ׂ�����
	static float rad = PI / 180;		//���W�A���ł�1��  rad * 180 =�@PI
	static int Rota_Dif = 0;
	static int int_angle = 0;
	static int NowRota = 0;

	bool MoveKeyFlag = CheckHitKey(KEY_INPUT_W) ||
		CheckHitKey(KEY_INPUT_A) ||
		CheckHitKey(KEY_INPUT_S) ||
		CheckHitKey(KEY_INPUT_D);


	if (CheckHitKey(KEY_INPUT_W) == 1) {
		MoveZ = p_Speed;
		Kamisori_Position.z = 80;
		Kamisori_Position.x = 0;
		Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		MoveX = -p_Speed;
		Kamisori_Position.x = -80;
		Kamisori_Position.z = 0;
		Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		MoveZ = -p_Speed;
		Kamisori_Position.z = -80;
		Kamisori_Position.x = 0;
		Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		MoveX = p_Speed;
		Kamisori_Position.x = 80;
		Kamisori_Position.z = 0;
		Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	}

	if (Rota_Vec < 0) {
		Rota_Vec = PI + (PI + Rota_Vec);
	}

	DrawFormatString(0, 100, 0x00ffff, "Rota_Vec %f", Rota_Vec);
	int_angle = Rota_Vec / rad;

	if (p_Rotation.y < 0) {
		p_Rotation.y = PI + (PI + p_Rotation.y);
	}

	NowRota = abs(p_Rotation.y) / rad;		//���݂̌����Ă��郉�W�A���p�x

	if (int_angle == 0 && NowRota > 180) {
		int_angle = 360;
	}
	if (int_angle > 180 && NowRota == 0) {
		NowRota = 360;
	}
	Rota_Dif = int_angle - NowRota;			//���������p�x�@�[�@���݂̊p�x �̍���
	Rota_Dif = abs(Rota_Dif);

	if (MoveKeyFlag == TRUE) {

		if (int_angle > NowRota) {
			if (Rota_Dif <= 180) {
				if (Rota_Dif != 0) {	//�����ׂ������ƌ��݂̉�]�l���ׂ�
					p_Rotation.y += rad * 1;		//�p�x��1�������Z����
				}
			}
			if (Rota_Dif > 180) {
				if (Rota_Dif != 0) {	//�����ׂ������ƌ��݂̉�]�l���ׂ�
					p_Rotation.y -= rad * 1;		//�p�x��1�������Z����
				}
			}
		}
		if (int_angle < NowRota) {
			if (Rota_Dif <= 180) {
				if (Rota_Dif != 0) {	//�����ׂ������ƌ��݂̉�]�l���ׂ�
					p_Rotation.y -= rad * 1;		//�p�x��1�������Z����
				}
			}
			if (Rota_Dif > 180) {
				if (Rota_Dif != 0) {	//�����ׂ������ƌ��݂̉�]�l���ׂ�
					p_Rotation.y += rad * 1;		//�p�x��1�������Z����
				}
			}
		}
	}

	if (NowRota == 360 && Rota_Dif == 0 && int_angle == 360) {
		p_Rotation.y = 0.0f;
	}

	MV1SetPosition(model_KAMISORI, VGet(
		sinf(p_Rotation.y) * -100 + p_Position.x,
		p_Position.y,
		cosf(p_Rotation.y) * -100 + p_Position.z
	));

	p_Position = VAdd(p_Position, VGet(0, 0, MoveZ));	//�v���C���[�̍��W�����Z����


	if (p_Position.z > 8000) {						//�L�������r�X�e�[�W���ł̈ړ�����//�r�̎�����ɂ͍s���Ȃ�
		p_Position.z = 8000;
	}
	if (p_Position.z < 1000) {						//�L�������r�X�e�[�W���ł̈ړ�����//�I��O��艺�ɂ͍s���Ȃ�
		p_Position.z = 1000;
	}

	DrawFormatString(0, 120, 0x00ffff, "p_Rotation.y %f", p_Rotation.y);
	DrawFormatString(0, 140, 0x00ffff, "Rota_Dif %d", Rota_Dif);
	DrawFormatString(0, 160, 0x00ffff, "NowRota %d", NowRota);
	DrawFormatString(0, 180, 0x00ffff, "int_angle %d", int_angle);


	if (HitPoly.HitFlag == 0)f_fall();		//�d��
	c_colision->f_update(p_Position);
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {
	c_colision->CubeDraw();
	// �R�c���f���̕`��
	MV1DrawModel(p_Model);
	//MV1SetScale(model_KAMISORI,VGet(-20.0f,-20.0f,-20.0f));

	MV1DrawModel(model_KAMISORI);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

