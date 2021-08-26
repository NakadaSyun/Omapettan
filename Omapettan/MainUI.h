#pragma once
#include "DxLib.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"

class c_MainUI {
public:
	c_MainUI(int bansokoImg);
	void f_init();		// ������
	void f_update();	// �X�V
	void f_draw();		// �`��

	bool hairStateFlg[HAIR_NUM] = { 0 };
	bool acneStateFlg[ACNE_NUM] = { 0 };

private:
	void MenuUI();		// ���j���[
	void TimeCountUI();	// ���ԃJ�E���g
	void AchievementUI();// �B����
	void LifeUI();		// ���C�t

	bool pauseFlg;		// �ꎞ��~�t���O

	int timeLimit;		// ��������
	int time;			// ���݂̎���
	int timer;			// ���ԃJ�E���g
	int minute;			// ��
	int second;			// �b

	int rate;			// ��

	int maxLife;		// �ő僉�C�t
	int life;			// ���C�t

	int bansoko_Img;
};