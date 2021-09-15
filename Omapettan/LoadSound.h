#pragma once
#include "DxLib.h"

struct Sound {
public:
	void SetSound();        //音量設定

	int KAMISORI_Hold;		//剃刀を構えたときの音
	int HIGESORI_SE;		//髭を剃った時の音
	int StageClear;			 //ステージクリア時のSE
	int Player_footStep;	//プレイヤーの足音
	int Player_footStep_DS; //プレイヤーの足音（倍速）
	int Menumove;			//メニュー内移動時SE
	int Menu_Select;		//メニュー内での決定時SE
	int Menu_Open;			//メニュー開くSE
	int Menu_Cansel;		//メニュー内でのキャンセル
	int Customer_Damage;	//フキデモの破壊
	int Customer_Cry[4];	//フキデモの破壊、客の叫び
	int GameOver;			//ゲームオーバー時SE
	int TitleBGM;			//タイトル画面のBGM
	int StageBGM;			//ステージ内でのBGM

	int volume = 5;             // 音量

};

int f_LoadSound(void);	//関数の定義

