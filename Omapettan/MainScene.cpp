#include "MainScene.h"
#include "ResultScene.h"
#include "LoadSound.h"

extern Sound g_Snd;

c_Main::c_Main() {
	//ゲームマネージャー生成
	c_gm = new c_GameManager();

	// ゲームマネジャ初期化
	c_gm->f_init();
	IsNextScene = false;

	//
	StageOverImage = LoadGraph("images/GameOver.png");
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

	//毛が全部剃られた状態ならResultシーンへ
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
			return new c_Result();
		}
	}
	
	//吹き出物が全部剃られた状態ならResultシーンへ
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
			return new c_Result();
		}
	}

	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

