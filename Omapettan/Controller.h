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

	bool IsButton1;
	bool IsButton2;
	bool IsButton3;
	bool IsButton4;

	bool IsButtonOption;

	int LeftStick;

private:
	DINPUT_JOYSTATE controler1;


};