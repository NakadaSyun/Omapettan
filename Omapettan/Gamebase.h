#pragma once

#include "DxLib.h"
#include "GameManager.h"
#include "SceneManager.h"

class GameBase {
public:
	bool f_init();
	void f_loop();
	void f_exit();
private:
	bool isRunning;

	//c_GameManager* c_gm;
	c_sceneManager* c_sm;

	void f_input();
	void f_update();
	void f_output();
};