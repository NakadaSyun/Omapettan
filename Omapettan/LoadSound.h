#pragma once
#include "DxLib.h"

struct Sound {
public:

	int KAMISORI_Hold;		//剃刀を構えたときの音
	int HIGESORI_SE;		//髭を剃った時の音
	int StageClear;			 //ステージクリア時のSE
	int Player_footStep;	//プレイヤーの足音
	int Menumove;			//メニュー内移動時SE
	int Menu_Select;		//メニュー内での決定時SE
	int Menu_Open;			//メニュー開くSE
	int Menu_Cansel;		//メニュー内でのキャンセル
	int Customer_Damage;	//フキデモの破壊


};

int f_LoadSound(void);	//関数の定義

