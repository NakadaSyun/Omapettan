#pragma once

#include "DxLib.h"

namespace {

	enum stickDirection {
		NONE,			//������
		UP,				//��
		RIGHTUP,		//�E��
		RIGHT,			//�E
		RIGHTDOWN,		// �E��
		DOWN,			//��
		LEFTDOWN,		//����
		LEFT,			//��
		LEFTUP,			//����
	};
}

class c_GamePad {
public:
	c_GamePad();
	void f_update();
	void f_output();

	void f_HairCutVibration();
	void f_AcneCutVibration();

	bool IsButton1;
	bool IsButton2;
	bool IsButton3;
	bool IsButton4;

	bool IsButtonOption;

	int LeftStick;

	int crossKey;

private:
	DINPUT_JOYSTATE controler1;


};