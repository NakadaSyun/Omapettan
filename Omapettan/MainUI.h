#pragma once
#include "DxLib.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "Controller.h"

class c_MainUI {
public:
	c_MainUI(int bansokoImg, int mainUIImg);
	~c_MainUI();
	void f_init();		// ������
	void f_update();	// �X�V
	void f_draw();		// �`��

	void MenuUI();		// ���j���[
	bool pauseFlg;		// �ꎞ��~�t���O

	bool hairStateFlg[HAIR_NUM] = { 0 };
	bool acneStateFlg[ACNE_NUM] = { 0 };

	c_GamePad* c_Pad;

	bool isBackTitle;

private:
	void TimeCountUI();	// ���ԃJ�E���g
	void AchievementUI();// �B����
	void LifeUI();		// ���C�t

	int timeLimit;		// ��������
	int time;			// ���݂̎���
	int timer;			// ���ԃJ�E���g
	int minute;			// ��
	int second;			// �b

	float rate;			// ��

	int maxLife;		// �ő僉�C�t
	int life;			// ���C�t

	int menuNum;		// �|�[�Y���̑I�����Ă���ԍ�

	int bansoko_Img;
	int mainUI_Img;

	int count;
};