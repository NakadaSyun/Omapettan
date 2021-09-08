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
	//パッドのキーが押されているか
	padKeyFlg = false;
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
		return new c_Result(c_gm->c_mainUI->rate);
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
	}

	//デバッグモードの受付時間
	//if (DebugLoadTime > 120)
	{
		//if (c_gm->c_player->c_pad->crossKey == LEFT) {
		//	//デバッグモード表示
		//	if (!DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = true;
		//		KeyDownFlg = true;
		//	}
		//	//デバッグモード非表示
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
		//	//デバッグモード表示
		//	if (!DebugFlg && !KeyDownFlg)
		//	{
		//		DebugFlg = true;
		//		KeyDownFlg = true;
		//	}
		//	//デバッグモード非表示
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
		//読み込み時間加算
		//DebugLoadTime++;
	}

	//デバッグモードを表示するかしないか
	f_debug(DebugFlg);


	//毛が全部剃られた状態ならResultシーンへ
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
			return new c_Result(c_gm->c_mainUI->rate);
		}
	}
	
	//吹き出物が全部剃られた状態ならResultシーンへ
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
			return new c_Result(c_gm->c_mainUI->rate);
		}
	}

	// ポーズメニューからタイトルへ
	if (c_gm->c_mainUI->isBackTitle) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Title();
	}
	// タイムオーバーでリザルトへ
	if (c_gm->c_mainUI->isNextResult) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Result(c_gm->c_mainUI->rate);
	}

	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

void c_Main::f_debug(bool flg) {

	{
		//十字キー下を押すと毛が縦に並ぶ
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
			//毛の当たり判定表示
			c_gm->c_hair->CubeDraw();
			//プレイヤー（剃刀）の当たり判定表示
			c_gm->c_player->c_colision->f_PolyDraw(c_gm->c_player->f_GetPlayerRotationY());

			//吹き出物の当たり判定表示
			for (int num = 0; num < ACNE_NUM; num++)
			{
				// 吹き出物の当たり判定表示
				c_gm->c_acne->c_collision[num]->f_CubeDraw();
			}

			//padKeyFlg = true;

		}
	}


	//十字キー下を押すと毛が縦に並ぶ
	if (c_gm->c_player->c_pad->crossKey == DOWN && !padKeyFlg)
	{
		padKeyFlg = true;
		c_gm->c_hair->f_DebugHair(padKeyFlg, false);
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}

	//十字キー上を押すと毛を全て消す
	if (c_gm->c_player->c_pad->crossKey == UP && !padKeyFlg)
	{
		padKeyFlg = true;
		c_gm->c_hair->f_DebugHair(padKeyFlg, true);
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}


	//十字キー右を押すとプレイヤーのダッシュの倍率を切り替えできる
	if (c_gm->c_player->c_pad->crossKey == RIGHT && !padKeyFlg)
	{
		//プレイヤーのダッシュの倍率をあげる
		playerDebug = c_gm->c_player->f_PlayerDebug(padKeyFlg, playerDebug);
		padKeyFlg = true;
	}
	else if (c_gm->c_player->c_pad->crossKey == 0 && padKeyFlg)
	{
		padKeyFlg = false;
	}

	//Yボタンを押すと時間が０になる
	if (c_gm->c_player->c_pad->IsButton4)
	{
		f_debugUI();
	}

}

void c_Main::f_debugUI() {
	c_gm->c_mainUI->timeLimit = 0;
}