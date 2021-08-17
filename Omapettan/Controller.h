#pragma once

#include "DxLib.h"

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