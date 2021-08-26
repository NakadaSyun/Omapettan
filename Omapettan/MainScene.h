#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "GameManager.h"

class c_Main :public c_Scene{
public:
	c_Main();
	~c_Main();
	virtual c_Scene* f_update() override;
	virtual void f_output() const override;

	c_GameManager* c_gm;
private:
	int StageClearImage;	//ステージクリア画像
	int StageOverImage;	//ステージクリア画像
	int StageClearTime = 0; //クリアカウント用
};