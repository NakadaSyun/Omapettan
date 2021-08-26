#pragma once
#include "DxLib.h"
#include "HairVertexBuffer.h"
#include "DrawAcne.h"

class c_MainUI {
public:
	c_MainUI(int bansokoImg);
	void f_init();		// 初期化
	void f_update();	// 更新
	void f_draw();		// 描画

	bool hairStateFlg[HAIR_NUM] = { 0 };
	bool acneStateFlg[ACNE_NUM] = { 0 };

private:
	void MenuUI();		// メニュー
	void TimeCountUI();	// 時間カウント
	void AchievementUI();// 達成率
	void LifeUI();		// ライフ

	bool pauseFlg;		// 一時停止フラグ

	int timeLimit;		// 制限時間
	int time;			// 現在の時間
	int timer;			// 時間カウント
	int minute;			// 分
	int second;			// 秒

	int rate;			// 率

	int maxLife;		// 最大ライフ
	int life;			// ライフ

	int bansoko_Img;
};