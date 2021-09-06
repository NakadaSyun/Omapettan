#include"TitleScene.h"
#include "MainScene.h"
#include "LoadSound.h"

extern Sound g_Snd;


static int SelectcursorX = 270;
static int SelectcursorY = 400;

c_Title::c_Title() {
	f_loadImage();
	IsNextScene = false;

	c_Pad = new c_GamePad();

	if (CheckSoundMem(g_Snd.GameOver) == 1) {
		StopSoundMem(g_Snd.GameOver);
	}
	if (CheckSoundMem(g_Snd.StageBGM) == 1) {
		StopSoundMem(g_Snd.StageBGM);
	}
}

c_Title::~c_Title() {
	delete c_Pad;
}

c_Scene* c_Title::f_update() {
	c_Pad->f_update();
	if (CheckSoundMem(g_Snd.TitleBGM) == 0) {
		PlaySoundMem(g_Snd.TitleBGM, DX_PLAYTYPE_LOOP);
	}

	if (SelectcursorY == 400) {
		if (c_Pad->IsButton1 && IsNextScene) {
			PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);
			StopSoundMem(g_Snd.TitleBGM);
			return new c_Main();
		}

		if (!c_Pad->IsButton1 && !IsNextScene) {
			IsNextScene = true;
		}
	}

	if (SelectcursorY == 450) {
		if (c_Pad->IsButton1) {
			DxLib_End();
			PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);
		}
	}


	if (c_Pad->LeftStick == 1 && SelectcursorY == 450) {
		SelectcursorY = 400;
		PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
	}
	if (c_Pad->LeftStick == 5 && SelectcursorY == 400) {
		SelectcursorY = 450;
		PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
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

