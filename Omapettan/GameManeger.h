#pragma once

#include "DxLib.h"

#include "DrawCube.h"
#include "Player.h"
#include "CameraCon.h"
#include "DispUI.h"

extern VECTOR Playerposition;

class c_GameManeger
{
public:
	void f_init();				//ゲームの初期化
	void f_RoadModel();			//モデルの読込み
	void f_update();			//フレームごとの処理
	void f_output();			//フレームごとの描画


	c_DrawCube* c_Dc;
	c_Player* c_player;
	c_CameraCon* c_camera;
	c_DispUI* c_dispUI;

private:
	// 画像ファイルの読みこみ

	int model_impostor;
	int model_Plane;

};