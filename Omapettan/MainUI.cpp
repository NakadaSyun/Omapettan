#include "MainUI.h"

c_MainUI::c_MainUI(int bansokoImg) {
	c_MainUI::f_init();
	bansoko_Img = bansokoImg;

	c_Pad = new c_GamePad();
}
c_MainUI::~c_MainUI() {
	delete c_Pad;
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

	count = 0;
}

void c_MainUI::f_update() {
	c_Pad->f_update();

	// ���ꂼ���UI����
	c_MainUI::MenuUI();

	if (pauseFlg == false) {
		c_MainUI::TimeCountUI();
		c_MainUI::AchievementUI();
		c_MainUI::LifeUI();
	}
}

void c_MainUI::f_draw() {
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	SetFontSize(24);
	DrawFormatString(24, 5, 0x00ff00, "�o�ߎ���");
	SetFontSize(48);
	DrawFormatString(10, 30, 0xffffff, "%02d:%02d", minute, second);

	DrawFormatString(530, 10, 0xffffff, "%03d%%", rate);
	DrawFormatString(590, 80, 0xff0000, "%d", life);

	for (int i = 0; i < life; i++) {
		DrawGraph(550, 100 + (50 * i), bansoko_Img, TRUE);
	}

	// �ꎞ��~���̕\��UI
	if (pauseFlg == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, 640, 480, 0x000000, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetFontSize(32);
		DrawFormatString(205, 150, 0xffffff, "�Q�[�����ĊJ");
		DrawFormatString(190, 200, 0xffffff, "�^�C�g���֖߂�");
		//DrawFormatString(222, 250, 0xffffff, "�I�v�V����");
	}

	SetFontSize(16);
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void c_MainUI::MenuUI() {

	if (c_Pad->IsButtonOption == true && count == 0) {
		if (pauseFlg == false) {
			pauseFlg = true;
		}
		else {
			// ���� = ���� + ((�N������ - ����) - �o�ߎ���)
			time = time + ((GetNowCount() - time) - timer);
			pauseFlg = false;
		}

		count++;
	}
	if (c_Pad->IsButtonOption == false) count = 0;

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