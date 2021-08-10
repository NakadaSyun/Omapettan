#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "GameManager.h"

class c_Main{
public:
	c_Main();
	~c_Main();
	
	void f_update();
	void f_output();

	c_GameManager* c_gm;
};