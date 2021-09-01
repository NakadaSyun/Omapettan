#include "MainScene.h"
#include "ResultScene.h"
#include "LoadSound.h"
#include "TitleScene.h"

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
	
	//デバッグモードを非表示
	DebugFlg = false;
	//キーが押されてない状態に
	KeyDownFlg = false;
}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();

	//ステージBGM処理
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

	//デバッグモードの受付時間
	if (DebugLoadTime > 120)
	{
		if (CheckHitKey(KEY_INPUT_RETURN) == 1) {
			//デバッグモード表示
			if (!DebugFlg && !KeyDownFlg)
			{
				DebugFlg = true;
				KeyDownFlg = true;
			}
			//デバッグモード非表示
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
		//読み込み時間加算
		DebugLoadTime++;
	}

	//デバッグモードを表示するかしないか
	f_debug(DebugFlg);


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

			StopSoundMem(g_Snd.StageBGM);
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
			StopSoundMem(g_Snd.StageBGM);
			return new c_Result();
		}
	}

	if (c_gm->c_mainUI->isBackTitle) {
		return new c_Title();
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