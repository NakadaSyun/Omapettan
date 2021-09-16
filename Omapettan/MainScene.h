#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "GameManager.h"

class c_Main :public c_Scene{
public:
	c_Main();
	~c_Main();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;
	virtual void f_fadeout() override;		//�Ó]����
	virtual void f_fadein() override;			//���邭����

	c_GameManager* c_gm;
	
private:
	
	int Freq, Add;			//�X�e�[�WBGM�s�b�`�ύX

	int StageClearImage;	//�X�e�[�W�N���A�摜
	int StageOverImage;	//�X�e�[�W�N���A�摜
	int StageClearTime = 0; //�N���A�J�E���g�p

	int Brightness;		//���邳�����p�ϐ�
	int SceneSeq;		//�t�F�[�h�p�ϐ�

	bool DebugFlg; //�f�o�b�O���[�h�\���E��\���p�t���O
	bool KeyDownFlg;//�L�[�������ꂽ�ǂ����̃t���O

	void f_debug(bool flg);
	int DebugLoadTime;
	bool padKeyFlg = false;
	bool playerDebug = false;

	bool isClearFlg = false;

	void f_debugUI();
};