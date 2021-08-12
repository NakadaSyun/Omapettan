#include"TitleScene.h"
#include "MainScene.h"


c_Title::c_Title() {
	f_loadImage();
	IsNextScene = false;
}

c_Title::~c_Title() {
}

c_Scene* c_Title::f_update() {
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		return new c_Main();
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
	}

	return this;
}

void c_Title::f_output() const{
	DrawGraph(0, 0, BG, true);
}

void c_Title::f_loadImage() {
	BG = LoadGraph("images/Title.png");
}

