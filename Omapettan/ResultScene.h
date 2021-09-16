#pragma once
#include "Dxlib.h"
#include "Scene.h"
#include "Controller.h"

namespace {
	//剃毛率の最大得点
	float HairScore = 80.0f;
	//吹き出物の倍率
	float AcneScore[3] = { 1.1, 1.15, 1.25 };
	//最高スコア
	float HighScore = 100.0f;
}

class c_Result : public c_Scene{
public:
	c_Result(float rate,int life);
	~c_Result();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;
	virtual void f_fadeout() override;		//暗転する
	virtual void f_fadein() override;			//明るくする


	void f_loadImage();

	c_GamePad* c_pad;
private:
	int BG;
	int Beginner;
	int Common;
	int Expert;
	int God;

	float rateData;
	float DrawRate;
	int SceneSeq;	//タイトルシーンの状態	0:フェードイン　1:入力待ち　2:フェードアウト
	int Brightness;

	int PictImage[4];
	int ResType;

	int playerLife;
};