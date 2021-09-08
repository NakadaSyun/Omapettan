#include "DxLib.h"
#include "ResultScene.h"
#include "TitleScene.h"


c_Result::c_Result(float rate) {
	f_loadImage();
	IsNextScene = false;
	rateData = rate;

	c_pad = new c_GamePad();
}

c_Result::~c_Result() {
	delete c_pad;
}

c_Scene* c_Result::f_update() {
	c_pad->f_update();

	if (c_pad->IsButton1 && IsNextScene) {
		return new c_Title();
	}

	if (!c_pad->IsButton1 && !IsNextScene) {
		IsNextScene = true;
	}

	return this;
}

void c_Result::f_output() const {
	DrawGraph(0, 0, BG, true);
	if (rateData >= 75) DrawGraph(500, 380, God, true);
	else if ((rateData < 75) && (rateData >= 50)) DrawGraph(500, 380, Expert, true);
	else if ((rateData < 50) && (rateData >= 25)) DrawGraph(500, 380, Common, true);
	else DrawGraph(500, 380, Beginner, true);
	DrawFormatString(250, 400, 0x000000, "Aボタンでタイトルに戻る");
	DrawFormatString(480, 30, 0x000000, "%03d%%", (int)rateData);
}

void c_Result::f_loadImage() {
	BG = LoadGraph("images/Result.png");
	Beginner = LoadGraph("images/shinmai.png");
	Common = LoadGraph("images/bonzin.png");
	Expert = LoadGraph("images/zyukuren.png");
	God = LoadGraph("images/God.png");
}