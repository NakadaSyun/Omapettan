#include "MainUI.h"

c_MainUI::c_MainUI(int bansokoImg) {
	c_MainUI::f_init();
	bansoko_Img = bansokoImg;
}

void c_MainUI::f_init() {

	pauseFlg = false;		// 一時停止フラグ

	timeLimit = 0;			// 制限時間
	time = GetNowCount();	// 時間
	timer = 0;				// 時間カウント
	minute = 0;				// 分
	second = 0;				// 秒

	rate = 0;				// 率

	maxLife = 3;			// 最大ライフ
	life = maxLife;			// ライフ
}

void c_MainUI::f_update() {

	// それぞれのUI処理
	c_MainUI::MenuUI();
	c_MainUI::TimeCountUI();
	c_MainUI::AchievementUI();
	c_MainUI::LifeUI();
}

void c_MainUI::f_draw() {
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	SetFontSize(24);
	DrawFormatString(265, 5, 0x00ff00, "経過時間");
	SetFontSize(48);
	DrawFormatString(253, 30, 0xffffff, "%02d:%02d", minute, second);

	DrawFormatString(530, 10, 0xffffff, "%03d%%", rate);
	DrawFormatString(590, 80, 0xff0000, "%d", life);

	SetFontSize(16);
	ChangeFontType(DX_FONTTYPE_NORMAL);

	for (int i = 0; i < life; i++) {
		DrawGraph(550, 100 + (50 * i), bansoko_Img, TRUE);
	}
}

void c_MainUI::MenuUI() {

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