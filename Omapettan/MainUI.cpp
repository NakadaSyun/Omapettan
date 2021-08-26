#include "MainUI.h"

c_MainUI::c_MainUI(int bansokoImg) {
	c_MainUI::f_init();
	bansoko_Img = bansokoImg;
}

void c_MainUI::f_init() {

	pauseFlg = false;		// �ꎞ��~�t���O

	timeLimit = 0;			// ��������
	time = GetNowCount();	// ����
	timer = 0;				// ���ԃJ�E���g
	minute = 0;				// ��
	second = 0;				// �b

	rate = 0;				// ��

	maxLife = 3;			// �ő僉�C�t
	life = maxLife;			// ���C�t
}

void c_MainUI::f_update() {

	// ���ꂼ���UI����
	c_MainUI::MenuUI();
	c_MainUI::TimeCountUI();
	c_MainUI::AchievementUI();
	c_MainUI::LifeUI();
}

void c_MainUI::f_draw() {
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	SetFontSize(24);
	DrawFormatString(265, 5, 0x00ff00, "�o�ߎ���");
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
	// ���ԍX�V �i��100%�ŃX�g�b�v
	if(rate != 100){
		timer = GetNowCount() - time;
	}
	
	// �J�E���g�̏��
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