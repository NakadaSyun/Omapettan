#include "MainScene.h"
#include "ResultScene.h"
#include "LoadSound.h"
#include "TitleScene.h"

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
	//�p�b�h�̃L�[��������Ă��邩
	padKeyFlg = false;
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
	//if (DebugLoadTime > 120)
	{
		//if (c_gm->c_player->c_pad->crossKey == LEFT) {
		//	//�f�o�b�O���[�h�\��
		//	if (!DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = true;
		//		KeyDownFlg = true;
		//	}
		//	//�f�o�b�O���[�h��\��
		//	else if (DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = false;
		//		KeyDownFlg = true;
		//	}
		//}
		//if (c_gm->c_player->c_pad->crossKey == 0) {
		//	KeyDownFlg = false;
		//}
		//if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
		//	//�f�o�b�O���[�h�\��
		//	if (!DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = true;
		//		KeyDownFlg = true;
		//	}
		//	//�f�o�b�O���[�h��\��
		//	else if (DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = false;
		//		KeyDownFlg = true;
		//	}
		//}
		//if (CheckHitKey(KEY_INPUT_RETURN) == 0) {
		//	KeyDownFlg = false;
		//}
	}
	//else
	{
		//�ǂݍ��ݎ��ԉ��Z
		//DebugLoadTime++;
	}

	//�f�o�b�O���[�h��\�����邩���Ȃ���
	f_debug(DebugFlg);


	//�т��S�����ꂽ��ԂȂ�Result�V�[����
	if (c_gm->c_hair->f_hairStatusSee()) {
		isClearFlg = true;

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
	if (c_gm->c_acne->AcneStatus() && isClearFlg == false) {
		c_gm->c_player->IsMove = false;
		
		if (StageClearTime < 120)
		{
			StageClearTime++;
		}
		else if (StageClearTime < 240)
		{
			StageClearTime++;
			DrawGraph(0, 0, StageOverImage, false);
			if (CheckSoundMem(g_Snd.GameOver) == 0) {
				PlaySoundMem(g_Snd.GameOver, DX_PLAYTYPE_BACK);
			}
			
		}
		else
		{
			StopSoundMem(g_Snd.StageBGM);
			return new c_Result();
		}
	}

	// �|�[�Y���j���[����^�C�g����
	if (c_gm->c_mainUI->isBackTitle) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Title();
	}
	// �^�C���I�[�o�[�Ń��U���g��
	if (c_gm->c_mainUI->isNextResult) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Result();
	}

	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

void c_Main::f_debug(bool flg) {

	{
		//�\���L�[���������Ɩт��c�ɕ���
		if (c_gm->c_player->c_pad->crossKey == LEFT && !padKeyFlg && !DebugFlg)
		{
			DebugFlg = true;
			padKeyFlg = true;
		}
		else if (c_gm->c_player->c_pad->crossKey == LEFT && !padKeyFlg && DebugFlg)
		{
			DebugFlg = false;
			padKeyFlg = true;
		}

		if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
		{
			padKeyFlg = false;
			//DebugFlg = false;
		}

		if (DebugFlg)
		{
			//�т̓����蔻��\��
			c_gm->c_hair->CubeDraw();
			//�v���C���[�i�䓁�j�̓����蔻��\��
			c_gm->c_player->c_colision->CubeDraw();

			//�����o���̓����蔻��\��
			for (int num = 0; num < ACNE_NUM; num++)
			{
				c_gm->c_acne->c_collision[num]->CubeDraw();
			}

			//padKeyFlg = true;

		}
	}


	//�\���L�[���������Ɩт��c�ɕ���
	if (c_gm->c_player->c_pad->crossKey == DOWN && !padKeyFlg)
	{
		padKeyFlg = true;
		c_gm->c_hair->f_DebugHair(padKeyFlg, false);
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}

	//�\���L�[��������Ɩт�S�ď���
	if (c_gm->c_player->c_pad->crossKey == UP && !padKeyFlg)
	{
		padKeyFlg = true;
		c_gm->c_hair->f_DebugHair(padKeyFlg, true);
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}


	//�\���L�[�E�������ƃv���C���[�̃_�b�V���̔{����؂�ւ��ł���
	if (c_gm->c_player->c_pad->crossKey == RIGHT && !padKeyFlg)
	{
		//�v���C���[�̃_�b�V���̔{����������
		playerDebug = c_gm->c_player->f_PlayerDebug(padKeyFlg, playerDebug);
		padKeyFlg = true;
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}

}