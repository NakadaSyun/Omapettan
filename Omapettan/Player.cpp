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
	p_OldPosition = p_Position;

	IsAcneHit = false; 
	IsMove = true;

    c_colision = new c_Collision(VGet(sinf(p_Rotation.y) * -DISTANCE_TO_COLLISION_DETECTION + p_Position.x,
		                              p_Position.y,
		                              cosf(p_Rotation.y) * -DISTANCE_TO_COLLISION_DETECTION + p_Position.z),
		                              KAMISORI_SIZE.x, KAMISORI_SIZE.y, KAMISORI_SIZE.z);



	c_cameracon = new c_CameraCon;
	c_pad = new c_GamePad();

	model_Arm = MV1LoadModel("models/arm4.mv1");
	model_KAMISORI = MV1LoadModel("models/KKAMISORI.mv1");
	model_Acne = MV1LoadModel("models/dekimono.mv1");

	SoundFlg = 0;		//�ŏ��̒䓁�̉���炷�t���O
	MV1AttachAnim(p_Model, 1);
	TotalAnimTime = MV1GetAttachAnimTotalTime(p_Model, 0);
	image_PTexture = LoadGraph("images/Ch18_1001_Diffuse.png");
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
	if (!IsMove) return;
	c_pad->f_update();

	if (SoundFlg == 0) {
		PlaySoundMem(g_Snd.KAMISORI_Hold, DX_PLAYTYPE_BACK);
		SoundFlg++;
	}

	AnimSet();


	// �R�c���f���ɐV�������W���Z�b�g
	MV1SetPosition(p_Model, p_Position);
	// �R�c���f���ɐV������]�l���Z�b�g
	MV1SetRotationXYZ(p_Model, p_Rotation);

	c_cameracon->f_update();		//c_cameracon���Ă�Œl���X�V


	//�䓁�̃��f���ɍ��W�A��]�l�A�R���W�����̐ݒ�
	MV1SetRotationXYZ(model_KAMISORI, VGet(p_Rotation.x, p_Rotation.y, p_Rotation.z));


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

	bool MoveKeyFlag = false;	//�ړ��L�[����ł�������Ă��邩�̃t���O
	if (c_pad->LeftStick != 0) MoveKeyFlag = true;		//�X�e�B�b�N���ǂ����ɌX���Ă�����true


	/*****	�R���g���[���[�̓���	*****/
	if (c_pad->LeftStick == UP||
		c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == LEFTUP ) {
		if (c_pad->IsButton2 == TRUE) MoveZ = p_Speed * p_SpeedMagnification;
		else {
			MoveZ = p_Speed;
		}
	}

	if (c_pad->LeftStick == LEFTUP ||
		c_pad->LeftStick == LEFT ||
		c_pad->LeftStick == LEFTDOWN) {
		if (c_pad->IsButton2 == TRUE) MoveX = -p_Speed * p_SpeedMagnification;
		else {
			MoveX = -p_Speed;
		}
	}
	if (c_pad->LeftStick == DOWN ||
		c_pad->LeftStick == RIGHTDOWN ||
		c_pad->LeftStick == LEFTDOWN) {
		if (c_pad->IsButton2 == TRUE) MoveZ = -p_Speed * p_SpeedMagnification;
		else {
			MoveZ = -p_Speed;
		}
	}
	if (c_pad->LeftStick == RIGHTUP ||
		c_pad->LeftStick == RIGHT ||
		c_pad->LeftStick == RIGHTDOWN) {
		if (c_pad->IsButton2 == TRUE) MoveX = p_Speed * p_SpeedMagnification;
		else {
			MoveX = p_Speed;
		}
	}

	Rota_Vec = atan2(-MoveX, -MoveZ);			//�v���C���[�̌�������
	if (Rota_Vec < 0) {								//�v���C���[�̌����ׂ�������-3.14�Ȃǔ����v���ɉ��Ƃ���-�̒l�ɂȂ�����
		Rota_Vec = PI + (PI + Rota_Vec);			//2PI�ň�����Z�����l�ɂ���
	}

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

	c_colision->f_update(VGet(sinf(p_Rotation.y) * -DISTANCE_TO_COLLISION_DETECTION + p_Position.x,
		                      p_Position.y,
		                      cosf(p_Rotation.y) * -DISTANCE_TO_COLLISION_DETECTION + p_Position.z));

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

	static int Skin1 = MV1GetMaterialDifMapTexture(p_Model, 0);
	//�}�e���A���Ŏg�p����Ă���e�N�X�`���̔ԍ����擾
	static int Skin2 = MV1GetMaterialDifMapTexture(p_Model, 2);

	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����
	MV1SetTextureGraphHandle(p_Model, Skin1, image_PTexture, FALSE);
	// �e�N�X�`���Ŏg�p����O���t�B�b�N�n���h����ύX����
	MV1SetTextureGraphHandle(p_Model, Skin2, image_PTexture, FALSE);

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

bool c_Player::f_PlayerDebug(bool DebugFlg,bool speedFlg) {
	/*if (DebugFlg)
	{
		p_SpeedMagnification = 5;
		return true;
	}
	else {
		p_SpeedMagnification = 2;
		return false;
	}*/
	if (!speedFlg)
	{
		p_SpeedMagnification = 5;
		return true;
	}
	else {
		p_SpeedMagnification = 2;
		return false;
	}
}

void c_Player::AnimSet() {

	static float NowAnimTime = 0.0f;
	if (c_pad->LeftStick != NONE && IsMove) {
		if (c_pad->IsButton2 == TRUE) NowAnimTime += 1.0f * p_SpeedMagnification;
		else  NowAnimTime += 1.0f;
	}
	if (NowAnimTime > TotalAnimTime) {
		NowAnimTime = 0.0f;
	}
	printf("%d\n", p_SpeedMagnification);
	MV1SetAttachAnimTime(p_Model, 0, NowAnimTime);
}