#include "DxLib.h"
#include "ResultScene.h"
#include "TitleScene.h"


c_Result::c_Result() {
	f_loadImage();
	IsNextScene = false;
}

c_Result::~c_Result() {

}

c_Scene* c_Result::f_update() {
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
		return new c_Title();
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
		IsNextScene = true;
	}

	return this;
}

void c_Result::f_output() const {
	DrawGraph(0, 0, BG, true);
}

void c_Result::f_loadImage() {
	BG = LoadGraph("images/Result.png");
}