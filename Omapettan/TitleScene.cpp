#include"TitleScene.h"
#include "MainScene.h"


static int SelectcursorX = 270;
static int SelectcursorY = 400;

c_Title::c_Title() {
	f_loadImage();
	IsNextScene = false;

}

c_Title::~c_Title() {
}

c_Scene* c_Title::f_update() {

	if (SelectcursorY == 400) {
		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && IsNextScene) {
			return new c_Main();
		}

		if (CheckHitKey(KEY_INPUT_SPACE) == 0 && !IsNextScene) {
			IsNextScene = true;
		}
	}

	if (SelectcursorY == 450) {
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			DxLib_End();
		}
	}


	if (CheckHitKey(KEY_INPUT_W) == 1) {
		SelectcursorY = 400;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1) {
		SelectcursorY = 450;
	}


	return this;
}

void c_Title::f_output() const{
	DrawGraph(0, 0, BG, true);

	DrawFormatString(300,400,0x000000,"ゲームスタート");
	DrawFormatString(300,450, 0x000000, "ゲーム終了");
	DrawBox(SelectcursorX, SelectcursorY, SelectcursorX+20, SelectcursorY+20,
		0x000000,TRUE);

}

void c_Title::f_loadImage() {
	BG = LoadGraph("images/Title.png");
}

