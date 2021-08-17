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

void c_GamePad::f_update() {// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &controler1);

	//�v���C���[�̃{�^������
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

	//�v���C���[�̃X�e�B�b�N����
	if (controler1.Y < 0
		&& controler1.X >= -200
		&& controler1.X <= 200) {
		LeftStick = UP;		//�����
	}
	else if (controler1.X > 0
		&& controler1.Y >= -200
		&& controler1.Y <= 200) {
		LeftStick = RIGHT;		//�E����
	}
	else if (controler1.Y > 0
		&& controler1.X >= -200
		&& controler1.X <= 200) {
		LeftStick = DOWN;		//������
	}
	else if (controler1.X < 0
		&& controler1.Y >= -200
		&& controler1.Y <= 200) {
		LeftStick = LEFT;		//������
	}
	else if (controler1.Y < 0
		&& controler1.X > 0) {
		LeftStick = RIGHTUP;		//�E�����
	}
	else if (controler1.Y > 0
		&& controler1.X > 0) {
		LeftStick = RIGHTDOWN;		//�E������
	}
	else if (controler1.X < 0
		&& controler1.Y > 0) {
		LeftStick = LEFTDOWN;		//��������
	}
	else if (controler1.X < 0
		&& controler1.Y < 0) {
		LeftStick = LEFTUP;		//�������
	}
	else {
		LeftStick = NONE;		//�����Ȃ�
	}

	//�f�o�b�N�p
	//f_output();
}

void c_GamePad::f_output() {

	if (IsButton1) printf("�{�^��A");
	if (IsButton2) printf("�{�^��B");
	if (IsButton3) printf("�{�^��X");
	if (IsButton4) printf("�{�^��Y");
	if (IsButtonOption) printf("�I�v�V����");

	printf("%d", LeftStick);
	printf("\n\n\n\n");

}

