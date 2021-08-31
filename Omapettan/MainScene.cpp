#include "MainScene.h"
#include "ResultScene.h"
#include "LoadSound.h"

extern Sound g_Snd;

c_Main::c_Main() {
	//�Q�[���}�l�[�W���[����
	c_gm = new c_GameManager();

	// �Q�[���}�l�W��������
	c_gm->f_init();
	IsNextScene = false;

	//
	StageOverImage = LoadGraph("images/GameOver.png");
	StageClearImage = LoadGraph("images/StageClear.png");
	
	//�f�o�b�O���[�h���\��
	DebugFlg = false;
	//�L�[��������ĂȂ���Ԃ�
	KeyDownFlg = false;
}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();

	//�X�e�[�WBGM����
	if (CheckSoundMem(g_Snd.StageBGM) == 0) {
		PlaySoundMem(g_Snd.StageBGM, DX_PLAYTYPE_LOOP);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Result();
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
	}

	//�f�o�b�O���[�h�̎�t����
	if (DebugLoadTime > 120)
	{
		if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
			//�f�o�b�O���[�h�\��
			if (!DebugFlg && !KeyDownFlg)
			{
				DebugFlg = true;
				KeyDownFlg = true;
			}
			//�f�o�b�O���[�h��\��
			else if (DebugFlg && !KeyDownFlg)
			{
				DebugFlg = false;
				KeyDownFlg = true;
			}
		}
		if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
			KeyDownFlg = false;
		}
	}
	else
	{
		//�ǂݍ��ݎ��ԉ��Z
		DebugLoadTime++;
	}

	//�f�o�b�O���[�h��\�����邩���Ȃ���
	f_debug(DebugFlg);


	//�т��S�����ꂽ��ԂȂ�Result�V�[����
	if (c_gm->c_hair->f_hairStatusSee()) {
		
		if (StageClearTime < 120)
		{
			StageClearTime++;
		}
		else if (StageClearTime < 240)
		{
			StageClearTime++;
			DrawGraph(0, 0, StageClearImage, true);
			if (CheckSoundMem(g_Snd.StageClear) == 0) {
				PlaySoundMem(g_Snd.StageClear, DX_PLAYTYPE_BACK);
			}
			
		}
		else
		{

			StopSoundMem(g_Snd.StageBGM);
			return new c_Result();
		}
	}
	
	//�����o�����S�����ꂽ��ԂȂ�Result�V�[����
	if (c_gm->c_acne->AcneStatus()) {
		c_gm->c_player->IsMove = false;
		
		if (StageClearTime < 120)
		{
			StageClearTime++;
		}
		else if (StageClearTime < 240)
		{
			StageClearTime++;
			DrawGraph(0, 0, StageOverImage, false);
			if (CheckSoundMem(g_Snd.StageClear) == 0) {
				PlaySoundMem(g_Snd.GameOver, DX_PLAYTYPE_BACK);
			}
			
		}
		else
		{
			StopSoundMem(g_Snd.StageBGM);
			return new c_Result();
		}
	}

	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

void c_Main::f_debug(bool flg) {
	if (flg)
	{
		c_gm->c_hair->CubeDraw();

		c_gm->c_player->c_colision->CubeDraw();
	}
}