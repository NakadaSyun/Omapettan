#include "Controller.h"

c_GamePad::c_GamePad() {
	GetJoypadDirectInputState(DX_INPUT_PAD1, &controler1);

	IsButton1 = false;
	IsButton2 = false;
	IsButton3 = false;
	IsButton4 = false;

	IsButtonOption = false;

	LeftStick = 0;

}

void c_GamePad::f_update() {// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &controler1);

	//プレイヤーのボタン判定
	if (controler1.Buttons[0] == 128) IsButton1 = true;
	else							IsButton1 = false;

	if (controler1.Buttons[1] == 128)	IsButton2 = true;
	else							IsButton2 = false;


	if (controler1.Buttons[2] == 128)	IsButton3 = true;
	else							IsButton3 = false;


	if (controler1.Buttons[3] == 128)	IsButton4 = true;
	else							IsButton4 = false;

	if (controler1.Buttons[7] == 128)	IsButtonOption = true;
	else							IsButtonOption = false;

	//if (g_controler1.Buttons[5] == 128)	g_playerRed.EndButton[1] = true;
	//else							g_playerRed.EndButton[1] = false;

	//プレイヤーのスティック判定
	if (controler1.Y < 0
		&& controler1.X >= -200
		&& controler1.X <= 200) {
		LeftStick = UP;		//上向き
	}
	else if (controler1.X > 0
		&& controler1.Y >= -200
		&& controler1.Y <= 200) {
		LeftStick = RIGHT;		//右向き
	}
	else if (controler1.Y > 0
		&& controler1.X >= -200
		&& controler1.X <= 200) {
		LeftStick = DOWN;		//下向き
	}
	else if (controler1.X < 0
		&& controler1.Y >= -200
		&& controler1.Y <= 200) {
		LeftStick = LEFT;		//左向き
	}
	else if (controler1.Y < 0
		&& controler1.X > 0) {
		LeftStick = RIGHTUP;		//右上向き
	}
	else if (controler1.Y > 0
		&& controler1.X > 0) {
		LeftStick = RIGHTDOWN;		//右下向き
	}
	else if (controler1.X < 0
		&& controler1.Y > 0) {
		LeftStick = LEFTDOWN;		//左下向き
	}
	else if (controler1.X < 0
		&& controler1.Y < 0) {
		LeftStick = LEFTUP;		//左上向き
	}
	else {
		LeftStick = NONE;		//方向なし
	}

	//デバック用
	//f_output();
}

void c_GamePad::f_output() {

	if (IsButton1) printf("ボタンA");
	if (IsButton2) printf("ボタンB");
	if (IsButton3) printf("ボタンX");
	if (IsButton4) printf("ボタンY");
	if (IsButtonOption) printf("オプション");

	printf("%d", LeftStick);
	printf("\n\n\n\n");

}

void c_GamePad::f_HairCutVibration() {
	//振動を一時停止
	StopJoypadVibration(DX_INPUT_PAD1,-1);

	// 振動開始
	StartJoypadVibration(DX_INPUT_PAD1, 500, 200, -1);
}

void c_GamePad::f_AcneCutVibration() {
	//振動を一時停止
	StopJoypadVibration(DX_INPUT_PAD1, -1);
	// 振動開始
	StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000, -1);
}

