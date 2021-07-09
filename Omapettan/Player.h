#pragma once
#include "DxLib.h"

class c_Player {
public:
	c_Player(const int Model);
	void f_init();
	void f_update();
	void f_draw();
private:
	int p_Model;
	VECTOR p_Position;
};