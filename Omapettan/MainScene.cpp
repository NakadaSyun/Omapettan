#include "MainScene.h"

c_Main::c_Main() {
	//�Q�[���}�l�[�W���[����
	c_gm = new c_GameManager();

	// �Q�[���}�l�W��������
	c_gm->f_init();
}

c_Main::~c_Main() {
	delete c_gm;
}

void c_Main::f_update() {
	c_gm->f_update();

}

void c_Main::f_output() {
	c_gm->f_output();
}

