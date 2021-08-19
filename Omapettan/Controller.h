#pragma once

#include "DxLib.h"

namespace {

	enum stickDirection {
		NONE,			//ñ≥ëÄçÏ
		UP,				//è„
		RIGHTUP,		//âEè„
		RIGHT,			//âE
		RIGHTDOWN,		// âEâ∫
		DOWN,			//â∫
		LEFTDOWN,		//ç∂â∫
		LEFT,			//ç∂
		LEFTUP,			//ç∂è„
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

private:
	DINPUT_JOYSTATE controler1;


};