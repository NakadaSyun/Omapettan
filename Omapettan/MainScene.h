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
	virtual void f_fadeout() override;		//暗転する
	virtual void f_fadein() override;			//明るくする

	c_GameManager* c_gm;
	
private:
	
	int Freq, Add;			//ステージBGMピッチ変更

	int StageClearImage;	//ステージクリア画像
	int StageOverImage;	//ステージクリア画像
	int TimeUPImage;		//タイムアップ画像
	int StageClearTime = 0; //クリアカウント用

	int Brightness;		//明るさ調整用変数
	int SceneSeq;		//フェード用変数

	bool DebugFlg; //デバッグモード表示・非表示用フラグ
	bool KeyDownFlg;//キーが押されたどうかのフラグ

	void f_debug(bool flg);
	int DebugLoadTime;
	bool padKeyFlg = false;
	bool playerDebug = false;

	bool isClearFlg = false;

	void f_debugUI();
};