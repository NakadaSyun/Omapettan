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
	bool isNextResult;

	int timeLimit;		// ��������
	float rate;			// ��

	int f_getTimer(); //timer�̒l���擾

private:
	void TimeCountUI();	// ���ԃJ�E���g
	void AchievementUI();// �B����
	void LifeUI();		// ���C�t

	void Menu_Draw();
	void TimeCount_Draw();
	void Achivement_Draw();
	void Life_Draw();

	int time;			// ���݂̎���
	int timer;			// ���ԃJ�E���g
	int minute;			// ��
	int second;			// �b
	float animCount;

	int maxLife;		// �ő僉�C�t
	int life;			// ���C�t
	float animSpeed;		// ���C�t�̃A�j���[�V�����X�s�[�h
	int damageAnim;		// �_���[�W

	int menuNum;		// �|�[�Y���̑I�����Ă���ԍ�

	int bansoko_Img;
	int mainUI_Img;

	int menuCount;
};