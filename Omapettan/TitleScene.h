#pragma once

#include "Dxlib.h"
#include "Scene.h"
#include "Controller.h"

class c_Title : public c_Scene {
public:
	c_Title();
	~c_Title();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;
	virtual void f_fadeout() override;		//暗転する
	virtual void f_fadein() override;			//明るくする

	void f_loadImage();

	void f_CheckSound();
	void f_SelectPoint();
	c_GamePad* c_Pad;

private:
	int BG;			//背景画像用変数
	int SceneSeq;	//タイトルシーンの状態	0:フェードイン　1:入力待ち　2:フェードアウト
	int Brightness;
};