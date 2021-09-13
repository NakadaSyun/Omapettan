#pragma once
#include "Dxlib.h"
#include "Scene.h"
#include "Controller.h"

class c_Result : public c_Scene{
public:
	c_Result(float rate);
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
	int SceneSeq;	//タイトルシーンの状態	0:フェードイン　1:入力待ち　2:フェードアウト
	int Brightness;
};