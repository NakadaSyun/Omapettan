#include "MainUI.h"
#include "TitleScene.h"
#include "LoadSound.h"

extern Sound g_Snd;

c_MainUI::c_MainUI(int bansokoImg, int mainUIImg) {
	c_MainUI::f_init();
	bansoko_Img = bansokoImg;
	mainUI_Img = mainUIImg;

	c_Pad = new c_GamePad();
}
c_MainUI::~c_MainUI() {
	delete c_Pad;
}

void c_MainUI::f_init() {

	pauseFlg = false;		// 一時停止フラグ

	timeLimit = 90;			// 制限時間
	time = GetNowCount();	// 時間
	timer = 0;				// 時間カウント
	minute = timeLimit / 60;			// 分
	second = timeLimit - (60 * minute);	// 秒
	animCount = 0.0f;
	oldTime = 0;

	rate = 0.0f;			// 率

	maxLife = ACNE_NUM - 1;	// 最大ライフ
	life = maxLife;			// ライフ
	animSpeed = 0.0f;
	damageAnim = 0;

	menuNum = 0;

	menuCount = 0;

	isBackTitle = false;
	isNextResult = false;

	threeCountTime = 0;
	startFlg = false;

	setVolumeFlg = false;
	sliderValue = 50;
	padInputFlg = false;
}

void c_MainUI::f_update() {
	c_Pad->f_update();

	if (threeCountTime < 200) {
		c_MainUI::ThreeCount();
		c_MainUI::f_GetStartFlg();
	}

	if(startFlg == true) {
		// それぞれのUI処理
		c_MainUI::MenuUI();

		if (pauseFlg == false) {
			c_MainUI::TimeCountUI();
			c_MainUI::AchievementUI();
			c_MainUI::LifeUI();
		}
	}
}

void c_MainUI::f_draw() {

	DrawGraph(0, 0, mainUI_Img, TRUE);

	// UIのテキスト部分全て
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	c_MainUI::TimeCount_Draw();
	c_MainUI::Achivement_Draw();
	c_MainUI::Life_Draw();
	c_MainUI::Menu_Draw();

	if (threeCountTime < 200) {
		c_MainUI::ThreeCount_Draw();
	}
	SetFontSize(16);
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void c_MainUI::MenuUI() {
	// [START]で一時停止、もう一度押すと再開
	if (c_Pad->IsButtonOption == true && menuCount == 0) {
		if (pauseFlg == false) {
			pauseFlg = true;
			setVolumeFlg = false;
			sliderValue = g_Snd.volume;

			PlaySoundMem(g_Snd.Menu_Open, DX_PLAYTYPE_BACK);
		}
		else {
			// 時間 = 時間 + ((起動時間 - 時間) - 経過時間)
			time = time + ((GetNowCount() - time) - timer);
			pauseFlg = false;

			PlaySoundMem(g_Snd.Menu_Cansel, DX_PLAYTYPE_BACK);
		}

		menuCount++;
	}
	if (c_Pad->IsButtonOption == false) menuCount = 0;

	// ポーズ中の操作
	if (pauseFlg == true) {
		if (InputAcceptManage() == true) {
			if (setVolumeFlg == true) {
				SetVolumeOperation();
			}
			else {
				// 上を押したとき
				if (c_Pad->LeftStick == UP) {
					if(menuNum-- == 0)
						menuNum = 2;
					padInputFlg = true;
					PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
				}
				// 下を押したとき
				if (c_Pad->LeftStick == DOWN){
					if (menuNum++ == 2)
						menuNum = 0;
					padInputFlg = true;
					PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
				}
				// [A]を押したとき
				if (c_Pad->IsButton1 == true) {
					padInputFlg = true;
					PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);

					switch (menuNum) {
					case 0:
						// [ゲームを再開]選択
						time = time + ((GetNowCount() - time) - timer);
						pauseFlg = false;
						break;

					case 1:
						// [サウンド]選択
						setVolumeFlg = true;
						break;

					case 2:
						// [タイトルへ戻る]選択
						isBackTitle = true;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else {
		menuNum = 0;
	}

}

void c_MainUI::TimeCountUI() {
	int count = 0;

	// 時間更新 (進捗100%・ゲームオーバーでストップ)
	if(rate != 100 && life > -1){
		timer = GetNowCount() - time;
	}
	count = timeLimit - (timer / 1000);

	// カウントの上限
	if (count >= 0) {
		minute = count / 60;
		second = count - (minute * 60);
	}
	else {
		// リザルトシーンへ
		if (isNextResult == false) {
			PlaySoundMem(g_Snd.TimeUp, DX_PLAYTYPE_BACK);
		}
		isNextResult = true;
	}

	//// カウントの上限
	//if (minute != 99 || second != 59) {
	//	//minute = timer / 60000;
	//	//second = (timer / 1000) - (minute * 60);
	//}

	// 残り30秒でフォントの色を動かす
	if (((timer / 1000) != oldTime) && count >= 0) {
		if (animCount > 30.0f) {
			oldTime = (timer / 1000);
			animCount = 0.0f;
		}
		else animCount += 1.0f;
	}
	else {
		animCount = 0.0f;
	}
}

void c_MainUI::AchievementUI() {

	for (int i = 0, num = 0; i < HAIR_NUM; i++) {
		if (hairStateFlg[i] == false) {
			num++;
		}
		rate = (float)num / HAIR_NUM * 100.0f;
	}
}

void c_MainUI::LifeUI() {

	for (int i = 0, num = 0; i < ACNE_NUM; i++) {
		if (acneStateFlg[i] == false) {
			num++;
		}
		life = num - 1;
	}

	if (life < maxLife) {
		if (damageAnim < 120) damageAnim += 15;
		else {
			damageAnim = 0;
			maxLife = life;
		}
	}

	if (animSpeed > 10.0f * life) animSpeed = 0.0f;
	else animSpeed += 0.5f;
}

void c_MainUI::ThreeCount() {
	if (threeCountTime % 50 == 0 && threeCountTime / 50 < 3) {
		PlaySoundMem(g_Snd.ThreeCount, DX_PLAYTYPE_BACK);
	}
	if (threeCountTime / 50 == 3 && CheckSoundMem(g_Snd.ThreeCountStart) == 0) {
		PlaySoundMem(g_Snd.ThreeCountStart, DX_PLAYTYPE_BACK);
	}

	if (threeCountTime < 200) threeCountTime++;
	else threeCountTime = 200;

	if (threeCountTime > 150) {
		time = GetNowCount();
		startFlg = true;
	}
}

void c_MainUI::Menu_Draw() {
	SetFontSize(16);// サイズ16
	DrawFormatString(5, 460, 0xffffff, "[START] ポーズ");

	// 一時停止時の表示UI
	if (pauseFlg == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, 640, 480, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(48);// サイズ48
		DrawFormatString(185, 10, 0xffffff, "- ポーズ -");
		SetFontSize(32);
		//DrawFormatString(222, 250, 0xffffff, "サウンド");
		
		if (setVolumeFlg == true)
			DrawSetVolume();
		else
			switch (menuNum)
			{
			case 0:
				// [ゲームを再開]選択
				DrawFormatString(205, 150, 0xff0000, "ゲームを再開");
				DrawFormatString(220, 200, 0xffffff, "サウンド");
				DrawFormatString(190, 250, 0xffffff, "タイトルへ戻る");
				break;

			case 1:
				// [音量設定]選択
				DrawFormatString(205, 150, 0xffffff, "ゲームを再開");
				DrawFormatString(220, 200, 0xff0000, "サウンド");
				DrawFormatString(190, 250, 0xffffff, "タイトルへ戻る");
				break;

			case 2:
				// [タイトルへ戻る]選択
				DrawFormatString(205, 150, 0xffffff, "ゲームを再開");
				DrawFormatString(220, 200, 0xffffff, "サウンド");
				DrawFormatString(190, 250, 0xff0000, "タイトルへ戻る");
				break;

			default:

				break;
			}
	}

}

void c_MainUI::TimeCount_Draw() {
	SetFontSize(48);// サイズ48
	DrawFormatString(10, 30, 0xffffff, "%02d:%02d", minute, second);
	if (minute == 0 && second <= 30) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - animCount * 25);
		DrawFormatString(10, 30, 0xff0000, "%02d:%02d", minute, second);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	SetFontSize(24);// サイズ24
	DrawFormatString(24, 5, 0x00ff00, "残り時間");
}

void c_MainUI::Achivement_Draw() {
	SetFontSize(48);// サイズ48
	DrawFormatString(480, 30, 0xffffff, "%03d.", (int)rate);
	DrawFormatString(600, 28, 0xffffff, "%%");

	SetFontSize(32);// サイズ32
	DrawFormatString(575, 42, 0xffffff, "%d", int((rate - (int)rate) * 10.0f));

	SetFontSize(24);// サイズ24
	DrawFormatString(510, 5, 0x00ff00, "剃毛率");
}

void c_MainUI::Life_Draw() {
	for (int i = 0; i < ACNE_NUM - 1; i++) {
		if (i < life) {
			DrawGraph(550, 100 + (50 * i), bansoko_Img, TRUE);
		}
		//else {
		//	SetDrawBright(0,0,0);
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		//	DrawGraph(550, 100 + (50 * i), bansoko_Img, TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//	SetDrawBright(255, 255, 255);
		//}

		if (i == life - 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - animSpeed * 25);
			DrawModiGraph(550 - animSpeed, 100 + (50 * i) - animSpeed,
				650 + animSpeed, 100 + (50 * i) - animSpeed,
				650 + animSpeed, 200 + (50 * i) + animSpeed,
				550 - animSpeed, 200 + (50 * i) + animSpeed,
				bansoko_Img, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, damageAnim);
	DrawBox(0, 0, 640, 480, 0xff0000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void c_MainUI::ThreeCount_Draw() {
	SetFontSize(96);// サイズ96
	if (threeCountTime < 150) {
		DrawFormatString(295, 120, 0xffffff, "%d", 3 - (threeCountTime / 50));
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 + ((150 - threeCountTime) * 5));
		DrawFormatString(260, 120 + ((150 - threeCountTime) * 2), 0xffffff, "GO!");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

int c_MainUI::f_getTimer() {
	return timer;
}

void c_MainUI::DrawSetVolume() {

	DrawFormatString(220, 190, 0xffffff, "サウンド");
	DrawFormatString(220, 230, 0xffffff, "--------");
	DrawFormatString(220 + sliderValue * 12, 230, 0xffffff, "●");
	
}

void c_MainUI::SetVolumeOperation() {


	// 右を押したとき
	if (c_Pad->LeftStick == RIGHT) {
		if (sliderValue < 10)
			sliderValue++;
		padInputFlg = true;

		g_Snd.SetSound_Menumove(sliderValue);
		PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
	}
	// 左を押したとき
	if (c_Pad->LeftStick == LEFT) {
		if (sliderValue > 0)
			sliderValue--;
		padInputFlg = true;

		g_Snd.SetSound_Menumove(sliderValue);
		PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
	}
	// [A]を押したとき
	if (c_Pad->IsButton1 == true) {
		setVolumeFlg = false;
		padInputFlg = true;
		g_Snd.volume = sliderValue;
		
		g_Snd.SetSound();
		PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);
	}
}

bool c_MainUI::InputAcceptManage() {


	// 入力を受け付けるか判断
	// 入力拒否時間が 0 より大きければ受け入れない（false）
	//                  以下ならば受け入れる　    （true）
	if (inputRefusalTime > 0) {
		inputRefusalTime--;
		return false;
	}
	else if (padInputFlg == false) {
		return true;
	}
	else
	{
		padInputFlg = false;
		inputRefusalTime = 15;
		return false;
	}
}