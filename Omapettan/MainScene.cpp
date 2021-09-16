#include "MainScene.h"
#include "ResultScene.h"
#include "LoadSound.h"
#include "TitleScene.h"

extern Sound g_Snd;
//DATEDATA Date;
//
//static int yeah;
//static int mon;
//static int day;
//static int hour;
//static int minute;
//static int sec;
int LightHandle;
c_Main::c_Main() {
	//ゲームマネージャー生成
	c_gm = new c_GameManager();// ライトハンドルのライトの効果がわかり易いように標準ライトを無効化
	
	// ゲームマネジャ初期化
	c_gm->f_init();
	IsNextScene = false;

	//
	StageOverImage = LoadGraph("images/GameOver.png");
	StageClearImage = LoadGraph("images/StageClear.png");
	TimeUPImage = LoadGraph("images/TimeUP.png");
	
	//デバッグモードを非表示
	DebugFlg = false;
	//キーが押されてない状態に
	KeyDownFlg = false;
	//パッドのキーが押されているか
	padKeyFlg = false;

	Freq = 60050;
	//int Add = 10;

	//GetDateTime(&Date);
	//yeah = Date.Year;
	//mon = Date.Mon;
	//day = Date.Day;
	//hour = Date.Hour;
	//minute = Date.Min;
	//sec = Date.Sec;

	SceneSeq = IDOL;
	Brightness = 255;

	ChangeVolumeSoundMem(int(150.0 / 255 * 25.5 * float(g_Snd.volume)), g_Snd.StageBGM);

}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();

	const char data[] = __DATE__;
	const char time[] = __TIME__;
	DrawFormatString(500, 420, 0x0000ff, "%c%c%c%c %c%c%c %c%c\n %s",
		data[7], data[8], data[9], data[10],
		data[0], data[1], data[2],
		data[4], data[5],
		time);
	

	//DrawFormatString(300, 460, 0x0000ff, "ビルド作成日時%d年%d月%d日%d時%d分%d秒\n", yeah, mon, day, hour, minute, sec);

	//ステージBGM処理
	if (CheckSoundMem(g_Snd.StageBGM) == 0 && c_gm->c_mainUI->startFlg == true) {
		SetFrequencySoundMem(48000, g_Snd.StageBGM);
		PlaySoundMem(g_Snd.StageBGM, DX_PLAYTYPE_LOOP);
	}
	if (c_gm->c_mainUI->f_getTimer() > 60000)
	{
		SetFrequencySoundMem(Freq, g_Snd.StageBGM);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Result(c_gm->c_mainUI->rate, c_gm->c_acne->f_AcneAliveNum());
	}
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
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
			ChangeVolumeSoundMem(240 - (StageClearTime - 120) * 2, g_Snd.StageBGM);
			StageClearTime++;
			DrawGraph(0, 0, StageClearImage, false);
			if (CheckSoundMem(g_Snd.StageClear) == 0) {
				PlaySoundMem(g_Snd.StageClear, DX_PLAYTYPE_BACK);
			}
			
		}
		else
		{
			if (SceneSeq == IDOL) {
				DrawGraph(0, 0, StageClearImage, false);
				f_fadeout();
				return this;
			}
			StopSoundMem(g_Snd.StageBGM);
			return new c_Result(c_gm->c_mainUI->rate, c_gm->c_acne->f_AcneAliveNum());
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
			if (SceneSeq == IDOL) {
				DrawGraph(0, 0, StageOverImage, false);
				f_fadeout();
				return this;
			}
			StopSoundMem(g_Snd.StageBGM);
			return new c_Result(c_gm->c_mainUI->rate, c_gm->c_acne->f_AcneAliveNum());
		}
	}

	// ポーズメニューからタイトルへ
	if (c_gm->c_mainUI->isBackTitle) {
		StopSoundMem(g_Snd.StageBGM);
		return new c_Title();
	}
	// タイムオーバーでリザルトへ
	if (c_gm->c_mainUI->isNextResult) {
		c_gm->c_player->IsMove = false;
		StopSoundMem(g_Snd.StageBGM);

		if (StageClearTime < 180)
		{
			StageClearTime++;
			DrawGraph(0, 0, TimeUPImage, true);
			//ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
			//SetFontSize(64);// サイズ64
			//DrawFormatString(190, 200, 0x00ff00, "TIME UP!");
			//SetFontSize(16);// サイズ16
			//ChangeFontType(DX_FONTTYPE_NORMAL);
		}
		else
		{
			if (SceneSeq == IDOL) {
				DrawGraph(0, 0, TimeUPImage, true);
				f_fadeout();
				return this;
			}
			return new c_Result(c_gm->c_mainUI->rate, c_gm->c_acne->f_AcneAliveNum());
		}
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
	int timeLimit = 2;
	c_gm->c_mainUI->timeLimit = timeLimit + (c_gm->c_mainUI->f_getTimer() / 1000);
}


void c_Main::f_fadein() {
	Brightness += 3;
	if (Brightness > 255) {
		SceneSeq = IDOL;
		Brightness = 255;
	}
	SetDrawBright(Brightness, Brightness, Brightness);

}

void c_Main::f_fadeout() {
	Brightness -= 3;
	if (Brightness < 0) {
		Brightness = 0;
		SceneSeq = NEXT_SCENE;
	}
	else {
		SetDrawBright(Brightness, Brightness, Brightness);
	}
}