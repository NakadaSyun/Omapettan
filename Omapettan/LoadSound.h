#pragma once
#include "DxLib.h"

struct Sound {
public:

	int KAMISORI_Hold;		//�䓁���\�����Ƃ��̉�
	int HIGESORI_SE;		//�E���������̉�
	int StageClear;			 //�X�e�[�W�N���A����SE
	int Player_footStep;	//�v���C���[�̑���
	int Menumove;			//���j���[���ړ���SE
	int Menu_Select;		//���j���[���ł̌��莞SE
	int Menu_Open;			//���j���[�J��SE
	int Menu_Cansel;		//���j���[���ł̃L�����Z��
	int Customer_Damage;	//�t�L�f���̔j��
	//sei_ge_garasu_ware03
	int GameOver;


};

int f_LoadSound(void);	//�֐��̒�`

