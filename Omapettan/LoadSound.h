#pragma once
#include "DxLib.h"

struct Sound {
public:
	void SetSound();           //���ʐݒ�
	void SetSound_Menumove(int volume);  //���ʐݒ�iMenumove�j

	int KAMISORI_Hold;		   //�䓁���\�����Ƃ��̉�
	int HIGESORI_SE;		   //�E���������̉�
	int StageClear;			    //�X�e�[�W�N���A����SE
	int Player_footStep;	   //�v���C���[�̑���
	int Player_footStep_DS;    //�v���C���[�̑����i�{���j
	int Menumove;			   //���j���[���ړ���SE
	int Menu_Select;		   //���j���[���ł̌��莞SE
	int Menu_Open;			   //���j���[�J��SE
	int Menu_Cansel;		   //���j���[���ł̃L�����Z��
	int Customer_Damage;	   //�t�L�f���̔j��
	int Customer_Cry[4];	   //�t�L�f���̔j��A�q�̋���
	int TimeUp;					//�^�C���A�b�v
	int ThreeCount;				//�O�b�J�E���g
	int ThreeCountStart;		//�O�b�J�E���g(�Q�[���J�n)
	int GameOver;			   //�Q�[���I�[�o�[��SE
	int TitleBGM;			   //�^�C�g����ʂ�BGM
	int StageBGM;			   //�X�e�[�W���ł�BGM

	int volume = 10;           // ����

};

int f_LoadSound(void);	//�֐��̒�`

