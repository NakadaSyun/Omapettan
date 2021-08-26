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
	//StageClearImage = LoadGraph("images/Result.png");
	StageClearImage = LoadGraph("images/StageClear.png");
	
}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		return new c_Result();
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
	}

	//�т��S�����ꂽ��ԂȂ�Result�V�[����
	if (c_gm->c_hair->f_hairStatusSee()) {
		/*if (StageClearTime <240)
		{
			DrawGraph(0, 0, StageClearImage, true);
			StageClearTime++;
		}
		else
		{
			return new c_Result();
		}*/

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
			return new c_Result();
		}
	}

	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

