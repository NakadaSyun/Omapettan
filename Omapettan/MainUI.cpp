#include "MainUI.h"
#include "TitleScene.h"

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

	timeLimit = 0;			// 制限時間
	time = GetNowCount();	// 時間
	timer = 0;				// 時間カウント
	minute = 0;				// 分
	second = 0;				// 秒

	rate = 0.0f;			// 率

	maxLife = 3;			// 最大ライフ
	life = maxLife;			// ライフ

	menuNum = 0;

	count = 0;

	isBackTitle = false;
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

	SetFontSize(48);// サイズ48
	DrawFormatString(10, 30, 0xffffff, "%02d:%02d", minute, second);

	//DrawFormatString(590, 80, 0xff0000, "%d", life);

	DrawFormatString(480, 30, 0xffffff, "%03d.", (int)rate);
	DrawFormatString(600, 28, 0xffffff, "%%");

	SetFontSize(32);// サイズ32
	DrawFormatString(575, 42, 0xffffff, "%d", int((rate - (int)rate) * 10.0f));

	SetFontSize(24);// サイズ24
	DrawFormatString(24, 5, 0x00ff00, "経過時間");
	DrawFormatString(510, 5, 0x00ff00, "剃毛率");

	SetFontSize(16);// サイズ16
	DrawFormatString(5, 460, 0xffffff, "[START] ポーズ");

	for (int i = 0; i < life; i++) {
		DrawGraph(550, 100 + (50 * i), bansoko_Img, TRUE);
	}

	// 一時停止時の表示UI
	if (pauseFlg == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, 640, 480, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(32);
		//DrawFormatString(222, 250, 0xffffff, "オプション");
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

	SetFontSize(16);
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void c_MainUI::MenuUI() {
	// [START]で一時停止、もう一度押すと再開
	if (c_Pad->IsButtonOption == true && count == 0) {
		if (pauseFlg == false) {
			pauseFlg = true;
		}
		else {
			// 時間 = 時間 + ((起動時間 - 時間) - 経過時間)
			time = time + ((GetNowCount() - time) - timer);
			pauseFlg = false;
		}

		count++;
	}
	if (c_Pad->IsButtonOption == false) count = 0;

	// ポーズ中の操作
	if (pauseFlg == true) {
		// 上を押したとき
		if (c_Pad->LeftStick == UP) {
			menuNum = 0;
		}
		// 下を押したとき
		if (c_Pad->LeftStick == DOWN) {
			menuNum = 1;
		}
		// [A]を押したとき
		if (c_Pad->IsButton1 == true) {
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
	// 時間更新 進捗100%でストップ
	if(rate != 100){
		timer = GetNowCount() - time;
	}
	
	// カウントの上限
	if (minute != 99 || second != 59) {
		minute = timer / 60000;
		second = (timer / 1000) - (minute * 60);
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
}