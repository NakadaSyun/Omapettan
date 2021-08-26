//Player.cpp

#include "Player.h"
#include "Math.h"
#include "GameManager.h"
#include <stdlib.h>

#define PI 3.141592653589793

extern Sound g_Snd;
static int SoundFlg = 0;

c_Player::c_Player(const int Model) {
	p_Model = Model;
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 760.0f, 4500.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);

	IsAcneHit = false; 

    c_colision = new c_Collision(VGet(sinf(p_Rotation.y) * -50 + p_Position.x,
		                              p_Position.y,
		                              cosf(p_Rotation.y) * -80 + p_Position.z),
		                              120.0f, 40.0f, 60.0f);

	/*  VGet(p_Position.x + Kamisori_Position.x,
        p_Position.y + Kamisori_Position.y,
        p_Position.z + Kamisori_Position.z)*/

	c_cameracon = new c_CameraCon;
	c_pad = new c_GamePad();

	model_Arm = MV1LoadModel("models/arm3.mv1");
	model_KAMISORI = MV1LoadModel("models/KKAMISORI.mv1");
	model_Acne = MV1LoadModel("models/dekimono.mv1");

	SoundFlg = 0;		//�ŏ��̒䓁�̉���炷�t���O

}

c_Player::~c_Player() {
	delete c_cameracon;
	delete c_colision;
	delete c_pad;
}

void c_Player::f_init() {
	// �R�c���f���̍��W��������
	p_Position = VGet(0.0f, 0.0f, 0.0f);
	p_Rotation = VGet(0.0f, 0.0f, 0.0f);


	MV1SetPosition(model_KAMISORI, VGet(p_Position.x, p_Position.y, p_Position.z));


}

void c_Player::f_update(bool Isfall) {
	c_pad->f_update();

	if (SoundFlg == 0) {
		PlaySoundMem(g_Snd.KAMISORI_Hold, DX_PLAYTYPE_BACK);
		SoundFlg++;
	}


	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(p_Model, p_Position);
	// �R�c���f���ɐV������]�l���Z�b�g
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameracon���Ă�Œl���X�V

	//�v���C���[�̓����蔻��̐����̊J�n�ʒu�ƁA�I���ʒu
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
	//�����o���Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY AcneHitPoly = MV1CollCheck_Line(model_Acne, -1, StartPos, EndPos);

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

	//�����o�����f���̃q�b�g�|���S��*******************************************
	VECTOR Acne_Pos0 = AcneHitPoly.Position[0],
		Acne_Pos1 = AcneHitPoly.Position[1],
		Acne_Pos2 = AcneHitPoly.Position[2];
	int Acne_LineColor = GetColor(0, 255, 0);

	DrawLine3D(Acne_Pos0, Acne_Pos1, Acne_LineColor);
	DrawLine3D(Acne_Pos1, Acne_Pos2, Acne_LineColor);
	DrawLine3D(Acne_Pos2, Acne_Pos0, Acne_LineColor);
	//*************************************************************************

	//���[���h���m�F
	DrawLine3D(p_Position, VGet(p_Position.x + 200, p_Position.y, p_Position.z), GetColor(255, 0, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y + 200, p_Position.z), GetColor(0, 255, 0));
	DrawLine3D(p_Position, VGet(p_Position.x, p_Position.y, p_Position.z + 200), GetColor(0, 0, 255));

	//�r�̃��f���Ƃ̃q�b�g�����|���S���̎O�_���W��\��
	DrawFormatString(0, 200, GetColor(255, 255, 255), "Pos0.x:%f", HitPoly.Position[0].x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Pos0.y:%f", HitPoly.Position[0].y);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Pos0.z:%f", HitPoly.Position[0].z);

	//�����o�����f���Ƃ̃q�b�g�����|���S���̎O�_���W��\��
	DrawFormatString(0, 260, GetColor(255, 255, 255), "AcneHitPoly.x:%f", AcneHitPoly.Position[0].x);
	DrawFormatString(0, 280, GetColor(255, 255, 255), "AcneHitPoly.y:%f", AcneHitPoly.Position[0].y);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "AcneHitPoly.z:%f", AcneHitPoly.Position[0].z);


	DrawLine3D(HitPoly.Position[0], HitPoly.Normal, GetColor(0, 0, 255));		//�|���S���̖@���`��

	/**************************************
	*�v���C���[�̈ړ�����
	**************************************/

	float MoveX = 0, MoveZ = 0;//�v���C���[�̈ړ���
	Arm_XRotate = 0.0f;


	static float Rota_Vec = 0;		//Rotate_Vectol�F�F�L���������͂��ꂽ�L�[�ɑ΂��Č����ׂ�����
	static int int_angle = 0;			//Rotate_Vectol�����W�A���p�x�ɒ�����int�^����
	static float rad = PI / 180;		//���W�A���ł�1��  rad * 180 =�@PI
	static int Rota_Dif = 0;			//Rotate_Difference�F�F���݂̉�]�l�ƌ������������́@���v���p�x�̍����i�[�ϐ�
	static int NowRota = 0;				//Now_Rotate�F�F���݂̌����Ă��郉�W�A���p�x

	//bool MoveKeyFlag = CheckHitKey(KEY_INPUT_W) ||		//�ړ��L�[����ł�������Ă��邩�̃t���O
	//	CheckHitKey(KEY_INPUT_A) ||
	//	CheckHitKey(KEY_INPUT_S) ||
	//	CheckHitKey(KEY_INPUT_D);

	bool MoveKeyFlag = false;	//�ړ��L�[����ł�������Ă��邩�̃t���O
	if (c_pad->LeftStick != 0) MoveKeyFlag = true;		//�X�e�B�b�N���ǂ����ɌX���Ă�����true


	//if (CheckHitKey(KEY_INPUT_W) == 1) {
	//	MoveZ = p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	//}
	//if (CheckHitKey(KEY_INPUT_A) == 1) {
	//	MoveX = -p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	//}
	//if (CheckHitKey(KEY_INPUT_S) == 1) {
	//	MoveZ = -p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	//}
	//if (CheckHitKey(KEY_INPUT_D) == 1) {
	//	MoveX = p_Speed;
	//	Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	//}

	/*****	�R���g���[���[�̓���	*****/
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

	Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	if (Rota_Vec < 0) {								//�v���C���[�̌����ׂ�������-3.14�Ȃǔ����v���ɉ��Ƃ���-�̒l�ɂȂ�����
		Rota_Vec = PI + (PI + Rota_Vec);			//2PI�ň�����Z�����l�ɂ���
	}

	DrawFormatString(0, 100, 0x00ffff, "Rota_Vec %f", Rota_Vec);

	int_angle = Rota_Vec / rad;						//�����ׂ����������W�A���p�x�ɕϊ�

	if (p_Rotation.y < 0) {							//�v���C���[�̌����Ă��������-3.14�Ȃǔ����v���ɉ��Ƃ���-�̒l�ɂȂ�����
		p_Rotation.y = PI + (PI + p_Rotation.y);	//2PI�ň�����Z�����l�ɂ���
	}

	NowRota = abs(p_Rotation.y) / rad;				//���݂̌����Ă��郉�W�A���p�x

	if (int_angle == 0 && NowRota > 180) {
		int_angle = 360;
	}
	if (int_angle > 180 && NowRota == 0) {
		NowRota = 360;
	}	
	Rota_Dif = int_angle - NowRota;			//���������p�x�@�[�@���݂̊p�x �̍���
	Rota_Dif = abs(Rota_Dif);				//��L�̒l�̍����̐�Βl

	Rota_Dif = Rota_Dif % 360;				//������360���ȏ�s���Ȃ��悤�ɂ���

	if (MoveKeyFlag == TRUE) {				//�ړ��L�[��������Ă��鎞
		if (CheckSoundMem(g_Snd.Player_footStep) == 0) {
			PlaySoundMem(g_Snd.Player_footStep, DX_PLAYTYPE_BACK);
		}
		
		//���݂̊p�x����������������Ɍ�������
		if (int_angle > NowRota) {			//���݂̊p�x�ƁA�����ׂ��p�x���ׂ�
			if (Rota_Dif <= 180) {			//�������ׂ�
				if (Rota_Dif != 0) {		//������0�ɂȂ�܂�
					if (Rota_Dif > 10) {	//������10���ȏ゠��Ƃ�
						p_Rotation.y += rad * 10;		//�p�x��10�������Z����
					}
					else {
						p_Rotation.y = int_angle * rad;		//�p�x��1�������Z����
					}
				}
			}
			if (Rota_Dif > 180) {			//���݂̊p�x�ƁA�����ׂ��p�x���ׂ�
				if (Rota_Dif != 0) {		//������0�ɂȂ�܂�
					if (Rota_Dif > 10) {	//������10���ȏ゠��Ƃ�
						p_Rotation.y -= rad * 10;		//�p�x��10�������Z����
					}
					else {
						p_Rotation.y = int_angle * rad;		//�p�x��1�������Z����
					}
				}
			}
		}
		if (int_angle < NowRota) {			//���݂̊p�x�ƁA�����ׂ��p�x���ׂ�
			if (Rota_Dif <= 180) {			//�������ׂ�
				if (Rota_Dif != 0) {		//������0�ɂȂ�܂�
					if (Rota_Dif > 10) {	//������10���ȏ゠��Ƃ�
						p_Rotation.y -= rad * 10;		//�p�x��10�������Z����
					}
					else {
						p_Rotation.y = int_angle * rad;		//�p�x��1�������Z����
					}
				}
			}
			if (Rota_Dif > 180) {			//�������ׂ�
				if (Rota_Dif != 0) {		//������0�ɂȂ�܂�
					if (Rota_Dif > 10) {	//������10���ȏ゠��Ƃ�
						p_Rotation.y += rad * 10;		//�p�x��10�������Z����
					}
					else {
						p_Rotation.y = int_angle * rad;		//�p�x��1�������Z����
					}
				}
			}
		}
	}

	//���݂̊p�x�������ʒu�Ɠ����Ȃ������A�l�����߂��Ȃ��悤�ɒl�������l�ɂ���
	if (NowRota == 360 && Rota_Dif == 0 && int_angle == 360) {		
		p_Rotation.y = 0.0f;
	}

	//���݂���̈ʒu�A�p�x���v���C���[�Ƃ̈ʒu�Ɗp�x�ɏ���������
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
	c_colision->f_update(VGet(sinf(p_Rotation.y) * -50 + p_Position.x,
		                      p_Position.y,
		                      cosf(p_Rotation.y) * -80 + p_Position.z));

	if (IsAcneHit) {			//�����o���ƏՓ˂��Ă������t���[���O�̍��W�ɖ߂�
		p_Position = p_OldPosition;
	}
	else {
		p_OldPosition = p_Position;
	}
	IsAcneHit = false;
}

void c_Player::f_fall() {
	p_Position.y -= 5.0f;
}

void c_Player::f_draw() {
	c_colision->CubeDraw();
	// �R�c���f���̕`��
	MV1DrawModel(p_Model);

	MV1DrawModel(model_KAMISORI);
}

VECTOR c_Player::f_GetPlayerPosition() {
	return p_Position;
}

float c_Player::f_GetPlayerRotationY() {
	return p_Rotation.y;
}