#include "MainScene.h"

c_Main::c_Main() {
	//ゲームマネージャー生成
	c_gm = new c_GameManager();

	// ゲームマネジャ初期化
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

