#include"TitleScene.h"
#include "MainScene.h"
#include "LoadSound.h"

extern Sound g_Snd;


static int SelectcursorX = 240;
static int SelectcursorY = 300;

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
	SceneSeq = FADE_IN;
	Brightness = 0;
}

c_Title::~c_Title() {
	delete c_Pad;
}

c_Scene* c_Title::f_update() {
	switch (SceneSeq)
	{
	case FADE_IN:
		f_fadein();
		return this;
		break;

	case IDOL:
		c_Pad->f_update(); 
		f_CheckSound();
		f_SelectPoint();
		break;

	case FADE_OUT:
		f_fadeout();
		break;

	case NEXT_SCENE:
		SetDrawBright(255, 255, 255);
		return new c_Main();
		break;
	}

	return this;


	
}

void c_Title::f_output() const{
	DrawGraph(0, 0, BG, true);
	

	DrawFormatString(270,300,0x000000,"ゲームスタート");
	DrawFormatString(270,350, 0x000000, "ゲーム終了");
	DrawBox(SelectcursorX, SelectcursorY, SelectcursorX+20, SelectcursorY+20,
		0x000000,TRUE);

}

void c_Title::f_loadImage() {
	BG = LoadGraph("images/Title.png");
}


void c_Title::f_fadein() {

	Brightness += 3;
	if (Brightness > 255) {
		SceneSeq = IDOL;
		Brightness = 255;
	}
	SetDrawBright(Brightness, Brightness, Brightness);
}

void c_Title::f_fadeout() {
	Brightness -= 3;
	if (Brightness < 0) {
		Brightness = 0;
		SceneSeq = NEXT_SCENE;
	}
	else {
		SetDrawBright(Brightness, Brightness, Brightness);
	}
}

void c_Title::f_CheckSound() {
	if (CheckSoundMem(g_Snd.TitleBGM) == 0) {
		PlaySoundMem(g_Snd.TitleBGM, DX_PLAYTYPE_LOOP);
	}
}

void c_Title::f_SelectPoint() {
	if (SelectcursorY == 300) {
		if (c_Pad->IsButton1 && IsNextScene) {
			PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);
			StopSoundMem(g_Snd.TitleBGM);
			SceneSeq = FADE_OUT;
		}

		if (!c_Pad->IsButton1 && !IsNextScene) {
			IsNextScene = true;
		}
	}

	if (SelectcursorY == 350) {
		if (c_Pad->IsButton1) {
			DxLib_End();
			PlaySoundMem(g_Snd.Menu_Select, DX_PLAYTYPE_BACK);
		}
	}


	if (c_Pad->LeftStick == 1 && SelectcursorY == 350) {
		SelectcursorY = 300;
		PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
	}
	if (c_Pad->LeftStick == 5 && SelectcursorY == 300) {
		SelectcursorY = 350;
		PlaySoundMem(g_Snd.Menumove, DX_PLAYTYPE_BACK);
	}
}