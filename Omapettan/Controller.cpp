#include "Controller.h"

c_GamePad::c_GamePad() {
	GetJoypadDirectInputState(DX_INPUT_PAD1, &controler1);

	IsButton1 = false;
	IsButton2 = false;
	IsButton3 = false;
	IsButton4 = false;

	IsButtonOption = false;

	LeftStick = 0;
	crossKey = 0;

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

	//�v���C���[�̏\���L�[����
	if (controler1.POV[0] == 0) {
		crossKey = UP;        //�����
	}
	else if (controler1.POV[0] == 9000) {
		crossKey = RIGHT;        //�E����
	}
	else if (controler1.POV[0] == 18000) {
		crossKey = DOWN;        //������
	}
	else if (controler1.POV[0] == 27000) {
		crossKey = LEFT;        //������
	}
	else if (controler1.POV[0] == 4500) {
		crossKey = RIGHTUP;        //�E�����
	}
	else if (controler1.POV[0] == 13500) {
		crossKey = RIGHTDOWN;        //�E������
	}
	else if (controler1.POV[0] == 22500) {
		crossKey = LEFTDOWN;        //��������
	}
	else if (controler1.POV[0] == 31500) {
		crossKey = LEFTUP;        //�������
	}
	else {
		crossKey = NONE;        //�����Ȃ�
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

	printf("%d", crossKey);
	printf("\n");
	printf("%d", LeftStick);
	printf("\n\n\n\n");

}

void c_GamePad::f_HairCutVibration() {
	//�U�����ꎞ��~
	StopJoypadVibration(DX_INPUT_PAD1,-1);

	// �U���J�n
	StartJoypadVibration(DX_INPUT_PAD1, 500, 200, -1);
}

void c_GamePad::f_AcneCutVibration() {
	//�U�����ꎞ��~
	StopJoypadVibration(DX_INPUT_PAD1, -1);
	// �U���J�n
	StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000, -1);
}

