#include "MainScene.h"
#include "ResultScene.h"

c_Main::c_Main() {
	//ゲームマネージャー生成
	c_gm = new c_GameManager();

	// ゲームマネジャ初期化
	c_gm->f_init();
}

c_Main::~c_Main() {
	delete c_gm;
}

c_Scene* c_Main::f_update() {
	c_gm->f_update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		return new c_Result();
	}


	return this;
}

void c_Main::f_output() const{
	c_gm->f_output();
}

