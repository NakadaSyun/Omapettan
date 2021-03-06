#pragma once

#include "DxLib.h"

namespace {

	enum stickDirection {
		NONE,			//無操作
		UP,				//上
		RIGHTUP,		//右上
		RIGHT,			//右
		RIGHTDOWN,		// 右下
		DOWN,			//下
		LEFTDOWN,		//左下
		LEFT,			//左
		LEFTUP,			//左上
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