#pragma once
#include "DxLib.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"
#include "Controller.h"

class c_MainUI {
public:
	c_MainUI(int bansokoImg, int mainUIImg, int soundIconImg);
	~c_MainUI();
	void f_init();		// ������
	void f_update();	// �X�V
	void f_draw();		// �`��

	void MenuUI();		// ���j���[

	int f_GetStartFlg();//startFlg���擾����֐�

	bool pauseFlg;		// �ꎞ��~�t���O

	bool hairStateFlg[HAIR_NUM] = { 0 };
	bool acneStateFlg[ACNE_NUM] = { 0 };

	c_GamePad* c_Pad;

	bool isBackTitle;
	bool isNextResult;

	int timeLimit;		// ��������
	float rate;			// ��
	int life;			// ���C�t

	int f_getTimer(); //timer�̒l���擾

	int startFlg;

private:
	void TimeCountUI();	// ���ԃJ�E���g
	void AchievementUI();// �B����
	void LifeUI();		// ���C�t
	void ThreeCount();	// 3�b�J�E���g

	void Menu_Draw();
	void TimeCount_Draw();
	void Achivement_Draw();
	void Life_Draw();
	void ThreeCount_Draw();

	void DrawSetVolume();              // ���ʐݒ��ʕ\��
	void SetVolumeOperation();         // ���ʐݒ葀��
	bool InputAcceptManage();          // ���͎󂯓���Ǘ�   true:�󂯓���   false;����

	int time;			// ���݂̎���
	int timer;			// ���ԃJ�E���g
	int minute;			// ��
	int second;			// �b
	float animCount;
	int oldTime;

	int maxLife;		// �ő僉�C�t
	float animSpeed;	// ���C�t�̃A�j���[�V�����X�s�[�h
	int damageAnim;		// �_���[�W

	int menuNum;		// �|�[�Y���̑I�����Ă���ԍ�

	int bansoko_Img;
	int mainUI_Img;
	int soundIcon_Img;

	int menuCount;

	int threeCountTime;

	bool setVolumeFlg;      // ���ʐݒ��ʂ��J��      true�ŊJ��
	int sliderValue;        // �X���C�_�[�̒l
	int inputRefusalTime;   // ���͋��ێ���
	bool padInputFlg;       // ���̓t���O              true:����   false:�Ȃ�
};