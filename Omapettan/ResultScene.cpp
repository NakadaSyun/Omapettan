#include "DxLib.h"
#include "ResultScene.h"
#include "TitleScene.h"


c_Result::c_Result(float rate,int life) {
	f_loadImage();
	IsNextScene = false;
	playerLife = life-1;
	rateData = rate * HairScore / HighScore * AcneScore[playerLife];
	DrawRate = 0.0f;
	SceneSeq = FADE_IN;
	c_pad = new c_GamePad(); 
	Brightness = 0;

	if (rateData >= 75) {
		ResType = 0;
	}
	else if ((rateData < 75) && (rateData >= 50)) {
		ResType = 1;
	}
	else if ((rateData < 50) && (rateData >= 25)) {
		ResType = 2;
	}
	else {
		ResType = 3;
	}
}

c_Result::~c_Result() {
	delete c_pad;
}

c_Scene* c_Result::f_update() {
	c_pad->f_update();
	switch (SceneSeq)
	{
	case FADE_IN:
		f_fadein();
		break;

	case IDOL:
		if (c_pad->IsButton1 && IsNextScene) {
			SceneSeq = FADE_OUT;
		}

		if (!c_pad->IsButton1 && !IsNextScene) {
			IsNextScene = true;
		}
		if (DrawRate < rateData) {
			DrawRate += rateData / 60;
			if (DrawRate > rateData)DrawRate = rateData;
		}
		break;

	case FADE_OUT:
		f_fadeout();
		break;

	case NEXT_SCENE:
		return new c_Title();
		break;
	}

	return this;
	/*if (c_pad->IsButton1 && IsNextScene) {
		return new c_Title();
	}

	if (!c_pad->IsButton1 && !IsNextScene) {
		IsNextScene = true;
	}

	return this;*/
}

void c_Result::f_output() const {
	char reward[4][20] = {
		 {"神・こびと"},
		 {"熟練こびと"},
		 {"凡人こびと"},
		 {"新人こびと"},
	};

	DrawGraph(0, 0, BG, true);
	SetFontSize(48); 
	
	DrawFormatString(100, 100, 0x000000, "称号:%s", reward[ResType]);
	DrawFormatString(50, 320, 0x000000, "お客様満足度…%05.2f%%", DrawRate);

	DrawExtendGraph(120, 150, 320, 350, PictImage[ResType], true);


	SetFontSize(12);
	DrawFormatString(250, 395, 0x000000, "Aボタンでタイトルに戻る");
}

void c_Result::f_loadImage() {
	BG = LoadGraph("images/Result.png");
	Beginner = LoadGraph("images/shinmai.png");
	Common = LoadGraph("images/bonzin.png");
	Expert = LoadGraph("images/zyukuren.png");
	God = LoadGraph("images/God.png");

	PictImage[0] = LoadGraph("images/GotPict.png");
	PictImage[1] = LoadGraph("images/ExpertPict.png");
	PictImage[2] = LoadGraph("images/NormalPict.png");
	PictImage[3] = LoadGraph("images/NoobPict.png");
}


void c_Result::f_fadein() {
	Brightness += 3;
	if (Brightness > 255) {
		SceneSeq = IDOL;
		Brightness = 255;
	}
	SetDrawBright(Brightness, Brightness, Brightness);
}

void c_Result::f_fadeout() {
	Brightness -= 3;
	if (Brightness < 0) {
		Brightness = 0;
		SceneSeq = NEXT_SCENE;
	}
	else {
		SetDrawBright(Brightness, Brightness, Brightness);
	}
}
