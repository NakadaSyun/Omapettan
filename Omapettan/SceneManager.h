#pragma once
#include "DxLib.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "ResultScene.h"


class c_sceneManager{
public:
	c_sceneManager();
	void f_update();
	void f_output();
	void f_NextScene();


private:

	c_Title* c_title;
	c_Main* c_main;
	c_Result* c_result;

	int selectScene;
};