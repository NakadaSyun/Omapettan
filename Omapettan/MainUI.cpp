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

	timeLimit = 600;			// 制限時間
	time = GetNowCount();	// 時間
	timer = 0;				// 時間カウント
	minute = timeLimit / 60;			// 分
	second = timeLimit - (60 * minute);	// 秒
	animCount = 0.0f;

	rate = 0.0f;			// 率

	maxLife = ACNE_NUM - 1;	// 最大ライフ
	life = maxLife;			// ライフ
	animSpeed = 0.0f;
	damageAnim = 0;

	menuNum = 0;

	menuCount = 0;

	isBackTitle = false;
	isNextResult = false;
}

void c_MainUI::f_update() {
	c_Pad->f_update();

	// それぞれのUI処理
	c_MainUI::MenuUI();

	if (pauseFlg == false) {
		c_MainUI::TimeCountUI();
		c_MainUI::AchievementUI();
		c_MainUI::LifeUI();
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

	SetFontSize(16);
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void c_MainUI::MenuUI() {
	// [START]で一時停止、もう一度押すと再開
	if (c_Pad->IsButtonOption == true && menuCount == 0) {
		if (pauseFlg == false) {
			PlaySoundMem(g_Snd.Menu_Open, DX_PLAYTYPE_BACK);
			pauseFlg = true;
		}
		else {
			PlaySoundMem(g_Snd.Menu_Cansel, DX_PLAYTYPE_BACK);
			// 時間 = 時間 + ((起動時間 - 時間) - 経過時間)
			time = time + ((GetNowCount() - time) - timer);
			pauseFlg = false;
		}

		menuCount++;
	}
	if (c_Pad->IsButtonOption == false) menuCount = 0;

	// ポーズ中の操作
	if (pauseFlg == true) {
		// 上を押したとき
		if (c_Pad->LeftStick == UP && menuNum == 1) {
			menuNum = 0;
			PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
		}
		// 下を押したとき
		if (c_Pad->LeftStick == DOWN && menuNum == 0) {
			PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
			menuNum = 1;
		}
		// [A]を押したとき
		if (c_Pad->IsButton1 == true) {
			PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);

			switch (menuNum){
			case 0:
				// [ゲームを再開]選択
				time = time + ((GetNowCount() - time) - timer);
				pauseFlg = false;
				break;
			case 1:
				// [タイトルへ戻る]選択
				isBackTitle = true;
				break;
			default:
				break;
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
		isNextResult = true;
	}

	//// カウントの上限
	//if (minute != 99 || second != 59) {
	//	//minute = timer / 60000;
	//	//second = (timer / 1000) - (minute * 60);
	//}

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
		switch (menuNum)
		{
		case 0:
			// [ゲームを再開]選択
			DrawFormatString(205, 150, 0xff0000, "ゲームを再開");
			DrawFormatString(190, 200, 0xffffff, "タイトルへ戻る");
			break;

		case 1:
			// [タイトルへ戻る]選択
			DrawFormatString(205, 150, 0xffffff, "ゲームを再開");
			DrawFormatString(190, 200, 0xff0000, "タイトルへ戻る");
			break;

		default:

			break;
		}
	}

}

void c_MainUI::TimeCount_Draw() {
	SetFontSize(48);// サイズ48
	DrawFormatString(10, 30, 0xffffff, "%02d:%02d", minute, second);

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